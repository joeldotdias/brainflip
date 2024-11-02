#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "interpreter.h"

#define MEM_CAPACITY 30000

EvalErr eval(Program* prog) {
    unsigned char memory[MEM_CAPACITY] = {0};
    size_t mem_ptr = 0;
    size_t inst_ptr = 0;

    while(inst_ptr < prog->size) {
        Inst* curr_inst = &prog->instructions[inst_ptr];

        switch(curr_inst->kind) {
        case IncrPtr:
            if(mem_ptr + curr_inst->times >= ARR_LEN) {
                return Eval_PtrAboveLimit;
            }
            mem_ptr += curr_inst->times;
            inst_ptr++;
            break;

        case DecrPtr:
            if(curr_inst->times > mem_ptr) {
                return Eval_PtrBelowZero;
            }
            mem_ptr -= curr_inst->times;
            inst_ptr++;
            break;

        case IncrByte:
            memory[mem_ptr] += curr_inst->times;
            inst_ptr++;
            break;

        case DecrByte:
            memory[mem_ptr] -= curr_inst->times;
            inst_ptr++;
            break;

        case WriteByte:
            for(size_t i = 0; i < curr_inst->times; i++) {
                if(fputc(memory[mem_ptr], stdout) == EOF) {
                    return Eval_IOError;
                }
            }
            inst_ptr++;
            break;

        case ReadByte:
            fflush(stdout);
            for(size_t i = 0; i < curr_inst->times; i++) {
                int ch = fgetc(stdin);
                memory[mem_ptr] = (ch == EOF) ? EOF_CHAR : (unsigned char)ch;
            }
            inst_ptr++;
            break;

        case LoopStart:
            if(memory[mem_ptr] == 0) {
                inst_ptr = curr_inst->end_idx;
            } else {
                inst_ptr++;
            }
            break;

        case LoopEnd:
            if(memory[mem_ptr] != 0) {
                inst_ptr = curr_inst->start_idx;
            } else {
                inst_ptr++;
            }
            break;
        }
    }

    return Eval_OK;
}

char* run_err_message(EvalErr err) {
    char* msg = NULL;

    switch(err) {
    case Eval_PtrBelowZero:
        msg = "Memory pointer reached below zero";
        break;
    case Eval_PtrAboveLimit:
        msg = "Memory pointer went above limit";
        break;
    case Eval_IOError:
        msg = "IO operation failed";
        break;
    case Eval_OK:
        break;
    }

    return msg;
}

int run(const char* source) {
    Program* prog = init_program();

    ParseErr result = parse(source, prog);
    if(result.kind != Parse_OK) {
        fprintf(stderr, "Parser Error: %s", result.message);
        return 1;
    }

    EvalErr eval_res = eval(prog);
    if(eval_res != Eval_OK) {
        fprintf(stderr, "Eval Error: %s", run_err_message(eval_res));
        return 1;
    }

    return 0;
}
