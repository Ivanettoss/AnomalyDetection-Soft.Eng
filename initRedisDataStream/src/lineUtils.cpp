#include "main.h"

void buildLine(char* buffer, std::vector<std::string>& fields){
    char *token = strtok(buffer, ";");
    while (token)
    {
        // Pushiamo dentro al vettore fields i token uno per uno, ovvero i values dei diversi campi per ogni entry
        fields.push_back(token);
        token = strtok(nullptr, ";");
    }
    while (!fields.empty() && fields.back().empty()) {
        fields.pop_back();
    }
}

void printLine(std::vector<std::string> fields){
    std::string row = "";
    for (const auto &field : fields)
    {  
        row += field + " ";
    }
    std::cout << row << std::endl;    
}

int findDomain(std::vector<std::string>& fields, std::string comp) {
    for (size_t i = 0; i < fields.size(); ++i) {
        if (fields[i] == comp) {
            return i; // Restituisci l'indice se la stringa è stata trovata
        }
    }
    return -1; // Restituisci -1 se la stringa non è stata trovata
}

void readLine(char* buffer, int buffer_size, FILE* file){
    fgets(buffer, buffer_size, file);
    buffer[strcspn(buffer, "\n")] = '\0';
}

char* stringToChar(std::string str){
    char* converted = new char[str.length() + 1];
    strcpy(converted, str.c_str());
    return converted;
}