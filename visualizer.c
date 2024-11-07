#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "visualizer.h"

#define MEM_CAPACITY 30000
#define DELAY 200000

Visualizer* init_Visualizer(Visualizer* v, unsigned char* tape, size_t tape_size,
                            size_t width) {
    v->tape = tape;
    v->tape_size = tape_size;
    v->width = width;
    v->tape_ptr = 0;

    return v;
}

void update_offset(Visualizer* v) {
    // adjusting the offset to keep pointer visible on the screen
    if(v->tape_ptr < v->offset) {
        v->offset = v->tape_ptr;
    } else if(v->tape_ptr >= v->offset + v->width) {
        v->offset = v->tape_ptr - v->width + 1;
    }
}

void draw_visualier(Visualizer* v, char* out_buf) {
    update_offset(v);

    printf(ANSI_CLEAR);

    // top border
    printf("┌");
    for(size_t i = 0; i < v->width; i++) {
        printf("───");
        if(i < v->width - 1)
            printf("┬");
    }
    printf("┐\n");

    // cells
    printf("│");
    // cell indices
    for(size_t i = 0; i < v->width && (i + v->offset) < v->tape_size; i++) {
        printf("%3zu", i + v->offset);
        if(i < v->width - 1)
            printf("│");
    }
    printf("│\n");

    // cell values --> '.' if it is empty
    // bold green makes the . jump up when cell is highlighted
    // great success
    printf("│");
    for(size_t i = 0; i < v->width && (i + v->offset) < v->tape_size; i++) {
        if(i + v->offset == v->tape_ptr) {
            printf(ANSI_BOLD_GREEN);
        }

        char c = v->tape[i + v->offset];
        if(c >= 32 && c <= 126) {
            printf(" %c ", c);
        } else {
            printf(" · ");
        }

        printf(ANSI_RESET);
        if(i < v->width - 1)
            printf("│");
    }
    printf("│\n");

    // bottom border
    printf("└");
    for(size_t i = 0; i < v->width; i++) {
        printf("───");
        if(i < v->width - 1)
            printf("┴");
    }
    printf("┘\n");

    // pointer indicator
    size_t rel_pos = v->tape_ptr - v->offset;
    for(size_t i = 0; i < rel_pos; i++) {
        printf("    ");
    }
    printf(ANSI_BLUE "  ▲" ANSI_RESET "\n");

    printf("\nPointer: %zu  Value: %d  ASCII: ", v->tape_ptr, v->tape[v->tape_ptr]);
    if(v->tape[v->tape_ptr] >= 32 && v->tape[v->tape_ptr] <= 126) {
        printf("'%c'", v->tape[v->tape_ptr]);
    } else {
        printf("n/a");
    }

    // buffer contents
    // every byte written is stored here
    printf("\nBuffer: %s", out_buf);
    fflush(stdout);
    printf("\n");
}

EvalErr eval(Program* prog) {
    unsigned char memory[MEM_CAPACITY] = {0};
    size_t mem_ptr = 0;
    size_t inst_ptr = 0;
    char out_buffer[1024];
    size_t out_idx = 0;

    Visualizer viz;
    init_Visualizer(&viz, memory, MEM_CAPACITY, 16);

    while(inst_ptr < prog->size) {
        Inst* curr_inst = &prog->instructions[inst_ptr];

        viz.tape_ptr = mem_ptr;
        draw_visualier(&viz, out_buffer);
        usleep(DELAY);

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
            // saving the cursor position before printing
            /* printf("\033[s"); */

            for(size_t i = 0; i < curr_inst->times; i++) {
                /* if(fputc(memory[mem_ptr], stdout) == EOF) { */
                /*     return Eval_IOError; */
                /* } */
                out_buffer[out_idx] = memory[mem_ptr];
                out_idx++;
            }

            // restoring the cursor position after printing
            /* printf("\033[u"); */

            inst_ptr++;
            break;

        case ReadByte:
            fflush(stdout);
            // probably might have to move to bottom of screen for input
            // also might not be a good idea
            printf("\033[%zu;0H", viz.width + 10);

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

int visualize(const char* source) {
    Program* prog = init_program();

    ParseErr result = parse(source, prog);
    if(result.kind != Parse_OK) {
        fprintf(stderr, "Parser Error: %s", result.message);
        return 1;
    }

    /* for(size_t i = 0; i < prog->size; i++) { */
    /*     print_instruction(&prog->instructions[i]); */
    /* } */
    /* printf("\nInstructions: %zu\n", prog->size); */

    EvalErr eval_res = eval(prog);
    if(eval_res != Eval_OK) {
        fprintf(stderr, "Eval Error: %s", run_err_message(eval_res));
        return 1;
    }

    return 0;
}
