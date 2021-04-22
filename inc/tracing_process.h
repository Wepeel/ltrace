#pragma once
#include <unistd.h>

class tracing_process
{
public:

	tracing_process(const char* path, char* const argv[]);

	void init(const char* path, char* const argv[]);

	long read_memory(void* addr);

	long write_memory(void* addr, void* data);


private:

	long traceme();

	long cont();


private:

	pid_t m_child_pid;
	int m_wait_status;
};