#include "debugger.h"

debugger::debugger(const char* path, char* const argv[])
	:m_process(path, argv)
{

}

types::byte debugger::create_breakpoint(void* address)
{
	types::byte ret_val = m_process.read_memory(address);

	types::byte breakpoint_value = 0xCC;
	m_process.write_memory(address, &breakpoint_value);

	return ret_val;
}