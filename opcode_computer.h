#ifndef OPCODE_COMPUTER_H
#define OPCODE_COMPUTER_H
#include <stddef.h>

typedef struct opcode
{
	int* code;
	size_t size; // size of array; divide by 4 to get number of instructions
} opcode;

// read file and return opcode
opcode* read_opcode(const char* file_name);

void free_opcode(opcode*);

void print_opcode(const opcode*);

void alter_opcode(opcode*, size_t pos, int val);

/* 
 * read and exectue next instruction
 * returns 0 if no last instruction
 * returns 99 if last instruction
 * returns 1 if error
 */
int read_next_opcode(opcode* opcode);

// resets instruction pointer and then run through entire program
int run_program(opcode* opcode);

// resets instruction pointer
void reset_computer();

#endif
