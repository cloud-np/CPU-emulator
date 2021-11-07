#include <stdint.h>
// I-Type opcodes
#define LW_OPCODE 0b100011
#define SW_OPCODE 0b101011
#define ADDI_OPCODE 0b001000
#define SLTI_OPCODE 0b001010
#define BEQ_OPCODE 0b000100
#define BNE_OPCODE 0b000101

// J-Type opcodes
#define J_OPCODE 0b000010
#define JAL_OPCODE 0b000011

// R-Type function codes
#define RTYPE_OPCODE 0b000000
#define ADD_FUNC_CODE 0b100000
#define SUB_FUNC_CODE 0b100010
#define SLT_FUNC_CODE 0b101010
#define JR_FUNC_CODE 0b001000
#define JALR_FUNC_CODE 0b001001
#define NOR_FUNC_CODE 0b100111
#define BREAK_FUNC_CODE 0b001101
#define ADDR_NULL 0x00000000
#define ADDR_INSTR 0x04000000 //0x10000000 / 4 = 0x4000000
#define ADDR_INSTR_L 0x00400000
#define ADDR_DATA 0x08000000
#define ADDR_DATA_L 0x01000000
#define ADDR_GETC 0x0C000000
#define ADDR_PUTC 0x0C000001
#define MEM_SIZE 0x0C000002
#define LAST(k,n) ((k) & ((1<<(n))-1))
#define MID(k,m,n) LAST((k)>>(m),((n)-(m)))
#define MEMORY_SIZE 10


typedef enum {IType, JType, RType, NoneType=-1} CmdType;
typedef enum {lw, sw, add, sub, addi, slt, slti, beq, bne, j, jr, jal, jalr, nor, _break} Commands;

typedef struct State {
    uint32_t pc;
    uint32_t npc;
    int reg[32];
}State;

typedef struct MemoryBlock {
    CmdType type;
    uint32_t val;
    Commands cmd;
    char* label;
    char* j_label;
}MemoryBlock;

typedef struct Memory {
    MemoryBlock** ram;
    size_t len;
}Memory;

static Memory* new_Memory(){
    Memory* memory = (Memory*) malloc(sizeof(Memory));
    memory->ram = (MemoryBlock**) malloc(sizeof(MemoryBlock*) * MEMORY_SIZE);
    return memory;
}

static MemoryBlock* new_MemoryBlock(){
    MemoryBlock* memory_block = (MemoryBlock*) malloc(sizeof(MemoryBlock));
    memory_block->type = NoneType;
    return memory_block;
}

static void free_memory(Memory* memory){
    for(int i = 0; i < memory->len; i++)
        free(memory->ram[i]);
}

static State* new_State(){
    State* state = (State*) malloc(sizeof(State));
    state->pc = 0;
    return state;
}

static void print_to_bin(MemoryBlock* mem){
    uint32_t n = mem->val;
    int k;
    for(int c = 31; c >= 0; c--) {
        k = n >> c;
        if(c == 25) printf(" ");
        if(mem->type == RType)
            if(c == 5 || c == 10 || c == 15 || c == 20)
                printf(" ");
        if(mem->type == IType)
            if(c == 15 || c == 20)
                printf(" ");

        k & 1 ? printf("1") : printf("0");
    }
}
