#include "process_ops.h"
#include <sys/types.h>
#include <sys/wait.h>

pid_t process_ops::trace_fork()
{
	return ::fork();
}

int process_ops::trace_execvp(const char* path, char* const argv[])
{
	return ::execvp(path, argv);
}

pid_t process_ops::trace_wait(int* status)
{
	return ::wait(status);
}
