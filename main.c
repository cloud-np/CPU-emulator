#include <stdio.h>
#include <stdbool.h>
#include "parse_mips.h"
//#include "mips.c"
#define DEBUG 1



int main() {
//    printf("Hello, World!\n");
    bool cpu_is_running = true;
    unsigned int clock = 0;
//    unsigned int PC = 0;
    State* mips_state = new_State();
    Memory* memory = read_file();

//        printf("%d\n");
//    for(int i = 0; i < memory->len; i++){
//        printf("\n%u\n", i);
//        print_to_bin(memory->instr_memory[i]);
//        printf("\ntype: %d\n", memory->instr_memory[i]->type);
//    }

    while(cpu_is_running){
        // Fetch the instruction
        MemoryBlock* curr_block = memory->instr_memory[mips_state->pc++];
//        unsigned int instruction = curr_block->val;

        // Decode the instruction
        switch (curr_block->type) {
            case RType:
#ifdef DEBUG
                MAGENTA;
                printf("\nR]");
                printf(" op\trs\t  rt    rd\t shamt\tfunc\n");
                WHITE;
#endif
//                execute_RType(instruction);
                break;
            case IType:
#ifdef DEBUG
                ORANGE;
                printf("\nI]");
                printf(" op\trs\t  rt    \timm\n");
                WHITE;
#endif
//                execute_IType(instruction);
                break;
            case JType:
#ifdef DEBUG
                CYAN;
                printf("\nJ]");
                printf(" op  \t\t\timm\n");
                WHITE;
#endif
//                execute_JType(instruction);
                break;
            case NoneType:
                perror("Can't be NoneType");
                exit(-1);
        }
        print_to_bin(curr_block);
//        printf("op: %d\n", opcode);
//        printf("rs: %d\n", rs);
//        printf("rt: %d\n", rt);
//        printf("shamt: %d\n", shamt);
//        printf("func: %d\n", func);
//        printf("rd: %d\n", rd);
//        printf("imm: %d\n", imm);

        if (mips_state->pc == memory->len)
            cpu_is_running = 0;
    }
    free_memory(memory);

    return 0;
}
