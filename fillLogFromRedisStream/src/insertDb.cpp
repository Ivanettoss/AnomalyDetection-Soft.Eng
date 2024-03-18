#include "main.h"
#include "sstream"

vector<string> split(const string &input)
{
    vector<string> risultato;
    istringstream iss(input);
    string token;
    while (getline(iss, token, ' '))
    {
        replace(token.begin(), token.end(), ',', '.');
        risultato.push_back(token);
    }
    return risultato;
}

int insertDb(Con2DB db, vector<string> fields, string tableName, string data)
{
    // devo fare l'operazione di insert del dato che ho letto
    // INSERT INTO log (campo1, campo2, campo3) VALUES ('valore1', 'valore2', 'valore3');
    string query = "INSERT INTO " + tableName + " (";
    for (size_t i = 0; i < fields.size() - 1; i++)
    {
        query += "\"" + fields[i] + "\"" + ", ";
    }
    query += "\"" + fields[fields.size() - 1] + "\"" + ")" + " VALUES (";
    vector<string> dataSplit = split(data);

    // checkSum
    if (dataSplit.size() != fields.size())
    {
        return -100;
    }

    for (size_t i = 0; i < dataSplit.size() - 1; i++)
    {
        query += "\'" + dataSplit[i] + "\', ";
    }
    query += "\'" + dataSplit[dataSplit.size() - 1] + "\'" + ");";

    //cout << query << endl;
    db.ExecSQLcmd(stringToChar(query));

    return 0;
}