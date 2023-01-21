#include "include/io.h"
#include <stdlib.h>
#include <stdio.h>

char* get_file(const char* path) {
    char* buffer = 0;
    long length;
    FILE* file = fopen(path, "rb");
    if(file) {
        fseek(file, 0, SEEK_END);
        length = ftell(file);
        fseek(file, 0, SEEK_SET);
        buffer = calloc(length, length);
        if(buffer) {
            fread(buffer, 1, length, file);
        } 
        fclose(file);
        return buffer;
    }
    printf("Error reading file path \"%s\"", path);
    exit(1);
}