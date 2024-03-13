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

    // Aumentare la grandezza del buffer se argc è 3
    if (argc > 2)
    {
        buffer_size *= atoi(argv[2]);
    }

    if (argc > 3)
    {
        cerr << "Too many arguments!" << endl;
        return -1;
    }

    // Nome del file CSV da leggere
    const char *filename = argv[1];

    if (DEBUGFILENAME)
    {
        filename = "AirQuality.csv";
    }

    // Apri il file in modalità lettura
    FILE *file = fopen(filename, "r");

    // Verifica se il file è stato aperto correttamente
    if (!file)
    {
        cerr << " Impossibile aprire il file\n"
             << filename << endl;
        return 1;
    }

    // Buffer per leggere ogni riga del file e vettore di stringhe per i valori dei campi del DB
    char buffer[buffer_size];
    // Riga in costruzione per la matrice matrix
    vector<string> current_row;
    vector<int> disabled_fields;
    vector<string> waste;

    readLine(buffer, buffer_size, file);
    buildLine(buffer, current_row);

    if (DEBUGFIELDSSELECT)
    {
        disabled_fields = exclusionCalc(current_row);
        current_row = excludeElements(current_row, disabled_fields);
    }

    // Ora ho tutti i campi esclusi quelli che l'utente non vuole, devo chiamare init_log e preparare la tabella
    Con2DB db = init_connection(PSQL_SERVER, PSQL_PORT, PSQL_NAME, PSQL_PASS, PSQL_DB);
    init_log(db, current_row);

    // Leggi il file riga per riga
    initStreams(c2r, WRITE_STREAM);
    int entry_counter = 0;
    while (true)
    {
        if (feof(file) || std::string(buffer).find_first_not_of(';') == std::string::npos)
        { // Se la riga è vuota o contiene solo caratteri di terminazione
            break;
        }
        // PULISCI IL BUFFER DELLA RIGA
        current_row.clear();
        // LEGGI DA CSV E METTI IN BUFFER
        readLine(buffer, buffer_size, file);

        // \r lookingfor
        if (buffer[strlen(buffer) - 1] == '\r')
        {
            buffer[strlen(buffer) - 1] = '\0';
        }

        // BUFFER A SINGOLO ELEMENTO ----> CURRENT_ROW CON CAMPI SPLITTATI
        buildLine(buffer, current_row);

        entry_counter++;

        // ESCLUDI GLI ELEMENTI CHE L'UTENTE NON VUOLE
        if (DEBUGFIELDSSELECT)
        {
            current_row = excludeElements(current_row, disabled_fields);
        }

        string input;
        for (size_t i = 0; i < current_row.size(); i++)
        {
            input += current_row[i] + " ";
        }

        // Non inserisco nella pipe le linee nulle
        if (current_row.size() <= 1)
        {
            continue;
        }

        reply = RedisCommand(c2r, "XADD %s * %d %s", WRITE_STREAM, entry_counter, stringToChar(input));
        assertReplyType(c2r, reply, REDIS_REPLY_STRING);
        // dumpReply(reply, 1);
        // printf("main(): pid =%d: stream %s: Added %d -> %s (id: %s)\n", pid, WRITE_STREAM, entry_counter, stringToChar(input), reply->str);
        freeReplyObject(reply);
    }

    fclose(file);

    redisFree(c2r);

    int ret = endConnection(db);
    return ret;
}
