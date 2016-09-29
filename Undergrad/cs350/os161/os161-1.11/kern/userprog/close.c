#include <syscall.h>
#include <thread.h>
#include <lib.h>

int
_close(int fd)
{
	return thread_remove_file(fd);

}
