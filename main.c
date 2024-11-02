#include <stdio.h>

#include "interpreter.h"
#include "shared.h"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Wrong usage");
        return 1;
    }

    char* source = read_file(argv[1]);
    run(source);

    return 0;
}
