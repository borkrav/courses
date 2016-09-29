#ifndef _SMART_ARRAY_H_
#define _SMART_ARRAY_H_

#include <array.h>
#include <types.h>

//Would like inheritance for this, but... C... oh well.


struct sarray
{

	int next;//next index to insert at
	struct array *content;

	struct lock *mutex;

};

struct sarray *sarray_create();
int            sarray_getnum(struct sarray *);
void 	      *sarray_getguy(struct sarray *, int index);
int	       sarray_getnextposition(struct sarray *);
int 	       sarray_bound(struct sarray *);
int            sarray_add(struct sarray *, void *guy);
int	       sarray_remove(struct sarray *, int index);
void	       sarray_destroy(struct sarray *);



#endif /* _SMART_ARRAY_H_ */
