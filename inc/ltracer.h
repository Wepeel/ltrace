#pragma once

#include <vector>
#include "types.h"
#include "debugger.h"
#include "elf_file.h"

class ltracer
{
public:

	ltracer(const char* path, char* const argv[]);


private:

	void insert_ltrace_breakpoints();


private:

	std::vector<types::byte> m_breakpoint_bytes;
	debugger m_debugger;
	elf_file m_elf_file;
};