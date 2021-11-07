#include <stdio.h>
#include <stdlib.h>
#include "helpers.h"
#include "memory.c"
#define PARSE_FILE "../input_file.txt"

static int find_opcode(const char* token){
    if (strcmp(token, "lw") == 0){
        return lw;
    }else if(strcmp(token, "sw") == 0){
        return sw;
    }else if(strcmp(token, "add") == 0){
        return add;
    }else if(strcmp(token, "sub") == 0){
        return sub;
    }else if(strcmp(token, "addi") == 0){
        return addi;
    }else if(strcmp(token, "slt") == 0){
        return slt;
    }else if(strcmp(token, "slti") == 0){
        return slti;
    }else if(strcmp(token, "beq") == 0){
        return beq;
    }else if(strcmp(token, "bne") == 0){
        return bne;
    }else if(strcmp(token, "j") == 0){
        return j;
    }else if(strcmp(token, "jr") == 0){
        return jr;
    }else if(strcmp(token, "jal") == 0){
        return jal;
    }else if(strcmp(token, "jalr") == 0){
        return jalr;
    }else if(strcmp(token, "nor") == 0){
        return nor;
    }else if(strcmp(token, "break") == 0){
        return _break;
    }else{
//        perror("Not a valid command.\n");
//        exit(-1);
        return -1;
    }
}

static void parse_token(char* token, size_t token_count, MemoryBlock* mem){
    // Remove any leftovers commas.
    if (token[strlen(token) - 1]  == ',')
        token[strlen(token) - 1] = 0;

    if (mem->type != NoneType){
        if(token[strlen(token) - 1] == ':'){
            token[strlen(token) - 1] = 0;
            mem->label = copy_str(mem->label, token);
//            printf("label: %s\n", ram->label);
        }
        int number;
        switch (mem->type) {
            case JType:
                if(does_str_contain_char(token))
                    mem->j_label = copy_str(mem->j_label, token);
//                else set_target(get_int_from_str(token), ram);
                break;
            case IType:
                number = get_int_from_str(token);
                switch (token_count) {
                    case 1:
                        set_rt(number, mem);
//                        printf("rt: %d\n", number);
                        break;
                    case 2:
                        set_rs(number, mem);
//                        printf("rs: %d\n", number);
                        break;
                    case 3:
                        set_imm(number, mem);
//                        printf("imm: %d\n", number);
                        break;
                }
                break;
            case RType:
                number = get_int_from_str(token);
                switch (token_count) {
                    case 1:
                        if(mem->cmd == jr)
                            set_rs(number, mem);
                        else{
                            set_rd(number, mem);
//                            printf("rd: %d\n", number);
                        }
                        break;
                    case 2:
                        set_rs(number, mem);
//                      printf("rs: %d\n", number);
                        break;
                    case 3:
                        if(mem->cmd == slt || mem->cmd == slti) {
                            set_shamt(number, mem);
//                          printf("shamt: %d\n", number);
                        }else{
                            set_rt(number, mem);
//                          printf("rt: %d\n", number);
                        }
//                      printf("func: %u\n", ram->cmd);
                        break;
                }
                break;
        }
    }else{
        int opcode = find_opcode(token);
        if(opcode != -1){
            mem->type = find_instruction_type(opcode);
            mem->cmd = opcode;
            if (mem->type == RType)
                set_func(opcode, mem);
            set_opcode(opcode, mem);
        }
    }

//    printf("curr val: %u", ram->val);
//    for(int i = 0; i < strlen(token); i++){
//        char c = token[i];
//        if(c == ':'){
//
//        }
//    }
}

static Memory* read_file(){
    FILE *fp;
    Memory* memory = new_Memory();

    // Open file and check if everything went smoothly.
    if(!(fp = fopen(PARSE_FILE, "r"))){
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }
    char* line = NULL;
    size_t j = 0, line_size = 0;
    ssize_t line_len;

    // Parse line by line.
    while ((line_len = getline(&line, &line_size, fp)) != -1){
        char** tokens = separate_str(line, " ");
        MemoryBlock* memory_block = new_MemoryBlock();

        int i = 0;
        for(;;){
            char* token = tokens[i++];
            if(token == NULL) break;
            parse_token(token, i - 1, memory_block);
        }
        memory->ram[j++] = memory_block;
    }
    memory->len = j;

    free(line);
    fclose(fp);
    return memory;
}
