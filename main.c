#include <stdio.h>
#include <string.h>

#include "compiler.h"
#include "shared.h"

int main(int argc, char* argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Wrong usage");
        return 1;
    }

    char* source = read_file(argv[1]);
    /* run(source); */

    char* filename = extract_filename(argv[1]);
    /* get_filename(argv[1], filename, sizeof(filename)); */

    parse_and_compile(source, filename);

    return 0;
}
