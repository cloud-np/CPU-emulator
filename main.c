#include <stdio.h>
#include <stdbool.h>
#include "parse_mips.h"



int main() {
//    printf("Hello, World!\n");
    bool cpu_is_running = 1;
    unsigned int clock = 0;
//    unsigned int PC = 0;
    State* mips_state = new_State();
    Memory* memory = read_file();

//        printf("%d\n");
    for(int i = 0; i < memory->len; i++){
        printf("\n%u\n", i);
        print_to_bin(memory->ram[i]);
    }

    while(cpu_is_running){
//        printf("Hello\n");
        unsigned int instruction = memory->ram[mips_state->pc++]->val;
        unsigned int opcode = get_opcode(instruction);
        switch (opcode) {
            case RType:
                break;
        }
        cpu_is_running = 0;
//        checkexec(mips_state.reg, mips_state.pc); //checks if the address is in the executable range
//        mips_state.reg[0] = 0;		//register $0 must retain the value zero in every new clock cycle of the processor
//        executed = false;		//every new clock cycle the flag is turned off since no instruction has yet been executed
//        tempnpc = mips_state.npc;	//since the instruction that will be executed will change the npc it needs to be stored
//
//        r_type(mips_state, executed);
//        i_type(mips_state, executed);
//        j_type(mips_state, executed);

//        if(!executed){			//if no instruction from the 3 types has executed at this stage (ie.false), then the binary must be invalid or an unknown error occurred
//            throw (static_cast<int>(exception::instruction));
//        }

//        mips_state.pc = tempnpc;	//set the value of pc (the address of the next instruction that is going to execute) to the original value of npc
    }
    free_memory(memory);

    return 0;
}
