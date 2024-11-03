#include "interpreter.h"
#include <stdio.h>

int parse_and_compile(const char* source, char* filename);
void compile(Program* prog, FILE* output);
