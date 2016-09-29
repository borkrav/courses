#include <processes.h>
#include <smartarray.h>
#include <synch.h>
#include <lib.h>
#include <curthread.h>
#include <kern/errno.h>
#include <machine/spl.h>

struct sarray *processes;

void
processes_bootstrap()
{
	processes = sarray_create();
}

int
process_add()
{

	struct procstat *newStatus = kmalloc(sizeof(struct procstat));
	if(newStatus == NULL) return -1;

	newStatus->mutex = lock_create("process mutex");	
	newStatus->isDone = cv_create("process condition variable");

	newStatus->waiting = 0;
	newStatus->exitcode = -1;

	pid_t pid = (pid_t)sarray_add(processes, newStatus);

	if(pid < 0)
	{
		kfree(newStatus);
		return -1;
	}

	curthread->pid = pid;

	return pid;
}

struct procstat *
process_get()
{
	return (struct procstat *)sarray_getguy(processes, (int)curthread->pid);
}

int
process_remove()
{
	struct procstat *status = 	
		(struct procstat *)sarray_getguy(processes, (int)curthread->pid);
	if(status == NULL) return -1;

	lock_destroy(status->mutex);
	cv_destroy(status->isDone);

	kfree(status);

	return sarray_remove(processes, curthread->pid);
}


int
getpid()
{
	return curthread->pid;
}


int
waitpid(pid_t pid, int *status, int options)
{
	if(status == NULL) return -1*EFAULT;

	int spl = splhigh();
	
	struct procstat *stat = 
		(struct procstat *)sarray_getguy(processes, (int)pid);

	if(stat == NULL) 
	{
		splx(spl);
		return -1;
	}

	//ensures that if the owner is lower in the queue to get the lock
	//that it'll just go back to sleep allow this one to run.
	//and owner will only get it when it's stable at 0
	stat->waiting++;

	lock_acquire(stat->mutex);
		
	splx(spl);	

	while(stat->exitcode == -1)
		cv_wait(stat->isDone, stat->mutex);

	//After all the waiting threads are woken
	//The process will actually go to sleep on this cv
	//Last waiting process to finish will wake the owner up
	if(--stat->waiting == 0)
		cv_signal(stat->isDone, stat->mutex);
	
	*status = stat->exitcode;
	
	lock_release(stat->mutex);

	return pid;
}
