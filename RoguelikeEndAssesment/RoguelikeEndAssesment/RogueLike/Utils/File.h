#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include "../ErrorHandling/FileNotFoundException.h"

namespace RogueLike { namespace Utils {

	class File {
	private:
		std::string _name;
		std::string _extension;
		std::string _path;
		std::string _fullpath;
		std::string _content;
		int _size;
	private:
		
	public:
		File(const std::string path);
		~File();

		//std::string ReadBinaryFile();
		std::string Read();
		bool Write(const std::string data, bool overwrite = false);
		const bool IsEmpty() const;
		const int Size() const;

		const std::string Name() const;
		const std::string FullName() const;
		const std::string Path() const;
		const std::string FullPath() const;
		const std::string Extension() const;
	};

} }