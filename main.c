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

    if(argc > 2 && strcmp(argv[2], "viz") == 0) {
        // for visualizer
        visualize(source);
    } else {
        // for compiler
        char* filename = extract_filename(argv[1]);
        bool is_riscv = false;
        if(argc > 2 && strcmp(argv[2], "riscv") == 0) {
            is_riscv = true;
        }

        parse_and_compile(source, filename, is_riscv);
    }

    return 0;
}
