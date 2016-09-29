#include <syscall.h>
#include <filehandle.h>
#include <uio.h>
#include <lib.h>
#include <vfs.h>
#include <kern/errno.h>
#include <thread.h>

int
_read(int fd, void *buf, size_t buflen)
{
	struct filehandle *handle;
	struct uio kuio;	

	int result = 0;
	char *console;

	switch (fd)
	{
	    case 0:
		handle = kmalloc(sizeof(struct filehandle));
		if(handle == NULL) return -1;
		
		console = kstrdup("con:");
		if(console == NULL)
		{
			result = -1;
			break;
		}
		result = -1 * vfs_lookup(console, &(handle->file));
		kfree(console);
		handle->offset = 0;
		break;
	    case 1:
	    case 2:
		result = -1*EBADF;
		break;
	    default:
		handle = thread_obtain_file(fd);
		if(handle == NULL) return -1 * EBADF;
		break;
	}

	if(result)
	{
		if(fd == 0)
			kfree(handle);
		return result;
	}

	mk_kuio(&kuio, buf, buflen, handle->offset, UIO_READ);
	
	result = -1*VOP_READ(handle->file, &kuio);

	if(fd == 0) kfree(handle);
	else handle->offset += buflen - kuio.uio_resid;

	//NEED TO CHECK FOR EOF...
	if(result)
		return result;
	
	return (buflen - kuio.uio_resid);

}
