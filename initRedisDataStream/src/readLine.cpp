#include "main.h"

void readLine(char* buffer, int buffer_size, FILE* file){
    fgets(buffer, buffer_size, file);
    buffer[strcspn(buffer, "\n")] = '\0';
}