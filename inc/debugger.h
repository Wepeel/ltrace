#pragma once
#include "tracing_process.h"
#include "types.h"
#include "tracing_process.h"

class debugger
{

public:

	debugger(const char* path, char* const argv[]);

	types::byte create_breakpoint(void* address);


private:

	tracing_process m_process;
};