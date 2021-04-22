#include "tracing_process.h"
#include "ptrace.h" 
#include "process_ops.h"

tracing_process::tracing_process(const char* path, char* const argv[])
{
	init(path, argv);
}

void tracing_process::init(const char* path, char* const argv[])
{
	pid_t pid = process_ops::trace_fork();

	if (fork_status::PID_ERROR == pid)
	{
		// TODO: Error
	}

	else if (fork_status::CHILD_PROCESS == pid)
	{
		// Init trace
		traceme();

		process_ops::trace_execvp(path, argv);
	}

	else // Parent process
	{
		m_child_pid = pid;
		pid_t wait_value = process_ops::trace_wait(&m_wait_status);

		if (wait_status::WAIT_ERROR == wait_value)
		{
			// TODO: Error
		}

		cont();
	}
}

long tracing_process::read_memory(void* addr)
{
	trace::read_memory(m_child_pid, addr);
}

long tracing_process::write_memory(void* addr, void* data)
{
	trace::write_memory(m_child_pid, addr, data);
}

long tracing_process::traceme()
{
	return trace::traceme();
}

long tracing_process::cont()
{
	return trace::cont(m_child_pid);
}