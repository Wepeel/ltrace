#include "elf_file.h"

elf_file::elf_file(const std::string& path)
	:m_file(path, "r")
{
	if (!verify_elf_structure())
	{
		// TODO: Error
	}
}

bool elf_file::verify_elf_structure()
{
	m_file.rewind();

	file::byte byte;

	m_file.read(byte);
	if (ELFMAG0 != byte)
	{
		return false;
	}

	m_file.read(byte);
	if (ELFMAG1 != byte)
	{
		return false;
	}

	m_file.read(byte);
	if (ELFMAG2 != byte)
	{
		return false;
	}

	m_file.read(byte);
	if (ELFMAG3 != byte)
	{
		return false;
	}

	return true;
}

Elf64_Ehdr elf_file::get_elf_header()
{
	m_file.rewind();

	Elf64_Ehdr header;

	m_file.read(header);

	return header;
}

Elf64_Shdr get_section_header(const Elf64_Word section_type)
{
	Elf64_Ehdr elf_header = get_elf_header();

	m_file.seek(elf_header.e_shoff, SEEK_SET);

	Elf64_Shdr header;
	m_file.read(header);

	for (int index = 0; index < elf_header.e_shnum; ++index)
	{
		m_file.seek(elf_header.e_shentsize, SEEK_CUR);
		m_file.read(header);

		if (section_type == header.sh_type)
		{
			return header;
		}
	}
}

std::vector<std::string> elf_file::get_dynamic_symbol_table()
{
	get_section_header(SHT_DYNSYM);
}