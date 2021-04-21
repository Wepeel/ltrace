#include "ptrace.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>

#include <cstdio>

long trace::traceme()
{
	return ptrace(PTRACE_TRACEME, NULL, NULL, NULL);
}

pid_t trace::trace_wait(int status)
{
	return wait(status);
}

long trace::read_memory(pid_t pid, void* addr)
{
	return ptrace(PTRACE_PEEKTEXT, pid, addr, NULL);
}

long trace::write_memory(pid_t pid, void* addr, void* data)
{
	return ptrace(PTRACE_POKETEXT, pid, addr, data);
}