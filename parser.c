#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

const char INSTS[] = {'>', '<', '+', '-', '.', ',', '[', ']'};

Inst make_inst(size_t idx, char ch) {
    Inst inst = {.idx = idx, .times = 1};

    switch(ch) {
    case '>':
        inst.kind = IncrPtr;
        break;
    case '<':
        inst.kind = DecrPtr;
        break;
    case '+':
        inst.kind = IncrByte;
        break;
    case '-':
        inst.kind = DecrByte;
        break;
    case '.':
        inst.kind = WriteByte;
        break;
    case ',':
        inst.kind = ReadByte;
        break;
    case '[':
        inst.kind = LoopStart;
        break;
    case ']':
        inst.kind = LoopEnd;
        break;
    }

    return inst;
}

Program* init_program() {
    Program* arr = malloc(sizeof(Program));
    arr->instructions = malloc(sizeof(Inst) * INITIAL_ARR_CAPACITY);
    arr->size = 0;
    arr->capacity = INITIAL_ARR_CAPACITY;
    return arr;
}

void push_inst(Program* arr, Inst inst) {
    if(arr->size >= arr->capacity) {
        arr->capacity *= 2;
        arr->instructions = realloc(arr->instructions, sizeof(Inst) * arr->capacity);
    }

    arr->instructions[arr->size++] = inst;
}

Inst* last_inst(Program* arr) {
    return arr->size > 0 ? &arr->instructions[arr->size - 1] : NULL;
}

void free_prog(Program* arr) {
    free(arr->instructions);
    free(arr);
}

ParseErr make_error(ErrKind kind) {
    ParseErr err = {.kind = kind};
    err.message = malloc(MAX_ERROR_MSG_LEN);

    switch(kind) {
    case PtrBelowZero:
        snprintf(err.message, MAX_ERROR_MSG_LEN, "error: mem pointer went below zero");
        break;
    case PtrAboveLimit:
        snprintf(err.message, MAX_ERROR_MSG_LEN, "error: mem pointer went above limit %d",
                 ARR_LEN);
        break;
    case UnbalancedBrackets:
        snprintf(err.message, MAX_ERROR_MSG_LEN,
                 "error: unbalanced brackets in bf source");
        break;
    case InfiniteLoop:
        snprintf(err.message, MAX_ERROR_MSG_LEN,
                 "error: potential infinite loop in bf source");
        break;
    case Parse_OK:
        break;
    }

    return err;
}

ParseErr parse(const char* src, Program* prog) {
    size_t loop_depth = 0;

    for(const char* ch = src; *ch != '\0'; ch++) {
        // comment
        if(strchr(INSTS, *ch) == NULL) {
            continue;
        }

        if(*ch == ']') {
            if(loop_depth == 0) {
                free_prog(prog);
                return make_error(UnbalancedBrackets);
            }

            loop_depth--;
        } else if(*ch == '[') {
            loop_depth++;
        }

        Inst curr_inst = make_inst(prog->size, *ch);
        Inst* prev_inst = last_inst(prog);

        if(prev_inst && prev_inst->kind == curr_inst.kind) {
            prev_inst->times++;
        } else {
            push_inst(prog, curr_inst);
        }
    }

    if(loop_depth > 0) {
        free_prog(prog);
        return make_error(UnbalancedBrackets);
    }

    for(size_t i = 0; i < prog->size; i++) {
        Inst* curr_inst = &prog->instructions[i];

        if(curr_inst->kind == LoopStart) {
            size_t loop_starts = curr_inst->times;
            size_t j;
            for(j = i + 1; j < prog->size; j++) {
                Inst* scan_inst = &prog->instructions[j];

                if(scan_inst->kind == LoopEnd) {
                    // "saturating" subtraction
                    if(loop_starts > scan_inst->times) {
                        loop_starts -= scan_inst->times;
                    } else {
                        loop_starts = 0;
                    }

                    if(loop_starts == 0) {
                        curr_inst->end_idx = j + 1;
                        break;
                    }
                } else if(scan_inst->kind == LoopStart) {
                    loop_starts += scan_inst->times;
                }
            }
        } else if(curr_inst->kind == LoopEnd) {
            size_t loop_ends = 1;
            size_t j;

            // find matching loop start
            for(j = i; j > 0; j--) {
                Inst* scan_inst = &prog->instructions[j - 1];

                if(scan_inst->kind == LoopStart) {
                    // Use saturating subtraction
                    if(loop_ends > scan_inst->times) {
                        loop_ends -= scan_inst->times;
                    } else {
                        loop_ends = 0;
                    }

                    if(loop_ends == 0) {
                        if(i == j) {
                            free_prog(prog);
                            return make_error(InfiniteLoop);
                        }
                        curr_inst->start_idx = j;
                        break;
                    }
                } else if(scan_inst->kind == LoopEnd) {
                    loop_ends += scan_inst->times;
                }
            }
        }
    }

    return (ParseErr){.kind = Parse_OK};
}

const char* inst_kind_to_string(InstKind kind) {
    switch(kind) {
    case IncrPtr:
        return "IncrPtr";
    case DecrPtr:
        return "DecrPtr";
    case IncrByte:
        return "IncrByte";
    case DecrByte:
        return "DecrByte";
    case WriteByte:
        return "WriteByte";
    case ReadByte:
        return "ReadByte";
    case LoopStart:
        return "LoopStart";
    case LoopEnd:
        return "LoopEnd";
    default:
        return "Unknown";
    }
}
void print_instruction(const Inst* inst) {
    printf("{Type: %s, Times: %zu", inst_kind_to_string(inst->kind), inst->times);

    // jump targets for loops
    if(inst->kind == LoopStart) {
        printf(", JumpEnd: %zu", inst->end_idx);
    } else if(inst->kind == LoopEnd) {
        printf(", JumpStart: %zu", inst->start_idx);
    }
    printf("}\n");
}
