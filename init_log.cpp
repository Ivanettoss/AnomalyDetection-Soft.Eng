#include "main.h"

using namespace std;

void init_log(vector<string> current_row){
    // Prima mi collego al db
    Con2DB db("localhost", "5432", "lollo", "lollo", "AnomalyDetection");
    // Poi creo la tabella log con i campi selezionati dall'utente
    createTable(db, "log", current_row);
    // Poi mi scollego
    db.finish();
}