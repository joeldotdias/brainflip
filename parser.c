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
    Program* prog = malloc(sizeof(Program));
    prog->instructions = malloc(sizeof(Inst) * INITIAL_ARR_CAPACITY);
    prog->size = 0;
    prog->capacity = INITIAL_ARR_CAPACITY;
    return prog;
}

void push_inst(Program* prog, Inst inst) {
    if(prog->size >= prog->capacity) {
        prog->capacity *= 2;
        prog->instructions = realloc(prog->instructions, sizeof(Inst) * prog->capacity);
    }

    prog->instructions[prog->size++] = inst;
}

Inst* last_inst(Program* prog) {
    return prog->size > 0 ? &prog->instructions[prog->size - 1] : NULL;
}

void free_prog(Program* prog) {
    free(prog->instructions);
    free(prog);
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

ParseErr parse(const char* src, Program* prog) {
    size_t loop_depth = 0;

    for(const char* ch = src; *ch != '\0'; ch++) {
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

        InstKind kind;
        switch(*ch) {
        case '+':
            kind = IncrByte;
            break;
        case '-':
            kind = DecrByte;
            break;
        case '>':
            kind = IncrPtr;
            break;
        case '<':
            kind = DecrPtr;
            break;
        case '.':
            kind = WriteByte;
            break;
        case ',':
            kind = ReadByte;
            break;
        case '[':
            kind = LoopStart;
            break;
        case ']':
            kind = LoopEnd;
            break;
        default:
            continue;
        }

        Inst curr_inst = {.kind = kind, .idx = prog->size, .times = 1, .start_idx = 0};

        // merge current inst with previous if they're the same
        Inst* prev_inst = last_inst(prog);
        if(prev_inst != NULL && prev_inst->kind == kind) {
            prev_inst->times++;
        } else {
            push_inst(prog, curr_inst);
        }
    }

    if(loop_depth > 0) {
        free_prog(prog);
        return make_error(UnbalancedBrackets);
    }

    // second pass: link the loops together
    for(size_t i = 0; i < prog->size; i++) {
        Inst* curr_inst = &prog->instructions[i];
        if(curr_inst->kind == LoopStart) {
            size_t loop_starts = curr_inst->times;
            for(size_t j = i + 1; j < prog->size; j++) {
                Inst* scan_inst = &prog->instructions[j];
                if(scan_inst->kind == LoopEnd) {
                    size_t loop_ends = scan_inst->times;
                    if(loop_starts <= loop_ends) {
                        loop_starts = 0;
                    } else {
                        loop_starts -= loop_ends;
                    }
                    if(loop_starts == 0) {
                        curr_inst->end_idx = j + 1;
                        scan_inst->start_idx = i + 1;
                        if(i == j - 1) {
                            free_prog(prog);
                            return make_error(InfiniteLoop);
                        }
                        break;
                    }
                } else if(scan_inst->kind == LoopStart) {
                    loop_starts += scan_inst->times;
                }
            }
        }
    }

    // oxymoronic return statement
    return (ParseErr){.kind = Parse_OK};
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
