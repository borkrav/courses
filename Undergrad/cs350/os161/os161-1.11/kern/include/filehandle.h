#ifndef _FILEHANDLE_H_
#define _FILEHANDLE_H_

#include <types.h>
#include <vnode.h>

struct filehandle
{

	off_t offset;
	struct vnode *file;

};

#endif
