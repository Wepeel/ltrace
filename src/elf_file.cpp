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


	types::byte byte = m_file.read<types::byte>();
	if (ELFMAG0 != byte)
	{
		return false;
	}

	byte = m_file.read<types::byte>();
	if (ELFMAG1 != byte)
	{
		return false;
	}

	byte = m_file.read<types::byte>();
	if (ELFMAG2 != byte)
	{
		return false;
	}

	byte = m_file.read<types::byte>();
	if (ELFMAG3 != byte)
	{
		return false;
	}

	return true;
}

Elf64_Ehdr elf_file::get_elf_header()
{
	m_file.rewind();

	Elf64_Ehdr header = m_file.read<Elf64_Ehdr>();

	return header;
}

Elf64_Shdr elf_file::get_section_header_by_index(const int section_index)
{
	Elf64_Ehdr elf_header = get_elf_header();
	m_file.seek(elf_header.e_shoff + section_index * elf_header.e_shentsize, SEEK_SET);
	return m_file.read<Elf64_Shdr>();
}

Elf64_Shdr elf_file::get_section_header(const Elf64_Word section_type)
{
	Elf64_Ehdr elf_header = get_elf_header();

	m_file.seek(elf_header.e_shoff, SEEK_SET);

	Elf64_Shdr header = m_file.read<Elf64_Shdr>();

	for (int index = 0; index < elf_header.e_shnum; ++index)
	{
		header = m_file.read<Elf64_Shdr>();

		if (section_type == header.sh_type)
		{
			return header;
		}
	}

	return Elf64_Shdr();
}

Elf64_Shdr elf_file::get_section_header(const std::string& section_name)
{
	Elf64_Ehdr elf_header = get_elf_header();
	Elf64_Shdr strtab_section_header = get_section_header(SHT_STRTAB);

	m_file.seek(elf_header.e_shoff, SEEK_SET);

	Elf64_Shdr header = m_file.read<Elf64_Shdr>();

	for (int index = 0; index < elf_header.e_shnum; ++index)
	{
		header = m_file.read<Elf64_Shdr>();

		/*if (section_name == header.sh_name)
		{
			return header;
		}*/
	}

	return Elf64_Shdr();
}

std::vector<std::string> elf_file::get_dynamic_imports()
{
	Elf64_Shdr dynsym_section_header = get_section_header(SHT_DYNSYM);

	if (0 != dynsym_section_header.sh_size)
	{
		Elf64_Shdr strtab_section_header = get_section_header(SHT_STRTAB);

		std::vector<std::string> ret_val;

		for (size_t i = 0; i < dynsym_section_header.sh_size / dynsym_section_header.sh_entsize; i++)
		{
			m_file.seek(dynsym_section_header.sh_offset + i * sizeof(Elf64_Sym), SEEK_SET);
			Elf64_Word sym_index = m_file.read<Elf64_Sym>().st_name;

			m_file.seek(strtab_section_header.sh_offset + sym_index, SEEK_SET);
			std::string symbol = m_file.read_string();

			ret_val.push_back(symbol);
		}

		return ret_val;
	}

	return std::vector<std::string>();
}

Elf64_Shdr elf_file::get_section_string_table_header()
{
	Elf64_Ehdr elf_header = get_elf_header();
	return get_section_header_by_index(elf_header.e_shstrndx);
}