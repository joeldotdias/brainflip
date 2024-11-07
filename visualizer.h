#include "parser.h"
#include <stdint.h>

typedef uint8_t u8;

#define ANSI_CLEAR "\033[2J\033[H"
#define ANSI_RESET "\033[0m"
#define ANSI_BLUE "\033[34m"
#define ANSI_BOLD_GREEN "\033[1;32m"

typedef struct {
    size_t width;
    size_t offset;
    unsigned char* tape;
    size_t tape_size;
    size_t tape_ptr;

} Visualizer;

typedef enum {
    Eval_IOError,
    Eval_PtrBelowZero,
    Eval_PtrAboveLimit,
    Eval_OK,
} EvalErr;

int visualize(const char* source);
