#include "memory.c"

void registers(uint, uint, uint, uint, uint);

typedef struct Instruction {
    uint opcode;
    uint rs;
    uint rt;
    uint rd;
    uint shamt;
    uint func;
    uint imm;
}Instruction;

// This struct basically represents the signals that get produced
// by the instruction when the opcode gets inserted in Control.
typedef struct Signals {
    bool reg_dst;
    bool reg_write;
    bool alu_src;
    bool alu_op1;
    bool alu_op0;
    bool branch;
    bool mem_write;
    bool mem_read;
    bool mem_to_reg;
}Signals;


Instruction* decode_instruction(uint32_t);

Instruction* decode_instruction(uint32_t val){
    Instruction* instruction = (Instruction*) malloc(sizeof(Instruction));
    instruction->opcode = get_opcode(val);
    instruction->rs = get_rs(val);
    instruction->rd = get_rs(val);
    instruction->rt = get_rs(val);
    instruction->shamt = get_shamt(val);
    instruction->func = get_func(val);
    instruction->imm = get_imm(val);
    return instruction;
}

Signals* control_unit(uint opcode){
    Signals* signals = malloc(sizeof(Signals));
    switch (find_instruction_type(opcode)) {
        case RType:
            // R-format 1 0 0 1 0 0 0 1 0
            signals->reg_dst = true;
            signals->alu_src = false;
            signals->mem_to_reg = false;
            signals->reg_write = true;
            signals->mem_read = false;
            signals->mem_write = false;
            signals->branch = false;
            signals->alu_op0 = false;
            signals->alu_op1 = true;
            break;
        case IType:
            break;
        case JType:
            break;
    }
    return signals;
}

void registers(uint rd_reg1, uint rd_reg2, uint wr_reg, uint wr_en, uint wr_data){

}

//
//static uint32_t find_opcode(uint32_t opcode){
////    switch (opcode) {
////        case
////    }
//}
//
//static void execute_RType(uint32_t val){
//    uint32_t rs = get_rs(val);
//    uint32_t rt = get_rt(val);
//    uint32_t rd = get_rd(val);
//    uint32_t shamt = get_shamt(val);
//    uint32_t func = get_func(val);
//}
//
//static void execute_IType(uint32_t val){
//    uint32_t opcode = get_opcode(val);
//    uint32_t rs = get_rs(val);
//    uint32_t rt = get_rt(val);
//    uint32_t imm = get_imm(val);
//}
//
//static void execute_JType(uint32_t val){
//    uint32_t opcode = get_opcode(val);
//    uint32_t imm = get_imm(val);
//}
