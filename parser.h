#include <stddef.h>

#define ARR_LEN 30000
#define NEWLINE 10
#define EOF_CHAR 0
#define MAX_ERROR_MSG_LEN 100
#define INITIAL_ARR_CAPACITY 1024

typedef enum {
    IncrPtr,
    DecrPtr,
    IncrByte,
    DecrByte,
    WriteByte,
    ReadByte,
    LoopStart,
    LoopEnd
} InstKind;

typedef struct {
    size_t idx;
    size_t times;
    InstKind kind;

    // for the loop start and end instruction kinds
    union {
        // used along with loop start
        // represents the index of inst after matching loop end
        size_t end_idx;

        // used along with loop end
        // represents the index of inst after matching loop start
        size_t start_idx;
    };
} Inst;

typedef enum {
    PtrBelowZero,
    PtrAboveLimit,
    UnbalancedBrackets,
    InfiniteLoop,
    // if everything works. probably not a good way to do this
    Parse_OK,
} ErrKind;

typedef struct {
    ErrKind kind;
    char* message;
} ParseErr;

typedef struct {
    Inst* instructions;
    size_t size;
    size_t capacity;
} Program;

Program* init_program();
ParseErr parse(const char* src, Program* prog);
void print_instruction(const Inst* inst);
const char* inst_kind_to_string(InstKind kind);
