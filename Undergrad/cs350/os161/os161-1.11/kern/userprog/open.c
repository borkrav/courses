#include <syscall.h>
#include <thread.h>
#include <lib.h>

int
_open(const char *filename, int flags)
{

	char *temp = kstrdup(filename);
	int fd = thread_add_file(temp, flags);
	kfree(temp);

	return fd;


}
