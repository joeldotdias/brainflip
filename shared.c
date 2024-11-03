#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

char* extract_filename(const char* filepath) {
    if(!filepath)
        return NULL;

    const char* filename_start = filepath;
    const char* last_slash = strrchr(filepath, '/');
    const char* last_backslash = strrchr(filepath, '\\');

    if(last_slash && (!last_backslash || last_slash > last_backslash)) {
        filename_start = last_slash + 1;
    } else if(last_backslash) {
        filename_start = last_backslash + 1;
    }

    const char* dot = strrchr(filename_start, '.');

    size_t length;
    if(dot) {
        length = dot - filename_start;
    } else {
        length = strlen(filename_start);
    }

    char* result = (char*)malloc(length + 1);
    if(!result)
        return NULL;

    strncpy(result, filename_start, length);
    result[length] = '\0';

    return result;
}
