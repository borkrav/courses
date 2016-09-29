#ifndef _SYSCALL_H_
#define _SYSCALL_H_

#include <types.h>
#include <lib.h>

/*
 * Prototypes for IN-KERNEL entry points for system call implementations.
 */

int sys_reboot(int code);
int _open(const char *filename, int flags);
int _close(int fd);
int _write(int fd, const void* buf, size_t buflen);
int _read(int fd, void *buf, size_t buflen);
void _exit(int exitcode);
#endif /* _SYSCALL_H_ */
