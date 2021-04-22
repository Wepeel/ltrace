#pragma once

#include <unistd.h>

namespace trace
{
	long traceme();

	long cont(pid_t pid);

	long read_memory(pid_t pid, void* addr);

	long write_memory(pid_t pid, void* addr, void* data);
}