#include <syscall.h>
#include <lib.h>
#include <kern/errno.h>
#include <filehandle.h>
#include <thread.h>
#include <vfs.h>
#include <uio.h>

int
_write(int fd, const void*buf, size_t buflen)
{
	struct filehandle *handle;
	int result = 0;

	struct uio kuio;

	char *console;
	switch (fd)
	{
	    case 0://STD_IN
		return -1*EBADF;
		break;
	    case 1://STD_OUT
	    case 2://STD_ERR
		handle = kmalloc(sizeof(struct filehandle));
		if(handle == NULL) return -1;

		console = kstrdup("con:");
		if(console == NULL)
		{
			result = -1*EBADF;
			break;
		}
		//LOOK IT UP
		result = -1*vfs_lookup(console, &(handle->file));
		kfree(console);
		handle->offset = 0;
		break;
	    default://STORED IN THREAD
		handle = thread_obtain_file(fd);
		if(handle == NULL) return -1*EBADF;
		break;
	}
	if(result)
	{
		if(fd == 1 || fd == 2)
			kfree(handle);
		return result;
	}
	//Make a uio space
	mk_kuio(&kuio, (void *)buf, buflen, handle->offset, UIO_WRITE);
	
	//Attempt to write
	result = VOP_WRITE(handle->file, &kuio);
	if(fd == 1 || fd ==2 )
		kfree(handle);//Free up the temperary handle
	else	//increse the thread's file's offset
		handle->offset += buflen - kuio.uio_resid;

	if(result) return -1*result;

	return (buflen - kuio.uio_resid);
}
