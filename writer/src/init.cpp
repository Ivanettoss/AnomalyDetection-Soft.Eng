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

    if (DEBUGL > 0)
    {
        filename = "prova.csv";
    }

    // Apri il file in modalità lettura
    FILE *file = fopen(filename, "r");

    // Verifica se il file è stato aperto correttamente
    if (!file)
    {
        cerr << " Impossibile aprire il file " << filename << endl;
        return 1;
    }

    // Buffer per leggere ogni riga del file e vettore di stringhe per i valori dei campi del DB
    char buffer[buffer_size];
    // Matrice di debug per il futuro DB
    vector<vector<string>> matrix;
    // Riga in costruzione per la matrice matrix
    vector<string> current_row;
    vector<int> disabled_fields;
    vector<string> waste;

    readLine(buffer, buffer_size, file);
    buildLine(buffer, current_row);
    if (DEBUGL > 1)
    {
        waste = wasteCalc();
    }

    if (DEBUGL > 1)
    {
        disabled_fields = exclusionCalc(current_row);
        current_row = excludeElements(current_row, disabled_fields);
    }

    // Ora ho tutti i campi esclusi quelli che l'utente non vuole, devo chiamare init_log e preparare la tabella
    Con2DB db = init_connection(PSQL_SERVER, PSQL_PORT, PSQL_NAME, PSQL_PASS, PSQL_DB);
    init_log(db, current_row);

    matrix.push_back(current_row);

    // Leggi il file riga per riga
    reply = RedisCommand(c2r, "DEL %s", WRITE_STREAM);
    assertReply(c2r, reply);
    dumpReply(reply, 0);
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
        // BUFFER A SINGOLO ELEMENTO ----> CURRENT_ROW CON CAMPI SPLITTATI
        buildLine(buffer, current_row);

        entry_counter++;

        // ESCLUDI GLI ELEMENTI CHE L'UTENTE NON VUOLE
        if (DEBUGL > 1)
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
        printf("main(): pid =%d: stream %s: Added %d -> %s (id: %s)\n", pid, WRITE_STREAM, entry_counter, stringToChar(input), reply->str);
        freeReplyObject(reply);

        // PUSH NELLA MATRICE DELLA RIGA CORRETTA
        matrix.push_back(current_row);
    }

    fclose(file);
    if (DEBUGL > 1)
    {
        vector<int> window = windowSelect(entry_counter);
        float tolerance = selectTolerance();
        cout << tolerance << endl;
    }
    /*
    for (size_t i = 0; i < matrix.size() - 1; i++)
    {
        reply = RedisCommand(c2r, "XREAD STREAMS %s 0", WRITE_STREAM);

        string key = getKey(reply, i);
        cout << key << "   ";
        string value = getValue(reply, i);
        cout << value << endl;
    }
    */

    /*
        for (int i = 0; i < entry_counter; i++)
        {
            printf("mina(): pid %d: [%d] Sending XREAD (stream: %s, BLOCK: %d)\n", pid, i, WRITE_STREAM, 10000);
            reply = RedisCommand(c2r, "XREAD BLOCK %d STREAMS %s COUNT 1", 10000, WRITE_STREAM);

            assertReply(c2r, reply);
            dumpReply(reply, 0);
            freeReplyObject(reply);
        }
    */
    redisFree(c2r);

    int ret = endConnection(db);
    return ret;
}
