#include "compiler.h"
#include "shared.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

const char* ASM_START = "_asm/x86_64_start.s";
const char* ASM_END = "_asm/x86_64_end.s";
const char* RISCV_START = "_asm/riscv_start.s";
const char* RISCV_END = "_asm/riscv_end.s";

void write_inst_asm_x64(FILE* output, const Inst* inst) {
    switch(inst->kind) {
    case IncrPtr:
        fprintf(output, "\n\tadd r12, %zu\n", inst->times);
        break;
    case DecrPtr:
        fprintf(output, "\n\tsub r12, %zu\n", inst->times);
        break;
    case IncrByte:
        fprintf(output, "\n\taddb [r12], %zu\n", inst->times);
        break;
    case DecrByte:
        fprintf(output, "\n\tsubb [r12], %zu\n", inst->times);
        break;
    case ReadByte:
        for(size_t i = 0; i < inst->times; i++) {
            fprintf(output, "\n\tmov rax, SYS_READ\n"
                            "\tmov rdi, STDIN\n"
                            "\tmov rsi, r12\n"
                            "\tmov rdx, 1\n"
                            "\tsyscall\n");
        }
        break;
    case WriteByte:
        for(size_t i = 0; i < inst->times; i++) {
            fprintf(output, "\n\tmov rax, SYS_WRITE\n"
                            "\tmov rdi, STDOUT\n"
                            "\tmov rsi, r12\n"
                            "\tmov rdx, 1\n"
                            "\tsyscall\n");
        }
        break;
    case LoopStart:
        fprintf(output,
                "\n\tcmpb [r12], 0\n"
                "\tje LOOP_END_%zu\n"
                "\n\tLOOP_START_%zu:\n",
                inst->end_idx - 1, inst->idx);
        break;
    case LoopEnd:
        fprintf(output,
                "\n\tcmpb [r12], 0\n"
                "\tjne LOOP_START_%zu\n"
                "\n\tLOOP_END_%zu:\n",
                inst->start_idx - 1, inst->idx);
        break;
    }
}

void write_inst_riscv_asm(FILE* output, const Inst* inst) {
    switch(inst->kind) {
    case IncrPtr:
        fprintf(output, "\n\taddi s2, s2, %zu\n", inst->times);
        break;
    case DecrPtr:
        fprintf(output, "\n\taddi s2, s2, -%zu\n", inst->times);
        break;
    case IncrByte:
        fprintf(output,
                "\n\tlb t0, 0(s2)\n"
                "\taddi t0, t0, %zu\n"
                "\tsb t0, 0(s2)\n",
                inst->times);
        break;
    case DecrByte:
        fprintf(output,
                "\n\tlb t0, 0(s2)\n"
                "\taddi t0, t0, -%zu\n"
                "\tsb t0, 0(s2)\n",
                inst->times);
        break;
    case ReadByte:
        for(size_t i = 0; i < inst->times; i++) {
            fprintf(output, "\n\tli a7, SYS_READ\n"
                            "\tli a0, STDIN\n"
                            "\tmv a1, s2\n"
                            "\tli a2, 1\n"
                            "\tecall\n");
        }
        break;
    case WriteByte:
        for(size_t i = 0; i < inst->times; i++) {
            fprintf(output, "\n\tli a7, SYS_WRITE\n"
                            "\tli a0, STDOUT\n"
                            "\tmv a1, s2\n"
                            "\tli a2, 1\n"
                            "\tecall\n");
        }
        break;
    case LoopStart:
        fprintf(output,
                "\n\tlb t0, 0(s2)\n"
                "\tbeqz t0, LOOP_END_%zu\n"
                "\nLOOP_START_%zu:\n",
                inst->end_idx - 1, inst->idx);
        break;
    case LoopEnd:
        fprintf(output,
                "\n\tlb t0, 0(s2)\n"
                "\tbnez t0, LOOP_START_%zu\n"
                "\nLOOP_END_%zu:\n",
                inst->start_idx - 1, inst->idx);
        break;
    }
}

void compile_x64(Program* prog, FILE* output) {
    char* asm_start = read_file(ASM_START);
    char* asm_end = read_file(ASM_END);
    fprintf(output, "%s", asm_start);

    for(size_t i = 0; i < prog->size; i++) {
        write_inst_asm_x64(output, &prog->instructions[i]);
    }

    fprintf(output, "%s", asm_end);
}

void compile_riscv(Program* prog, FILE* output) {
    char* riscv_start = read_file(RISCV_START);
    char* riscv_end = read_file(RISCV_END);
    fprintf(output, "%s", riscv_start);

    for(size_t i = 0; i < prog->size; i++) {
        write_inst_riscv_asm(output, &prog->instructions[i]);
    }

    fprintf(output, "%s", riscv_end);
}

int parse_and_compile(const char* source, char* filename, bool is_riscv) {
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
    /* return 1; */

    char out_filepath[256];
    strcpy(out_filepath, "out/");
    strcat(out_filepath, filename);
    if(is_riscv) {
        strcat(out_filepath, "_riscv");
    } else {
        strcat(out_filepath, "_x86");
    }
    strcat(out_filepath, ".s");
    FILE* output = fopen(out_filepath, "w");
    if(!output) {
        fprintf(stderr, "Error opening output file:\n");
        return 1;
    }

    if(is_riscv) {
        compile_riscv(prog, output);
    } else {
        compile_x64(prog, output);
    }

    fclose(output);

    return 0;
}
