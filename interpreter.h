#include "parser.h"
#include <stdint.h>

typedef uint8_t u8;

typedef enum {
    Eval_IOError,
    Eval_PtrBelowZero,
    Eval_PtrAboveLimit,
    Eval_OK,
} EvalErr;

int run(const char* source);
