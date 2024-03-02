#include "main.h"

using namespace std;

void init_log(Con2DB db, vector<string> current_row){
    createTable(db, "log", current_row);
}