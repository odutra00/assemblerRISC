#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 100
#define MAX_INSTRUCTIONS 1000
#define MAX_LABELS 100

typedef struct {
    char mnemonic[10];
    int opcode;
    int rs;
    int rt;
    int rd;
    int shamt;
    int funct;
    int immediate;
    int address;
    int JumpADDR;
    char label[20];
} Instruction;

typedef struct {
    char label[20];
    int address;
} Label;

void printBinary(unsigned int n) {
    for (int i = 31; i >= 0; i--) {
        unsigned int mask = 1 << i;
        printf("%d", (n & mask) ? 1 : 0);
        if (i % 4 == 0) {
            printf(" "); // Add space for readability
        }
    }
    printf("\n");
}

int parseRegister(char *reg) {
//    printf("\nregister %s : ", reg);
    // Remove any leading or trailing whitespace
    while (*reg == ' ' || *reg == '\t' || *reg == '(') {
        reg++;
    }
    while (reg[strlen(reg) - 1] == ' ' || reg[strlen(reg) - 1] == '\t' || reg[strlen(reg) - 1] == ')') {
        reg[strlen(reg) - 1] = '\0';
    }

    // Check if the register is in the format $rxx
    if (reg[0] == '$' && reg[1] == 'r') {
        return atoi(&reg[2]);
    }

    return -1;
}

//int parseImmediate(char *imm, int grupo) {
//    printf("\n");
//    //printf("Immediate string: %s\n", imm);
//    //printf("Immediate integer: %d\n", atoi(imm));
//    return atoi(imm) & 0xFFFF;
//}
int parseExpression(const char *expr, int grupo);
int parseImmediate(char *imm, int grupo) {
    // Trim leading and trailing spaces
    while (isspace((unsigned char)*imm)) imm++;
    char *end = imm + strlen(imm) - 1;
    while (end > imm && isspace((unsigned char)*end)) end--;
    end[1] = '\0';

    // Parse the expression with grupo as a possible variable
    int result = parseExpression(imm, grupo);
    
    // Apply the 16-bit mask
    return result & 0xFFFF;
}

int parseTerm(const char **expr, int grupo) {
    int value = 0;

    // Check if the term is a hexadecimal number
    if (**expr == '0' && *(*expr + 1) == 'x') {
        value = strtol(*expr, (char **)expr, 16);  // Convert from hexadecimal
    } 
    // Check for a decimal number
    else if (isdigit(**expr) || (**expr == '-' && isdigit(*((*expr) + 1)))) {
        value = strtol(*expr, (char **)expr, 10);  // Convert from decimal
    } 
    // Check for a variable (e.g., "grupo")
    else if (strncmp(*expr, "grupo", 5) == 0) {
        value = grupo;
        *expr += 5;
    }

    return value;
}

int parseFactor(const char **expr, int grupo) {
    int value = parseTerm(expr, grupo);
    
    while (**expr == '*' || **expr == '/') {
        char op = *(*expr)++;
        int nextValue = parseTerm(expr, grupo);
        
        if (op == '*') {
            value *= nextValue;
        } else if (op == '/') {
            value /= nextValue;
        }
    }
    
    return value;
}

int parseExpression(const char *expr, int grupo) {
    int value = parseFactor(&expr, grupo);
    
    while (*expr == '+' || *expr == '-') {
        char op = *expr++;
        int nextValue = parseFactor(&expr, grupo);
        
        if (op == '+') {
            value += nextValue;
        } else if (op == '-') {
            value -= nextValue;
        }
    }
    
    return value;
}



















void parseInstruction(char *line, Instruction *inst, int grupo) {
    char *token = strtok(line, " ,\t");
    if (token == NULL) {
        printf("Error: Invalid instruction format.\n");
        return;
    }
    if (token[strlen(token) - 1] == ':') {
        strcpy(inst->label, token);
        token = strtok(NULL, " ,\t");
        if (token == NULL) {
            printf("Error: Invalid instruction format after label.\n");
            return;
        }
    }
    strcpy(inst->mnemonic, token);

    if (strcmp(inst->mnemonic, "lw") == 0 || strcmp(inst->mnemonic, "sw") == 0 || strcmp(inst->mnemonic, "addi") == 0 || strcmp(inst->mnemonic, "ori") == 0) {
        token = strtok(NULL, " ,\t");
        if (token == NULL) {
            printf("Error: Missing rt register.\n");
            return;
        }
        inst->rt = parseRegister(token);
        token = strtok(NULL, " ,\t");
        char *offset = strtok(token, "(");
        char *rs = strtok(NULL, ")");
        if (offset == NULL || rs == NULL) {
            printf("Error: Invalid format for immediate and rs register.\n");
            return;
        }
        inst->immediate = parseImmediate(offset, grupo);
//        printf("\noffset / inst->menmonic / inst->immediate: %s / %s / %d", offset, inst->mnemonic ,inst->immediate);
        inst->rs = parseRegister(rs);
    } else if (strcmp(inst->mnemonic, "bne") == 0) {
        token = strtok(NULL, " ,\t");
        if (token == NULL) {
            printf("Error: Missing rs register.\n");
            return;
        }
        inst->rs = parseRegister(token);
        token = strtok(NULL, " ,\t");
        if (token == NULL) {
            printf("Error: Missing rt register.\n");
            return;
        }
        inst->rt = parseRegister(token);
        token = strtok(NULL, " ,\t");
        if (token == NULL) {
            printf("Error: Missing label.\n");
            return;
        }
        strcpy(inst->label, token);
    } else if (strcmp(inst->mnemonic, "add") == 0 || strcmp(inst->mnemonic, "sub") == 0 || strcmp(inst->mnemonic, "mul") == 0 ||
               strcmp(inst->mnemonic, "and") == 0 || strcmp(inst->mnemonic, "or") == 0) {
        token = strtok(NULL, " ,\t");
        if (token == NULL) {
            printf("Error: Missing rd register.\n");
            return;
        }
        inst->rd = parseRegister(token);
        token = strtok(NULL, " ,\t");
        if (token == NULL) {
            printf("Error: Missing rs register.\n");
            return;
        }
        inst->rs = parseRegister(token);
        token = strtok(NULL, " ,\t");
        if (token == NULL) {
            printf("Error: Missing rt register.\n");
            return;
        }
        inst->rt = parseRegister(token);
    } else if (strcmp(inst->mnemonic, "jmp") == 0) {
        token = strtok(NULL, " ,\t");
        if (token == NULL) {
            printf("Error: Missing address for jmp.\n");
            return;
        }
        //inst->address = parseImmediate(token);
        strcpy(inst->label, token);
//        printf("Parsing JMP Instruction: %s, Label: %s\n", inst->mnemonic, inst->label); // Debug print
    }
}
























void generateHexFile(Instruction *instructions, int count, int grupo, Label *labels, int labelCount, const char *outputFileName) {
    FILE *hexFile = fopen(outputFileName, "w");
    if (!hexFile) {
        perror("Failed to open output file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < count; i++) {
        Instruction inst = instructions[i];
        unsigned int machineCode = 0;

        if (strcmp(inst.mnemonic, "lw") == 0) {
            machineCode = ((grupo + 32) << 26) | (inst.rs << 21) | (inst.rt << 16) | (inst.immediate & 0xFFFF);
        } else if (strcmp(inst.mnemonic, "sw") == 0) {
            machineCode = ((grupo + 33) << 26) | (inst.rs << 21) | (inst.rt << 16) | (inst.immediate & 0xFFFF);
        } else if (strcmp(inst.mnemonic, "bne") == 0) {
            machineCode = ((grupo + 34) << 26) | (inst.rs << 21) | (inst.rt << 16) | (inst.immediate & 0xFFFF);
        } else if (strcmp(inst.mnemonic, "addi") == 0) {
            machineCode = ((grupo + 35) << 26) | (inst.rs << 21) | (inst.rt << 16) | (inst.immediate & 0xFFFF);
        } else if (strcmp(inst.mnemonic, "ori") == 0) {
            machineCode = ((grupo + 36) << 26) | (inst.rs << 21) | (inst.rt << 16) | (inst.immediate & 0xFFFF);
        } else if (strcmp(inst.mnemonic, "add") == 0) {
            machineCode = ((grupo + 10) << 26) | (inst.rs << 21) | (inst.rt << 16) | (inst.rd << 11) | (10 << 6) | 32;
        } else if (strcmp(inst.mnemonic, "sub") == 0) {
            machineCode = ((grupo + 10) << 26) | (inst.rs << 21) | (inst.rt << 16) | (inst.rd << 11) | (10 << 6) | 34;
        } else if (strcmp(inst.mnemonic, "mul") == 0) {
            machineCode = ((grupo + 10) << 26) | (inst.rs << 21) | (inst.rt << 16) | (inst.rd << 11) | (10 << 6) | 50;
        } else if (strcmp(inst.mnemonic, "and") == 0) {
            machineCode = ((grupo + 10) << 26) | (inst.rs << 21) | (inst.rt << 16) | (inst.rd << 11) | (10 << 6) | 36;
        } else if (strcmp(inst.mnemonic, "or") == 0) {
            machineCode = ((grupo + 10) << 26) | (inst.rs << 21) | (inst.rt << 16) | (inst.rd << 11) | (10 << 6) | 37;
        } else if (strcmp(inst.mnemonic, "jmp") == 0) {
            machineCode = (2 << 26) | (inst.JumpADDR & 0x3FFFFFF);
        }

        // Convert machine code to Intel HEX format
        unsigned char byteCount = 4;
        unsigned int address = inst.address;
        unsigned char recordType = 0;
        unsigned char data[4];
        data[0] = (machineCode >> 24) & 0xFF;
        data[1] = (machineCode >> 16) & 0xFF;
        data[2] = (machineCode >> 8) & 0xFF;
        data[3] = machineCode & 0xFF;
        unsigned char checksum = byteCount + (address >> 8) + (address & 0xFF) + recordType + data[0] + data[1] + data[2] + data[3];
        checksum = ~checksum + 1;

        fprintf(hexFile, ":%02X%04X%02X%02X%02X%02X%02X%02X\n", byteCount, address, recordType, data[0], data[1], data[2], data[3], checksum);
    }

    // Write end of file record
    fprintf(hexFile, ":00000001FF\n");

    fclose(hexFile);
}






int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <input.asm> <grupo> <output.hex>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("Failed to open input file");
        return EXIT_FAILURE;
    }

    int grupo = atoi(argv[2]);
    const char *outputFileName = argv[3];
    Instruction instructions[MAX_INSTRUCTIONS];
    Label labels[MAX_LABELS];
    int count = 0;
    int labelCount = 0;
    char line[MAX_LINE_LENGTH];

    // First pass: parse instructions, collect labels, and assign addresses
    int address = 0;
    while (fgets(line, sizeof(line), inputFile)) {
        // Check if the line contains a label at the beginning
        char *labelEnd = strchr(line, ':');
        char *instructionPart = line; // Pointer to the instruction part
        if (labelEnd) {
            *labelEnd = '\0'; // Null-terminate the label
            strcpy(labels[labelCount].label, line);
            labels[labelCount].address = address; // Assign current address to the label
//            printf("\nLabel: %s, Address: %d\n", labels[labelCount].label, labels[labelCount].address); // Debug print            
            labelCount++;
            instructionPart = labelEnd + 1; // Move the pointer to the instruction part after the label
        }

        parseInstruction(instructionPart, &instructions[count], grupo);
        instructions[count].address = address; // Assign address to the instruction
        address += 4; // Increment address by instruction size (4 bytes)
        count++;
    }

    // Second pass: resolve labels and compute offsets
    for (int i = 0; i < count; i++) {
        if (strcmp(instructions[i].mnemonic, "bne") == 0) {
            for (int j = 0; j < labelCount; j++) {
//                printf("\n\nBNE - instructions[i].label, labels[j].label %s , %s", instructions[i].label, labels[j].label);
                if (strcmp(instructions[i].label, labels[j].label) == 0) {
//                    // Calculate the offset for the branch instruction
//                    instructions[i].immediate = (labels[j].address - instructions[i].address - 4) ;
//                    printf("\nBNE - label(j).address: %d", labels[j].address);
//                    printf("\nBNE - Instructions(i).address: %d", instructions[i].address);
//                    printf("\nBNE - Instructions(i).immediate: %d", instructions[i].immediate);
//                    break;
                    // Calculate the offset for the branch instruction
                    int offset = (labels[j].address - instructions[i].address - 4);
                    // Sign-extend the offset to 16 bits
                    if (offset < -32768 || offset > 32767) {
                        printf("Error: Offset out of range for bne instruction.\n");
                        break;
                    }
                    instructions[i].immediate = offset & 0xFFFF;
//                    printf("\nBNE - label(j).address: %d", labels[j].address);
//                    printf("\nBNE - Instructions(i).address: %d", instructions[i].address);
//                    printf("\nBNE - Instructions(i).immediate: %d", instructions[i].immediate);
                    break;
                }
            }
        } else if (strcmp(instructions[i].mnemonic, "jmp") == 0) {
            for (int j = 0; j < labelCount; j++) {
//                printf("\n\nJMP - instructions[i].label, labels[j].label %s , %s", instructions[i].label, labels[j].label);
                if (strcmp(instructions[i].label, labels[j].label) == 0) {
                    //instructions[i].address = labels[j].address;
                    instructions[i].JumpADDR = labels[j].address;
//                    printf("\nJMP - label(j).JumpADDR: %d", instructions[i].JumpADDR);                                   
//                    printf("\nJMP - label(j).address: %d", labels[j].address);
//                    printf("\nJMP - Instructions(i).address: %d", instructions[i].address);
//                    printf("\nJMP - Instructions(i).immediate: %d", instructions[i].immediate);
                    break;
                }
            }
        }
    }

    fclose(inputFile);

    generateHexFile(instructions, count, grupo, labels, labelCount, outputFileName);

    return EXIT_SUCCESS;
}
