#include "main.h"
#define WRITE_STREAM "stream_1"

using namespace std;

int init(int argc, char *argv[])
{
    int buffer_size = BUFFER_SIZE;

    // Redis vars
    redisContext *c2r;
    redisReply *reply;
    int pid = getpid();

    printf("main(): pid %d: connecting to redis ...\n", pid);
    c2r = redisConnect("localhost", 6379);
    reply = RedisCommand(c2r, "XTRIM %s MAXLEN 0", WRITE_STREAM);
    freeReplyObject(reply);
    printf("main(): pid %d: connected to redis\n", pid);

    // Choose buffer_size if user specified it, otherwise use 1 block of 512 bytes
    if (argc > 2)
    {
        buffer_size *= atoi(argv[2]);
    }

    if (argc > 3)
    {
        cerr << "Too many arguments!" << endl;
        return -1;
    }

    // CSV namefile declaration
    const char *filename = argv[1];

    // Open file in read mode
    FILE *file = fopen(filename, "r");

    if (!file)
    {
        cerr << " \n\nSpecify the name of the CSV file inside the initRedisDataStream/bin folder.\n";
        cerr << " As <buffer_size>, specify the number of 512-byte blocks to use (if not specified, 1 block will be used).\n";
        cerr << " ./install.sh <filename.csv> <buffer_size>" << endl;
        return -1;
    }

    // Buffer to read each line of the file and vector of strings for the DB field values
    char buffer[buffer_size];
    // Constructing row for the matrix
    vector<string> current_row;
    vector<int> enabled_fields;
    vector<string> waste;

    // Read fields first
    readLine(buffer, buffer_size, file);
    buildLine(buffer, current_row);

    // Exclude fields you dont want to process
    if (DEBUGFIELDSSELECT)
    {
        enabled_fields = exclusionCalc(current_row);
        // If user excludes all fields
        if (enabled_fields.size() == 0)
        {
            cout << "All fields have been excluded, no calculation possible" << endl;
            return 0;
        }
        current_row = excludeElements(current_row, enabled_fields);
    }

    // Now I have all fields excluded those that the user does not want, I must call init_log and prepare the table
    Con2DB db(PSQL_SERVER, PSQL_PORT, PSQL_NAME, PSQL_PASS, PSQL_DB);
    createTable(db, "log", current_row);

    // Read the file line by line
    initStreams(c2r, WRITE_STREAM);
    int entry_counter = 0;
    while (true)
    {
        if (feof(file) || std::string(buffer).find_first_not_of(';') == std::string::npos)
        { // If the line is empty or contains only termination characters
            break;
        }
        // CLEAR THE LINE BUFFER
        current_row.clear();
        // READ FROM CSV AND PUT INTO BUFFER
        readLine(buffer, buffer_size, file);

        // \r lookingfor to normalize the encoded string
        if (buffer[strlen(buffer) - 1] == '\r')
        {
            buffer[strlen(buffer) - 1] = '\0';
        }

        // BUFFER TO SINGLE ELEMENT ----> CURRENT_ROW WITH SPLIT FIELDS
        buildLine(buffer, current_row);

        entry_counter++;

        // EXCLUDE ITEMS THAT USER DOES NOT WANT
        if (DEBUGFIELDSSELECT)
        {
            current_row = excludeElements(current_row, enabled_fields);
        }

        string input;
        for (size_t i = 0; i < current_row.size(); i++)
        {
            input += current_row[i] + " ";
        }

        // Do not insert null lines into the pipe
        if (current_row.size() <= 1)
        {
            continue;
        }

        reply = RedisCommand(c2r, "XADD %s * %d %s", WRITE_STREAM, entry_counter, stringToChar(input));
        assertReplyType(c2r, reply, REDIS_REPLY_STRING);
        freeReplyObject(reply);
    }

    fclose(file);

    redisFree(c2r);

    db.finish();
    return 0;
}
