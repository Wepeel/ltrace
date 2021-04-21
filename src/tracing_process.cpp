#include "tracing_process.h"
#include "ptrace.h" 
#include "process_status.h"

tracing_process::tracing_process(const char* path, char* const argv[])
{
	init(path, argv);
}

void tracing_process::init(const char* path, char* const argv[])
{
	pid_t pid = fork();

	if (fork_status::PID_ERROR == pid)
	{
		// TODO: Error
	}

	else if (fork_status::CHILD_PROCESS == pid)
	{
		// Init trace
		trace::traceme();

		execvp(path, argv);
	}

	else // Parent process
	{
		m_pid = pid;
	}
}

long tracing_process::read_memory(void* addr)
{
	trace::read_memory(m_pid, addr);
}

long tracing_process::write_memory(void* addr, void* data)
{
	trace::write_memory(m_pid, addr, data);
}