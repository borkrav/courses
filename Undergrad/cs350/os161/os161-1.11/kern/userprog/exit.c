#include <syscall.h>
#include <thread.h>
#include <curthread.h>

#include <machine/spl.h>
#include <processes.h>
#include <synch.h>

void
_exit(int exitcode)
{
	
	assert(exitcode >= 0);

	struct procstat *status = process_get();
	
	assert(status != NULL);

	status->exitcode = exitcode;
	
	cv_broadcast(status->isDone, status->mutex);

	lock_acquire(status->mutex);
	while(status->waiting != 0)
		cv_wait(status->isDone, status->mutex);
	
	lock_release(status->mutex);
	
	int spl = splhigh();
	process_remove();
	splx(spl);
	
	thread_exit();
}
