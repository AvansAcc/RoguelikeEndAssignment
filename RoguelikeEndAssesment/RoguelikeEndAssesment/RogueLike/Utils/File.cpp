#include "File.h"

namespace RogueLike { namespace Utils {

	File::File(const std::string path)
	{
		this->_fullpath = path;
		this->_content = "";
		this->_size = -1;
		
		int index_name = path.find_last_of("/\\") + 1;
		int dot = path.find_last_of(".");
		this->_name = (!path.empty()) ? (path.substr(index_name, (((path.size()-1) - index_name) - ((path.size() - 1) - dot)))) : "";
		this->_extension = (!path.empty() && dot >= 0) ? (path.substr(dot + 1)) : "";
		this->_path = (!path.empty() && index_name >= 0) ? (path.substr(0, index_name)) : "";
	}

	File::~File()
	{
		// Nothing to see here..
	}

	//ios::in		Open for input operations.
	//ios::out		Open for output operations.
	//ios::binary	Open in binary mode.
	//ios::ate		Set the initial position at the end of the file. If this flag is not set, the initial position is the beginning of the file.
	//ios::app		All output operations are performed at the end of the file, appending the content to the current content of the file.
	//ios::trunc	If the file is opened for output operations and it already existed, its previous content is deleted and replaced by the new one.


	// Read as Binary file.
	/*std::string File::ReadBinaryFile()
	{
		if (this->_fullpath.empty()) {
			throw ErrorHandling::FileNotFoundException();
			return "";
		}

		std::ifstream file(this->_fullpath, std::ios::in | std::ios::binary | std::ios::ate);
		char* block = nullptr;
		std::streampos size;

		if (file.is_open())
		{
			size = file.tellg();
			this->_size = (int)size;
			
			
			if (this->_size > 0)
			{
				block = new char[this->_size];
				file.seekg(0, std::ios::beg);
				file.read(block, size);
				file.close();

				this->_content = block;
				delete[] block;
				block = nullptr;
			}
			return this->_content;
		}
		else
		{
			//std::cout << "Unable to open file: " << this->_fullpath << std::endl;
			std::string str = "Unable to open file: ";
			str.append(_fullpath);
			throw ErrorHandling::FileNotFoundException(str);
			return "";
		}
	}*/

	std::string File::Read()
	{
		if (this->_fullpath.empty()) {
			throw ErrorHandling::FileNotFoundException();
			return "";
		}

		std::ifstream file(this->_fullpath, std::ios::in | std::ios::binary | std::ios::ate);
		std::streampos size;

		if (file.is_open())
		{
			size = file.tellg();
			this->_size = (int)size;

			if (this->_size > 0)
			{
				file.seekg(0, std::ios::beg);
				std::string str = "";
				this->_content = "";
			
				while (std::getline(file, str))
				{
					this->_content += (str + "\n");
				}

				file.close();
			}
			return this->_content;
		}
		else
		{
			//std::cout << "Unable to open file: " << this->_fullpath << std::endl;
			std::string str = "Unable to open file: ";
			str.append(_fullpath);
			throw ErrorHandling::FileNotFoundException(str);
			return "";
		}
	}

	bool File::Write(const std::string data, bool overwrite)
	{
		if (this->_fullpath.empty()) {
			throw ErrorHandling::FileNotFoundException();
			return false;
		}

		std::ofstream file(this->_fullpath, ((overwrite) ? (std::ofstream::out | std::ofstream::trunc) : (std::ios::out | std::ios::app | std::ios::binary)));
		
		if (file.is_open())
		{
			file.write(data.c_str(), data.size());
			file.close();

			this->Read();

			return true;
		}
		else
		{
			//std::cout << "Unable to open file: " << this->_fullpath << std::endl;
			std::string str = "Unable to open file: ";
			str.append(_fullpath);
			throw ErrorHandling::FileNotFoundException(str);
			return false;
		}
	}
	const int File::Size() const { return this->_size; }
	const bool File::IsEmpty() const { return (this->_size <= 0); }
	const std::string File::Name() const { return this->_name; }
	const std::string File::FullName() const { return (this->_name + "." + this->_extension); }
	const std::string File::Path() const { return this->_path; }
	const std::string File::FullPath() const { return this->_fullpath; }
	const std::string File::Extension() const { return this->_extension; }

} }