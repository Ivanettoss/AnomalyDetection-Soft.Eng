#include "main.h"

using namespace std;

Con2DB init_connection(const char* server, const char* port, const char* name, const char* pass, const char* db_name){
    Con2DB db(server, port, name, pass, db_name);
    return db;
}

int endConnection(Con2DB db){
    db.finish();
    return 0;
}