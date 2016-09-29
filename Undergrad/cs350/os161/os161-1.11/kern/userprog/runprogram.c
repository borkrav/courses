/*
 * Sample/test code for running a user program.  You can use this for
 * reference when implementing the execv() system call. Remember though
 * that execv() needs to do more than this function does.
 */

#include <types.h>
#include <kern/unistd.h>
#include <kern/errno.h>
#include <lib.h>
#include <addrspace.h>
#include <thread.h>
#include <curthread.h>
#include <vm.h>
#include <vfs.h>
#include <test.h>

#include <processes.h>

/*
 * Load program "progname" and start running it in usermode.
 * Does not return except on error.
 *
 * Calls vfs_open on progname and thus may destroy it.
 */
int
runprogram(char *progname, unsigned long nargs, char **args)
{


	struct vnode *v;
	vaddr_t entrypoint, stackptr;
	int result;

	/* Open the file. */
	result = vfs_open(progname, O_RDONLY, &v);
	if (result) {
		return result;
	}

	/* We should be a new thread. */
	assert(curthread->t_vmspace == NULL);

	/* Create a new address space. */
	curthread->t_vmspace = as_create();
	if (curthread->t_vmspace==NULL) {
		vfs_close(v);
		return ENOMEM;
	}

	/* Activate it. */
	as_activate(curthread->t_vmspace);
	/* Load the executable. */
	result = load_elf(v, &entrypoint);
	if (result) {
		/* thread_exit destroys curthread->t_vmspace */
		vfs_close(v);
		return result;
	}

	/* Done with the file now. */
	vfs_close(v);

	/* Define the user stack in the address space */


	result = as_define_stack(curthread->t_vmspace, &stackptr);

	if (result) {
		/* thread_exit destroys curthread->t_vmspace */
		return result;
	}

	unsigned int c; //just a counter
	//put the args on the stack and change string ptrs
	for(c = 0; c < nargs; c++)
	{
		//Length of the string + NULL char
		unsigned int stringDataSize = strlen(args[c])+1;
		stackptr -= stringDataSize;

		copyout(args[c], (userptr_t)stackptr, stringDataSize); 
		args[c] = (char *)stackptr;
		//the arg ptr now points to that addr
	}

	//All the same type => same size.
	//nargs number of pointers + NULL ptr
	unsigned int ptrArrayDataSize = (nargs+1) * sizeof(args[0]);
	//move the stack ptr back the size of the ptrArray
	stackptr -= ptrArrayDataSize;
	//the ptrArray needs to be aligned wrt 4 bytes
	//But the stackptr, ultimately, needs to be aligned wrt 8 bytes
	stackptr -= (stackptr % 8);//max fragmentation = 7bytes
	args[nargs] = NULL;

	copyout(args, (userptr_t)stackptr, ptrArrayDataSize);
	args = (char **)stackptr;


	process_add();

	/* Warp to user mode. */
	md_usermode(nargs, (userptr_t)args,
	    stackptr, entrypoint);
	/* md_usermode does not return */
	panic("md_usermode returned\n");
	return EINVAL;
}

