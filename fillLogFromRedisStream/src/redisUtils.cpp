#include "main.h"

using namespace std;


string getKey(redisReply *reply, int numero){
    return reply->element[0]->element[1]->element[numero]->element[0]->str;
}

string getValue(redisReply *reply, int numero){
    return reply->element[0]->element[1]->element[numero]->element[1]->element[1]->str;
}