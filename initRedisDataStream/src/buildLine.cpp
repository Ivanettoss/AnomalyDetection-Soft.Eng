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