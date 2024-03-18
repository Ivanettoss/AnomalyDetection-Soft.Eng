#include "main.h"

#define READ_STREAM "stream_1"

using namespace std;

//
int reader()
{
    redisContext *c2r;
    redisReply *reply;

    Con2DB db(PSQL_SERVER, PSQL_PORT, PSQL_NAME, PSQL_PASS, PSQL_DB);
    // faccio getFields qui per non doverlo fare ad ogni chiamata quando devo fare l'insert nel database
    vector<string> fields = getFields(db, "log");

    int block = 10000;
    int pid;
    int checkSum; // valore di check per la correttezza delle funzioni

    pid = getpid();

    printf("main(): pid %d: connecting to redis ...\n", pid);

    c2r = redisConnect("localhost", 6379);

    printf("main(): pid %d: connected to redis\n", pid);

    initStreams(c2r, READ_STREAM);

    printf("Reading from %s\n", READ_STREAM);
    reply = RedisCommand(c2r, "XLEN %s", READ_STREAM);
    vector<int> window = {0, 0};
    if (DEBUGWINDOWSELECT == 1)
    {
        window = windowSelect(reply->integer);
    }

    int counter = window[0];
    freeReplyObject(reply);

    while (true)
    {
        printf("new_reader(): pid %d: Sending XREADGROUP (stream: %s, BLOCK: %d)\n", pid, READ_STREAM, block);
        reply = RedisCommand(c2r, "XREADGROUP GROUP diameter lollo BLOCK %d COUNT 1 NOACK STREAMS %s >",
                             block, READ_STREAM);
        // Controlla se ci sono stati errori nella risposta o se è nulla
        if (reply->type == REDIS_REPLY_NIL)
        {
            printf("No new infos found in 10 sec interval\n");
            printf("exiting...\n");
            break;
        }
        if (reply == NULL || reply->type == REDIS_REPLY_ERROR)
        {
            printf("Error reading messages from Redis\n");
            break;
        }

        // Qui devo fare le operazioni di insert dentro la tabella log di ciò che ho letto dal log

        if (counter <= window[1])
        {
            checkSum = insertDb(db, fields, "log", getValue(reply, 0));
            if (checkSum == -100)
            {
                cerr << "Error occured: fields quantity not overlapping" << endl;
                cout << "Error occured: fields quantity not overlapping" << endl;
                return -1;
            }
        }
        counter += 1;
        freeReplyObject(reply);
    }
    freeReplyObject(reply);
    redisFree(c2r);
    printf("disconnecting from redis ...\n");
    return 0;
}