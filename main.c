#include <stdio.h>
#include <stdlib.h>
void vm(FILE *fPtr);
int main(int argc, char* argv[]) {
  if (argc < 2) {
    printf("You did not input any files.\n");
    exit(1);
  }
  FILE *fPtr;
  char c;
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
  char c;
  int mem_length = 1024;
  int while_loop_length = 16;
  int *memory = calloc(mem_length, sizeof(int));
  long while_mem = 0;
  int *while_ptr;
  int jmp = 0;
  int while_nested = 0;
  if (!memory) {
    printf("FATAL: Cannot alloc memory.\n");
    exit(1);
  }
  int mem_pos = 0;
  int while_loop_start = -1;
  while ((c = fgetc(fPtr)) != EOF) {
    if (jmp == 1 && c != ']') {
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
        if (mem_pos  >= (mem_length - 1)) {
          mem_length += 1024;
          memory = realloc(memory, sizeof(int) * mem_length);
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
        break;
      case '[':
        while_ptr = memory + mem_pos;
        while_mem = ftell(fPtr);
        if (!while_ptr) {
          jmp = 1;
        }
        break;
      case ']':
        if (!(*while_ptr)) {
          jmp = 0;
        } else {
          fseek(fPtr, while_mem, SEEK_SET);
        }
        break;
/*
      case '[':
        ++while_nested;
        while_mem->pos = ftell(fPtr);
        if (!memory[mem_pos]) {
           while_mem->jmp = 1;
        }
        ++while_mem;
        break;
      case ']':
        --while_nested;
        --while_mem;
        if (while_mem->jmp == 1) {
          break;
        } else if (memory[mem_pos]){
          fseek(fPtr, *while_mem, SEEK_SET);
          ++while_mem;
        }
        break;
*/
      default:
        break;
    }
  }
}
