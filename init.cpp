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

    readLine(buffer, buffer_size, file);
    buildLine(buffer, current_row);
    vector<int> disabled_fields = exclusionCalc(current_row);
    current_row = excludeElements(current_row, disabled_fields);

    // Ora ho tutti i campi esclusi quelli che l'utente non vuole, devo chiamare init_log e preparare la tabella
    Con2DB db = init_connection(PSQL_SERVER, PSQL_PORT, PSQL_NAME, PSQL_PASS, PSQL_DB);
    init_log(db, current_row);
    
    matrix.push_back(current_row);

    // Leggi il file riga per riga
    initStreams(c2r, WRITE_STREAM);
    int entry_counter = 0;
    while (true)
    {
        // PULISCI IL BUFFER DELLA RIGA
        current_row.clear();
        // LEGGI DA CSV E METTI IN BUFFER
        readLine(buffer, buffer_size, file);
        // BUFFER A SINGOLO ELEMENTO ----> BUFFER CON CAMPI SPLITTATI
        buildLine(buffer, current_row);
        if (feof(file) || std::string(buffer).find_first_not_of(';') == std::string::npos)
        { // Se la riga è vuota o contiene solo caratteri di terminazione
            break;
        }
        entry_counter++;
        printf("RIGA85 RAGGIUNTA");

        // ESCLUDI GLI ELEMENTI CHE L'UTENTE NON VUOLE
        current_row = excludeElements(current_row, disabled_fields);
    
        reply = RedisCommand(c2r, "XADD %s * entry:%d mem:%s", WRITE_STREAM, entry_counter, buffer);
        assertReplyType(c2r, reply, REDIS_REPLY_STRING);
        printf("main(): pid =%d: Added entry:%d -> mem:%s (id: %d)\n", pid, entry_counter, reply->str, entry_counter);
        freeReplyObject(reply);

        // PUSH NELLA MATRICE DELLA RIGA CORRETTA
        matrix.push_back(current_row);
    }

    fclose(file);
    /*
    for (long unsigned int i = 0; i < matrix.size(); i++)
    {
        if (matrix[i].size() > 1)
        {
            printLine(matrix[i]);
        }
    }
    */
   int ret = endConnection(db);
    return ret;
}
