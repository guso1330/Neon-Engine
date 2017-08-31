#include "../utils/fileUtils.h"

namespace neon {
	std::string read_file(const char* filepath) {
		FILE* file = fopen(filepath, "rt");
		if(file == nullptr) {
			std::cout << filepath << " not found" << std::endl;
			exit(0);
		} else {
			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			char* data = new char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);

			std::string result(data);
			delete[] data;
			return result;
		}
	}
}
