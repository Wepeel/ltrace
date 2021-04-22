#pragma once
#include <vector>
#include <string>
#include "file.h"
#include <elf.h>


class elf_file
{
public:

	elf_file(const std::string& path);

	bool verify_elf_structure();

	Elf64_Ehdr get_elf_header();

	Elf64_Shdr get_section_header(const Elf64_Word section_type);

	std::vector<std::string> get_dynamic_imports();


private:

	file m_file;
};