#include "opcode_computer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int __instruction_ptr = 0;

opcode* read_opcode(const char* file_name)
{
	FILE* fptr;
	fptr = fopen(file_name, "r");

	char* line = NULL;
	size_t len = 0;
	getline(&line, &len, fptr);

	char* token = strtok(line, ",");
	int size = 0;
	// max size == len so allocate that much memory
	int* code = (int*) malloc(sizeof(int)*len);
	do
	{
		code[size] = atoi(token);
	}
	while( (token =(strtok(NULL, ","))) != NULL && ++size);

	code = (int*) realloc(code, sizeof(int)*size);
	opcode* oc = (opcode*) malloc(sizeof(int*) + sizeof(size_t));
	oc->code = code;
	oc->size = size;

	free(line);
	fclose(fptr);
	return oc;
}

void free_opcode(opcode* opcode)
{
	free(opcode->code);
	free(opcode);
}

void print_opcode(const opcode* opcode)
{
	printf("opcode\n");
	int* code = opcode->code;
	for(size_t i = 0; i < opcode->size; i += 4)
	{
		int op		= code[i];
		int arg1	= code[i+1];
		int arg2	= code[i+2];
		int res		= code[i+3];
		printf("[%i, %i, %i, %i]\n", op, arg1, arg2, res);
	}
}

int read_next_opcode(opcode* opcode)
{
	int* code = opcode->code;
	int op	 = code[__instruction_ptr];
	int arg1 = code[code[__instruction_ptr+1]];
	int arg2 = code[code[__instruction_ptr+2]];
	int* res = &code[code[__instruction_ptr+3]];
	printf("op code %i, %i, %i, %i\n", op, arg1, arg2, *res);
	switch(op)
	{
		case 1:
			*res = arg1 + arg2;
			break;
		case 2:
			*res = arg1 * arg2;
			break;
		case 99:
			printf("END CODE 99 result %i\n", code[0]);
			return 0;
		default:
			printf("CODE NOT RECOGNIZED: %i @ %i\n", code[__instruction_ptr], __instruction_ptr);
			return 0;
			break;
	}

	__instruction_ptr += 4;
	return 1;
}

void alter_opcode(opcode* opcode, size_t pos, int val)
{
	opcode->code[pos] = val;
}

void reset_computer()
{
	__instruction_ptr = 0;
}

int run_program(opcode* opcode)
{
	reset_computer();
	while(read_next_opcode(opcode)){}
	return opcode->code[0];
}
