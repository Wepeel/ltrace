#include "process_ops.h"
#include <unistd.h>

pid_t process_ops::fork()
{
	return fork();
}

int process_ops::execvp(const char* path, char* const argv[])
{
	return execbp(path, argv);
}

pid_t process_ops::wait(int* status)
{
	return wait(status);
}