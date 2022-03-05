#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>    // malloc & free
#include <stdint.h>    // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h"    // built-in functions to read and write to a specific file

int32_t *reg; // Array of 32 32-bit registers

void init_regs();
bool interpret(char *instr);
void write_read_demo();

/**
 * Initialize register array for usage.
 * Malloc space for each 32-bit register then initializes each register to 0.
 * Do not alter this function!
 */
void init_regs()
{
    int reg_amount = 32;
    reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
    for (int i = 0; i < 32; i++)
        reg[i] = i;
}
/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
/**
 * Here we will use this function in order to compare what exactly the first field of the code is.
*/
int compare(char *toke)
{
    if (*toke == 'L')// Here we check for LW
    {
        if (*(toke + 1) == 'W')
        {
            return 1;
        }
    }
    else if (*toke == 'S') // Here we check for SW
    {
        if (*(toke + 1) == 'W')
        {
            return 2;
        }
    }
    else if (*toke == 'A') // Here we check for ADD and ADDI
    {
        if (*(toke + 1) == 'D')
        {
            if (*(toke + 1) == 'D')
            {
                if (*(toke + 1) == 'I')// This is where the I is accounted for
                {
                    return 4;
                }
                else
                {
                    return 3;
                }
            }
        }
    }
    else
    {
        return -1;
    }
}
/**
 * This is the function where we mainly work in
*/
bool interpret(char *instr)
{
    /**
     * Here we will initiallize our tokens and allow for us to compare
    */
    char **tokens = tokenize(instr, ' ');
    char *ptr = tokens[0];
    int type = compare(ptr);
    if (type == 1) // This is where we will check for the LW
    {
        int regist = atoi(*tokenize(tokens[1], 'X')); // Here we get the register we will be working with
        char **address = tokenize(tokens[2], 'X'); // We then look into the address of the word
        int memo = atoi(address[0]); // Here we get the memory location number
        int base = atoi(*tokenize(address[1], 'X')); // Here we get the insantance of the vase
        int32_t location = reg[memo] + base; 
        int32_t finder = read_address(location, "mem.txt"); //We can grab from the file
        reg[regist] = finder; // This is how we set it in the registers
        return true;
    }
    else if (type == 2) // This is where we will check for the SW
    {
        int regist = atoi(*tokenize(tokens[1], 'X')); // Here we get the register we will be working with
        char **address = tokenize(tokens[2], 'X'); // We then look into the address of the word
        int memo = atoi(address[0]); // Here we get the memory location number
        int base = atoi(*tokenize(address[1], 'X'));
        int32_t location = reg[memo] + base;
        write_address(reg[regist], location, "mem.txt");// Here we write it to the file
        return true;
    }
    else if (type == 3) // This is where we will check for the ADD
    {
        int main = atoi(*tokenize(tokens[1], 'X')); // Here we will get the main register we will be working with
        int firstNum = reg[atoi(*tokenize(tokens[2], 'X'))]; // Here we get the first number within the register
        int secondNum = reg[atoi(*tokenize(tokens[3], 'X'))]; // Here we get the second number within the register
        reg[main] = firstNum + secondNum; // This is where we set the main register to the addition
        return true;
    }
    else if (type == 4) // This is where we will check for the ADDI
    {
        int main = atoi(*tokenize(tokens[1], 'X'));
        int firstNum = reg[atoi(*tokenize(tokens[2], 'X'))];
        int secondNum = atoi(*tokenize(tokens[3], 'X')); // This is similar to above however we do not need to look within the register rather just the number.
        reg[main] = firstNum + secondNum;
        return true;
    }
    else //This is only if a number is not valid
    {
        return false;
    }
}

/**
 * Simple demo program to show the usage of read_address() and write_address() found in memory.c
 * Before and after running this program, look at mem.txt to see how the values change.
 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt
 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.
 */
void write_read_demo()
{
    int32_t data_to_write = 0xFFF; // equal to 4095
    int32_t address = 0x98;        // equal to 152
    char *mem_file = "mem.txt";

    // Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)
    int32_t write = write_address(data_to_write, address, mem_file);
    if (write == (int32_t)NULL)
        printf("ERROR: Unsucessful write to address %0X\n", 0x40);
    int32_t read = read_address(address, mem_file);

    printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}

/**
 * Prints all 32 registers in column-format
 */
void print_regs()
{
    int col_size = 10;
    for (int i = 0; i < 8; i++)
    {
        printf("X%02i:%.*lld", i, col_size, (long long int)reg[i]);
        printf(" X%02i:%.*lld", i + 8, col_size, (long long int)reg[i + 8]);
        printf(" X%02i:%.*lld", i + 16, col_size, (long long int)reg[i + 16]);
        printf(" X%02i:%.*lld\n", i + 24, col_size, (long long int)reg[i + 24]);
    }
}

/**
 * Your code goes in the main
 *
 */
int main()
{
    // Do not write any code between init_regs
    init_regs(); // DO NOT REMOVE THIS LINE

    print_regs();

    // Below is a sample program to a write-read. Overwrite this with your own code.
    // write_read_demo();

    printf(" RV32 Interpreter.\nType RV32 instructions. Use upper-case letters and space as a delimiter.\nEnter 'EOF' character to end program\n");

    char *instruction = malloc(1000 * sizeof(char));
    bool is_null = false;
    // fgets() returns null if EOF is reached.
    is_null = fgets(instruction, 1000, stdin) == NULL;
    while (!is_null)
    {
        interpret(instruction);
        printf("\n");
        print_regs();
        printf("\n");

        is_null = fgets(instruction, 1000, stdin) == NULL;
    }

    printf("Good bye!\n");

    return 0;
}
