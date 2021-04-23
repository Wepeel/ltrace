#include "file.h"

file::file(const std::string& path, const char* mode)
	:m_path(path), m_ptr(nullptr)
{
	open(path, mode);
}

file::~file()
{
	close();
}

std::string file::read_string()
{
	std::string ret;

	types::byte byte_read;

	do
	{
		const size_t read_result = fread(&byte_read, sizeof(byte_read), 1, m_ptr);
		if (1 != read_result)
		{
			// TODO:
		}
		ret.push_back(byte_read);
	} while (byte_read);

	return ret;
}

void file::seek(long offset, int origin)
{
	const int seek_ret_val = fseek(m_ptr, offset, origin);
	if (0 != seek_ret_val)
	{
		// TODO: Error
	}
}

void file::rewind()
{
	::rewind(m_ptr);
}

void file::open(const std::string& path, const char* mode)
{
	m_ptr = fopen(path.c_str(), mode);
}

void file::close()
{
	if (nullptr != m_ptr)
	{
		fclose(m_ptr);
	}

	m_ptr = nullptr;
}