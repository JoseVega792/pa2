#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // malloc & free
#include <stdint.h> // use guaranteed 64-bit integers
#include "tokenizer.h" // Create header file and reference that
#include "memory.h" // built-in functions to read and write to a specific file

int32_t* reg; // Array of 32 32-bit registers

void init_regs();
bool interpret(char* instr);
void write_read_demo();

/**
 * Initialize register array for usage.
 * Malloc space for each 32-bit register then initializes each register to 0.
 * Do not alter this function!
 */
void init_regs(){
	int reg_amount = 32;
	reg = malloc(reg_amount * sizeof(int32_t)); // 32 * 4 bytes
	for(int i = 0; i < 32; i++)
		reg[i] = i;
}



/**
 * Fill out this function and use it to read interpret user input to execute RV64 instructions.
 * You may expect that a single, properly formatted RISC-V instruction string will be passed
 * as a parameter to this function.
 */
int compare(char* toke){
	if(*toke == 'L'){
		if (*(toke + 1) == 'W')
		{
			return 1;
		}
	}else if(*toke == 'S'){
		if(*(toke + 1) == 'W'){
			return 2;
		}
	}else if(*toke == 'A'){
		if(*(toke + 1) == 'D'){
			if(*(toke + 1) == 'D'){
				if(*(toke + 1) == 'I'){
					return 4;
				}else{
					return 3;
				}
			}
		}
	}else{
		return -1;
	}
}
bool interpret(char* instr){
	char** tokens = tokenize(instr,' ');
	int type = compare(*tokens);
	if(type == 1){
		int regist = atoi(*tokenize(tokens[1], 'X'));
		char **address = tokenize(tokens[2], 'X');
		int memo = atoi(address[0]);
		int base = atoi(*tokenize(address[1], 'X'));
		int32_t location = reg[memo]+base;
		int32_t finder = read_address(location,"mem.txt");
		reg[regist] = finder;
		return true;
	}else if(type == 2){
		int regist = atoi(*tokenize(tokens[1], 'X'));
		char **address = tokenize(tokens[2], 'X');
		int memo = atoi(address[0]);
		int base = atoi(*tokenize(address[1], 'X'));
		int32_t location = reg[memo] + base;
		write_address(reg[regist],location,"mem.txt");
		return true;
	}else if(type == 3){
		int main = atoi(*tokenize(tokens[1], 'X'));
		int firstNum = reg[atoi(*tokenize(tokens[2], 'X'))];
		int secondNum = reg[atoi(*tokenize(tokens[3], 'X'))];
		reg[main] = firstNum + secondNum;
		return true;
	}else if(type == 4){
		int main = atoi(*tokenize(tokens[1], 'X'));
		int firstNum = reg[atoi(*tokenize(tokens[2], 'X'))];
		int secondNum = atoi(*tokenize(tokens[3], 'X'));
		reg[main] = firstNum + secondNum;
		return true;
	}else{
		return false;
	}
}


/**
 * Simple demo program to show the usage of read_address() and write_address() found in memory.c
 * Before and after running this program, look at mem.txt to see how the values change.
 * Feel free to change "data_to_write" and "address" variables to see how these affect mem.txt
 * Use 0x before an int in C to hardcode it as text, but you may enter base 10 as you see fit.
 */
void write_read_demo(){
	int32_t data_to_write = 0xFFF; // equal to 4095
	int32_t address = 0x98; // equal to 152
	char* mem_file = "mem.txt";

	// Write 4095 (or "0000000 00000FFF") in the 20th address (address 152 == 0x98)
	int32_t write = write_address(data_to_write, address, mem_file);
	if(write == (int32_t) NULL)
		printf("ERROR: Unsucessful write to address %0X\n", 0x40);
	int32_t read = read_address(address, mem_file);

	printf("Read address %lu (0x%lX): %lu (0x%lX)\n", address, address, read, read); // %lu -> format as an long-unsigned
}

/**
 * Your code goes in the main
 *
 */
int main(){
	// Do not write any code between init_regs
	init_regs(); // DO NOT REMOVE THIS LINE

	// Below is a sample program to a write-read. Overwrite this with your own code.
	write_read_demo();

	return 0;
}
