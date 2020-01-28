#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

void vm(FILE *fPtr);
void elf64(FILE *fPtr);

int main(int argc, char* argv[]) {
	if (argc < 2) {
		printf("You did not input any files.\n");
		exit(1);
	}
	FILE *fPtr;
	fPtr = fopen(argv[1], "r");
	if (!fPtr) {
		printf("Cannot read this file.\n");
		exit(1);
	}
	vm(fPtr);
	fclose(fPtr);
	return 0;
}

void vm(FILE *fPtr) {
	int mem_length = 1024;
	unsigned char *memory = calloc(mem_length, sizeof(unsigned char));
	if (!memory) {
		printf("FATAL: Cannot alloc memory.\n");
		exit(1);
	}
	int mem_pos = 0;

	int jmp = 0;

	stack_t ss;
	init_stack(&ss);

	char c;
	while ((c = fgetc(fPtr)) != EOF) {
		if (jmp >= 1) {
			if (c == '[') {
				++jmp;
			} else if (c == ']') {
				--jmp;
			}
			continue;
		}
		switch (c) {
		case '+':
			++(memory[mem_pos]);
			break;
		case '-':
			--(memory[mem_pos]);
			break;
		case '>':
			++mem_pos;
			if (mem_pos >= (mem_length - 1)) {
				mem_length += 1024;
				memory = realloc(memory, sizeof(unsigned char) * mem_length);
			}
			break;
		case '<':
			if (mem_pos <= 0) {
				printf("FATAL: Memory error\n");
				exit(1);
			} else {
				--mem_pos;
			}
			break;
		case '.':
			putchar(memory[mem_pos]);
			break;
		case ',':
			memory[mem_pos] = getchar();
			getchar();
			break;
		case '[':
			if (!(memory[mem_pos])) {
				++jmp;
			} else {
				ss->push(ss, ftell(fPtr) - 1);
			}
			break;
		case ']':
			if (ss->size(ss) > 0) {
				fseek(fPtr, ss->top(ss), SEEK_SET);
				ss->pop(ss);
			} else {
				puts("Loop not pair");
				close_stack(ss);
				exit(1);
			}
			break;
		case '#':
			do {
				c = fgetc(fPtr);
			} while (c != '\n' && c != 0);
		default:
			break;
		}
	}
	close_stack(ss);
}
