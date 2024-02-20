#include <iostream>
#include <vector>
#include <cstring>
#include "con2db/pgsql.h"

using namespace std;

string buildRaws(string Raw){
    string raws=raws+"("+Raw+"),";
    return raws;
}
string insertInTo(string raws, string flag ){
    string query= "INSERT INTO Movie("+flag+")"+"VALUES"+raws+";";
    return query;
}

// we create the columns string that we want add in the table
string addColumns(string columnName){
    string columns=columns+columnName+"varchar(50),";
    return columns;
}

//we create the entire query 
string createTable(string columns){
    string query="CREATE TABLE IF NOT EXIST Movie ( ";
    query=query + columns+");";
    return query;
}

int main(){

Con2DB db1 ("localhost","5432","ivanetto","ivanetto","Movies");

vector<vector<string>>Matrix{
    {"Film","Regista","Genere","Durata"},
    {"Dune","Villanueve","Fantasy","240min"},
    {"8 1/2","Fellini","Dramma","180min"}};

int ncolumns=Matrix[0].size();
int nraws=Matrix.size();

string columns;
string columnName;

//first row cycle: columns name
for (int i=0; i<ncolumns;i++)
{
    columnName=Matrix[0][i];
    columns=addColumns(columnName);
}

string createQuery=createTable(columns);

// Allocazione di un array di caratteri
    char charQuery[createQuery.length() + 1]; // +1 per il terminatore null

    // Copia della stringa in charQuery
    strcpy(charQuery, createQuery.c_str());

db1.ExecSQLcmd(charQuery); //executes the query


string rawToInsert;
string raws;

for (int i=1; i<nraws;i++)
{
    rawToInsert = "";
    for (int j = 0; j < ncolumns; j++){
        rawToInsert += Matrix[i][j] + " ";
    }
    raws=buildRaws(rawToInsert);
}

string flag = "";
for (int i = 0; i < ncolumns; i++){
    flag += Matrix[0][i] + " ";
}

string insertQuery=insertInTo(raws, flag);

// Allocazione di un array di caratteri
    charQuery[insertQuery.length() + 1]; // +1 per il terminatore null

    // Copia della stringa in charQuery
    strcpy(charQuery, insertQuery.c_str());

db1.ExecSQLcmd(charQuery);//executes the query



return 0;

}
// void Create Table
// void InsertQuery(vector<vector<string>>Matrix, Con2DB db1){
 
  
  



