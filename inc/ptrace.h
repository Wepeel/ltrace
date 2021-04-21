#pragma once

namespace trace
{
	long traceme();

	pid_t trace_wait(int status);

	long read_memory(pid_t pid, void* addr);

	long write_memory(pid_t pid, void* addr, void* data);
}