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

	Elf64_Shdr get_section_header_by_index(const int section_index);

	Elf64_Shdr get_section_header(const Elf64_Word section_type);

	Elf64_Shdr get_section_header(const std::string& name);

	std::vector<std::string> get_dynamic_imports();


private:

	Elf64_Shdr get_section_string_table_header();

private:

	file m_file;
};