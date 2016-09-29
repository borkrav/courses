/*
 * Synchronization primitives.
 * See synch.h for specifications of the functions.
 */

#include <types.h>
#include <lib.h>
#include <synch.h>
#include <thread.h>
#include <curthread.h>
#include <machine/spl.h>


#ifndef LOCK_STRUCTS
#define LOCK_STRUCTS
////////////////////////////////////////////////////////////
//
// Semaphore.

struct semaphore *
sem_create(const char *namearg, int initial_count)
{
	struct semaphore *sem;

	assert(initial_count >= 0);

	sem = kmalloc(sizeof(struct semaphore));
	if (sem == NULL) {
		return NULL;
	}

	sem->name = kstrdup(namearg);
	if (sem->name == NULL) {
		kfree(sem);
		return NULL;
	}

	sem->count = initial_count;
	return sem;
}

void
sem_destroy(struct semaphore *sem)
{
	int spl;
	assert(sem != NULL);

	spl = splhigh();
	assert(thread_hassleepers(sem)==0);
	splx(spl);

	/*
	 * Note: while someone could theoretically start sleeping on
	 * the semaphore after the above test but before we free it,
	 * if they're going to do that, they can just as easily wait
	 * a bit and start sleeping on the semaphore after it's been
	 * freed. Consequently, there's not a whole lot of point in 
	 * including the kfrees in the splhigh block, so we don't.
	 */

	kfree(sem->name);
	kfree(sem);
}

void 
P(struct semaphore *sem)
{
	int spl;
	assert(sem != NULL);

	/*
	 * May not block in an interrupt handler.
	 *
	 * For robustness, always check, even if we can actually
	 * complete the P without blocking.
	 */
	assert(in_interrupt==0);

	spl = splhigh();
	while (sem->count==0) {
		thread_sleep(sem);
	}
	assert(sem->count>0);
	sem->count--;
	splx(spl);
}

void
V(struct semaphore *sem)
{
	int spl;
	assert(sem != NULL);
	spl = splhigh();
	sem->count++;
	assert(sem->count>0);
	thread_wakeup(sem);
	splx(spl);
}

////////////////////////////////////////////////////////////
//
// Lock.
struct lock *
lock_create(const char *name)
{
struct lock *lock;

	lock = kmalloc(sizeof(struct lock));
	if (lock == NULL) {
		return NULL;
	}

	lock->name = kstrdup(name);
	if (lock->name == NULL) {
		kfree(lock);
		return NULL;
	}

	lock->hasLock = NULL;

	return lock;
}

int
lock_do_i_hold(struct lock *lock)
{
	int result;
	int spl = splhigh();
	result = (lock->hasLock == curthread);
	splx(spl);

	return result;
}

int
lock_locked(struct lock *lock)
{
	return lock->hasLock != NULL;
}

void
lock_destroy(struct lock *lock)
{
	assert(lock != NULL);
	assert(!lock_locked(lock));	

	kfree(lock->name);
	kfree(lock);
}

void
lock_acquire(struct lock *lock)
{
	int spl = splhigh();
	if(lock_locked(lock))
	{
		//if you already have the lock, you don't need to re-acquire
		if(!lock_do_i_hold(lock))
			thread_sleep(lock);

		lock_acquire(lock);	
	}
	else
		lock->hasLock = curthread;//curthread now has lock

	splx(spl);
}


void
lock_release(struct lock *lock)
{
	int spl = splhigh();
	if(lock_do_i_hold(lock))
	{
		lock->hasLock = NULL;
		thread_wakeup_one(lock);
	}
	splx(spl);	
}



////////////////////////////////////////////////////////////
//
// CV


struct cv *
cv_create(const char *name)
{
	struct cv *cv;

	cv = kmalloc(sizeof(struct cv));
	if (cv == NULL) {
		return NULL;
	}

	cv->name = kstrdup(name);
	if (cv->name==NULL) {
		kfree(cv);
		return NULL;
	}
	
	
	return cv;
}

void
cv_destroy(struct cv *cv)
{
	assert(cv != NULL);
	
	kfree(cv->name);
	kfree(cv);
}

void
cv_wait(struct cv *cv, struct lock *lock)
{
	//Must acquire lock before waiting on the CV
	if(lock_do_i_hold(lock)){
	
		int spl = splhigh();
		lock_release(lock);
	
		thread_sleep(cv);

		lock_acquire(lock);
		splx(spl);
	}
}

void
cv_signal(struct cv *cv, struct lock *lock)
{
	int spl = splhigh();
	if(lock_do_i_hold(lock))
		thread_wakeup_one(cv);	
	splx(spl);

}
void
cv_broadcast(struct cv *cv, struct lock *lock)
{
	int spl = splhigh();
	if(lock_do_i_hold(lock))
		thread_wakeup(cv);	
	spl = splx(spl);
}

#endif
