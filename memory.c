#include "memory.h"
#include <stdio.h>
#include <stdlib.h>

unsigned int int_to_bin(unsigned int k) {
    return (k == 0 || k == 1 ? k : ((k % 2) + 10 * int_to_bin(k / 2)));
}

unsigned int test(){
    unsigned int val = 0;
    val = (val | LW_OPCODE) << 26;
    printf("op?: %u\n", val);
    printf("opcode: %d\n", val >> 26);
//    printf("opcode: %d\n", val >> 25);
    return 19;
}

CmdType find_instruction_type(uint32_t opcode){
    switch (opcode) {
        case lw:
        case sw:
        case addi:
        case slti:
        case bne:
        case beq:
            return IType;
        case j:
        case jal:
            return JType;
        case add:
        case sub:
        case slt:
        case jr:
        case jalr:
        case nor:
        case _break:
            return RType;
        default:
            return -1;
    }
}

uint32_t get_opcode(uint32_t val){
    return MID(val, 26, 31);
}

void set_opcode(Commands cmd, MemoryBlock* memory_block){
    unsigned int val = 0;
    switch (cmd) {
        case lw:
            memory_block->val = memory_block->val | (LW_OPCODE << 26);
            break;
        case sw:
            memory_block->val = memory_block->val | (SW_OPCODE << 26);
            break;
        case add:
        case sub:
        case slt:
        case nor:
        case jr:
        case jalr:
        case _break:
            memory_block->val = memory_block->val | (RTYPE_OPCODE << 26);
            break;
        case beq:
            memory_block->val = memory_block->val | (BEQ_OPCODE << 26);
            break;
        case bne:
            memory_block->val = memory_block->val | (BNE_OPCODE << 26);
            break;
        case addi:
            memory_block->val = memory_block->val | (ADDI_OPCODE << 26);
            break;
        case slti:
            memory_block->val = memory_block->val | (SLTI_OPCODE << 26);
            break;
        case j:
            memory_block->val = memory_block->val | (J_OPCODE << 26);
            break;
        case jal:
            memory_block->val = memory_block->val | (JAL_OPCODE << 26);
            break;
        default:
            perror("Wrong opcode in set_opcode.\n");
            exit(-1);
    }
}

void set_target(unsigned int target, MemoryBlock* memory_block){
    memory_block->val |= target;
}

void set_addr(unsigned int addr, MemoryBlock* memory_block){
    memory_block->val |= (addr << 20);
}

unsigned int get_func(unsigned int val){
    return MID(val, 0, 6);
}

void set_func(Commands cmd, MemoryBlock* memory_block){
    switch (cmd) {
        case add:
            memory_block->val |= ADD_FUNC_CODE;
            break;
        case sub:
            memory_block->val |= SUB_FUNC_CODE;
            break;
        case slt:
            memory_block->val |= SLT_FUNC_CODE;
            break;
        case nor:
            memory_block->val |= NOR_FUNC_CODE;
            break;
        case jr:
            memory_block->val |= JR_FUNC_CODE;
            break;
        case jalr:
            memory_block->val |= JALR_FUNC_CODE;
            break;
        case _break:
            memory_block->val |= BREAK_FUNC_CODE;
            break;
        default:
            perror("Not supported R-Type cmd or wrong call of set_func.\n");
            exit(-1);
    }
}

uint32_t get_rs(uint32_t val){
    return MID(val, 21, 25);
}

void set_rs(unsigned int rs, MemoryBlock* memory_block){
    memory_block->val |= (rs << 21);
}

uint32_t get_rt(uint32_t val){
    return MID(val, 16, 20);
}

void set_rt(unsigned int rt, MemoryBlock* memory_block){
    memory_block->val |= (rt << 16);
}

uint32_t get_imm(uint32_t val){
    return MID(val, 0, 15);
}

void set_imm(int imm, MemoryBlock* memory_block){
    memory_block->val |= imm;
}

uint32_t get_rd(uint32_t val){
    return MID(val, 11, 15);
}

void set_rd(unsigned int rd, MemoryBlock* memory_block){
    memory_block->val |= rd << 11;
}

uint32_t get_shamt(uint32_t val){
    return MID(val, 0, 6);
}

void set_shamt(unsigned int shamt, MemoryBlock* memory_block){
    memory_block->val |= (shamt << 6);
}
