#include "ltracer.h"

ltracer::ltracer(const char* path, char* const argv[])
	: m_debugger(path, argv), m_elf_file(path)
{
	insert_ltrace_breakpoints();
}

void ltracer::insert_ltrace_breakpoints()
{
	Elf64_Shdr plt_header = m_elf_file.get_section_header(".plt");
	const int entry_size = plt_header.sh_entsize;
	const int amount_of_plt_functions = plt_header.sh_size / plt_header.sh_entsize;

	char* plt_ptr = nullptr;// = plt_header.sh_offset; // TODO: Correct it to go to the first byte in the plt
	plt_ptr = plt_ptr + entry_size; // Skip over the .plt - go straight to the functions

	for (int index = 0; index < amount_of_plt_functions; ++index, plt_ptr += entry_size)
	{
		this->m_breakpoint_bytes.push_back(m_debugger.create_breakpoint(plt_ptr));
	}
}