#ifndef _PROCHANDLE_H_
#define _PROCHANDLE_H_

#include <types.h>

//Process STATUS
struct procstat
{

	struct lock *mutex;
	struct cv *isDone;

	int waiting;
	int exitcode;

};


extern struct sarray *processes;

void processes_bootstrap();

int process_add();
struct procstat *process_get();
int process_remove();

pid_t getpid();
int waitpid(pid_t pid, int *status, int options);

#endif
