#include "opcode_computer.h"
#include <stdio.h>

int main()
{
	opcode* opcode = read_opcode("input");

	print_opcode(opcode);

	int result;
	do
	{
		result = read_next_opcode(opcode);
	}
	while(result);
	printf("Result %i\n", opcode->code[0]);

	return 0;
}
