#pragma once
#include <cstdio>
#include <string>

class file
{
public:

	using byte = unsigned char;

	file(const std::string& path, const char* mode);

	~file();

	file(const file&) = delete;

	const file& operator=(const file&) = delete;

	template<typename Type>
	Type read()
	{
		Type obj;
		const size_t read_ret_value = fread(&obj, sizeof(obj), 1, m_ptr);
		if (1 != read_ret_value)
		{
			// TODO: Error
		}

		return obj;
	}

	template<typename Type>
	void write(const Type& obj)
	{
		const size_t write_ret_value = fwrite(obj, sizeof(obj), 1, m_ptr);
		if (1 != write_ret_value)
		{
			// TODO: Error
		}
	}

	std::string read_string();

	void seek(long offset, int origin);

	void rewind();


private:

	void open(const std::string& path, const char* mode);

	void close();

private:

	std::string m_path;
	FILE* m_ptr = nullptr;
};