#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "compiler.h"
#include "shared.h"

int main(int argc, char* argv[]) {
    if(argc < 2) {
        fprintf(stderr, "Wrong usage");
        return 1;
    }

    char* source = read_file(argv[1]);
    /* run(source); */

    char* filename = extract_filename(argv[1]);
    bool is_riscv;
    if(argc == 2) {
        is_riscv = false;
    } else {
        if(strcmp(argv[2], "riscv") == 0) {
            is_riscv = true;
        }
    }

    parse_and_compile(source, filename, is_riscv);

    /* if(strcmp(argv[2], "riscv") == 0) { */
    /*     parse_and_compile_riscv(source, filename); */
    /* } else { */
    /*     parse_and_compile_x64(source, filename); */
    /* } */

    return 0;
}
