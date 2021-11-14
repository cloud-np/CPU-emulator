#include <stdio.h>
#include <stdbool.h>
#include "parse_mips.h"
#include "mips.h"
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

#ifdef DEBUG
        switch (curr_block->type) {
            case RType:
                MAGENTA;
                printf("\nR]");
                printf(" op\trs\t  rt    rd\t shamt\tfunc\n");
                WHITE;
                break;
            case IType:
                ORANGE;
                printf("\nI]");
                printf(" op\trs\t  rt    \timm\n");
                WHITE;
                break;
            case JType:
                CYAN;
                printf("\nJ]");
                printf(" op  \t\t\timm\n");
                WHITE;
                break;
            case NoneType:
                perror("Can't be NoneType");
                exit(-1);
        }
        print_to_bin(curr_block);
#endif
        // Decode the instruction.
        Instruction* instruction = decode_instruction(curr_block->val);

        // Pass the opcode IR[31-26] to the control unit.
        // Supports R-Format commands for now.
        Signals* signals = control_unit(instruction->opcode);

        // ALU control.
//        alu_control();

        // ALU.
//        ALU();

        // Data memory.

        if (mips_state->pc == memory->len)
            cpu_is_running = 0;

        // For now this is a single cycle CPU.
        // Otherwise, we would keep some parts.
        free(instruction);
        free(signals);
    }
    free_memory(memory);

    return 0;
}

//        printf("op: %d\n", opcode);
//        printf("rs: %d\n", rs);
//        printf("rt: %d\n", rt);
//        printf("shamt: %d\n", shamt);
//        printf("func: %d\n", func);
//        printf("rd: %d\n", rd);
//        printf("imm: %d\n", imm);
