// Devo scrivere un programma che si connette alla redisStream, esegue il comando redisCommand XLEN e stampa 
// a schermo il risultato
#define MONITOR_STREAM "stream_1"

#include <iostream>
#include <ostream>
#include "con2redis/src/con2redis.h"
#include "con2redis/src/local.h"
#include <hiredis/hiredis.h>

using namespace std;

int main(){

    redisContext *c2r;
    redisReply *reply;
    c2r = redisConnect("localhost", 6379);
    initStreams(c2r, MONITOR_STREAM);
    printf("Reading from %s\n", MONITOR_STREAM);
    reply = RedisCommand(c2r, "XLEN %s", MONITOR_STREAM);
    cout << "There are "; 
    cout << reply->integer;
    cout << " entries in redisStream" << endl;
    freeReplyObject(reply);
    redisFree(c2r);
}