#include "ltracer.h"

ltracer::ltracer(const char* path, char* const argv[])
	: m_debugger(path, argv), m_elf_file(path)
{
	insert_ltrace_breakpoints();
}

void ltracer::insert_ltrace_breakpoints()
{

}