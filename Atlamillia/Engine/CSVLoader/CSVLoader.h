#pragma once

#include <vector>
#include "../Graphics/Debug.h"

namespace Atlamillia
{
	class CSVLoader
	{
		private:
		protected:
		public:

			static std::vector<std::vector<int>> LoadCSVFile_int(const char* _filename);
			static std::vector<std::vector<std::vector<int>>> Load3DCSVFile_int(const char* _filename);
			static std::vector<std::vector<std::string>> LoadCSVFile_str(const char * _filename);
	};
}