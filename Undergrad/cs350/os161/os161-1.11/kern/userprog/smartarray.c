#include <types.h>
#include <lib.h>
#include <array.h>
#include <smartarray.h>
#include <synch.h>

struct sarray *
sarray_create(void)
{
	struct sarray *sa = kmalloc(sizeof(struct sarray));

	if(sa == NULL)
		return NULL;

	sa->content = array_create();
	sa->next = 0;//First element entered hardcoded to 0.
	sa->mutex =  lock_create("SArrayMut");
	
	return sa;
}

int
sarray_getnum(struct sarray *sa)
{
	return array_getnum(sa->content);
}

void *
sarray_getguy(struct sarray *sa, int index)
{
	return array_getguy(sa->content, index);
}

int
sarray_getnextposition(struct sarray *sa)
{
	return sa->next;
}

int
sarray_add(struct sarray *sa, void *guy)
{
	int result = 0;

	lock_acquire(sa->mutex);

	int bound = array_getnum(sa->content);
	if(sa->next == bound)
	{
		result = array_add(sa->content, guy);
		
		sa->next++;
	}
	else
	{
		array_setguy(sa->content, sa->next, guy);

		//Update the next value for next insertion place
		//This is O(n) and could be bad for large arrays
		//Especially if in practise it seems to follow ~ FIFO
		for(sa->next++;
			sa->next < bound 
			&& array_getguy(sa->content, sa->next)!=NULL;
		    sa->next++);
	}

	lock_release(sa->mutex);

	return result;

}

int
sarray_remove(struct sarray *sa, int index)
{
	lock_acquire(sa->mutex); //If locking this makes everything choppy, maintenance can be done differnetly
	if(index >= array_getnum(sa->content) ||
		array_getguy(sa->content, index) == NULL)
		return -1;

	array_setguy(sa->content, index, NULL);//Don't remove. Just nullify

	//Update next insertion position value
	sa->next = (index < sa->next)? index : sa->next;

	int bound = array_getnum(sa->content);
	
	//This is a maintenance loop on the array
	//Trys to clean up the array. O(n).
	for(; bound > 0 && array_getguy(sa->content, bound-1)==NULL; bound--)
	{
		array_remove(sa->content, bound-1);			
	}
	
	//I'm skeptical that this condition could ever be true, but...
	if(sa->next > bound) sa->next = bound;
	lock_release(sa->mutex);

	return 0;
}


void
sarray_destroy(struct sarray *sa)
{
	//So... it assumes array isn't pointing to any malloc'd data
	if(sa->content) array_destroy(sa->content);
	lock_destroy(sa->mutex);
	kfree(sa);
}
