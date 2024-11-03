#include "compiler.h"
#include "shared.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

const char* ASM_START = "_asm/x86_64_start.s";
const char* ASM_END = "_asm/x86_64_end.s";

void write_inst_asm(FILE* output, const Inst* inst) {
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

void compile(Program* prog, FILE* output) {
    char* asm_start = read_file(ASM_START);
    char* asm_end = read_file(ASM_END);
    fprintf(output, "%s", asm_start);

    for(size_t i = 0; i < prog->size; i++) {
        write_inst_asm(output, &prog->instructions[i]);
    }

    /* fprintf(output, "%s", ASM_END); */
    fprintf(output, "%s", asm_end);
}

int parse_and_compile(const char* source, char* filename) {
    Program* prog = init_program();

    ParseErr result = parse(source, prog);
    if(result.kind != Parse_OK) {
        fprintf(stderr, "Parser Error: %s", result.message);
        return 1;
    }

    for(size_t i = 0; i < prog->size; i++) {
        print_instruction(&prog->instructions[i]);
    }
    /* printf("\nInstructions: %zu\n", prog->size); */

    char out_filepath[256];
    strcpy(out_filepath, "out/");
    strcat(out_filepath, filename);
    strcat(out_filepath, ".s");
    printf("%s", filename);
    /* snprintf(out_filepath, sizeof(filename), "out/%s.s", filename); */
    printf("%s", out_filepath);
    FILE* output = fopen(out_filepath, "w");
    if(!output) {
        fprintf(stderr, "Error opening output file:\n");
        return 1;
    }

    compile(prog, output);

    fclose(output);

    return 0;
}
