#include <stdio.h>
#include <stdlib.h>

char* read_file(const char* path) {
    FILE* file = fopen(path, "r");
    if(!file) {
        fprintf(stderr, "Couldn't open %s'\n", path);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = malloc(size + 1);
    size_t bytes_read = fread(buffer, 1, size, file);
    buffer[bytes_read] = '\0';

    fclose(file);
    return buffer;
}
