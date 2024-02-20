#include <iostream>
#include "con2db/pgsql.h"
#include <vector>
using namespace std;
int main(){

Con2DB db1 ("localhost","5432","ivanetto","ivanetto","Movies");

vector<vector<string>>Matrix{
    {"Film","Regista","Genere","Durata"},
    {"Dune","Villanueve","Fantasy","240min"},
    {"8 1/2","Fellini","Dramma","180min"}};

int ncolumn=Matrix[0].size();
int nraws=Matrix.size();


//first row cycle: columns name
for (int i=0; i<ncolumn;i++)
{
   string columnName=Matrix[0][i];
    string columns=addColumns(columnName);
}

string createQuery=createTable(columns);
ExecSQLcmd(createQuery); //executes the query

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



for (int i=1; i<nraws;i++)
{
    string rawToInsert=Matrix[i];
    string raws=buildRaws(rawToInsert);
}

string insertQuery=insertInTo(raws);
ExecSQLcmd(insertQuery);//executes the query


string buildRaws(string Raw){
    string raws=raws+"("+Raw+"),";
    return raws;
}
string insertInTo(string raws ){
    string query= "INSERT INTO Movie("+Matrix[0]+")"+"VALUES"+raws+";"
    return query;
}


return 0;

}
// void Create Table
// void InsertQuery(vector<vector<string>>Matrix, Con2DB db1){
 
  
  



