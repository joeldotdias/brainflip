#include <stdio.h>

#include "parser.h"
#include "shared.h"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Wrong usage");
        return 1;
    }

    char* source = read_file(argv[1]);
    Program* prog = init_program();

    ParseErr result = parse(source, prog);
    if(result.kind != Parse_OK) {
        fprintf(stderr, "%s", result.message);
        return 1;
    }

    for(size_t i = 0; i < prog->size; i++) {
        print_instruction(&prog->instructions[i]);
    }

    return 0;
}
