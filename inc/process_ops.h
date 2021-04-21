#pragma once

enum fork_status
{
	PID_ERROR = -1,
	CHILD_PROCESS = 0
};

enum wait_status
{
	WAIT_ERROR = -1
};

namespace process_ops
{
	pid_t fork();

	int execvp(const char* path, char* const argv[]);

	pid_t wait(int* status);
}