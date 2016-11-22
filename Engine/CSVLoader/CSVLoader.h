#pragma once

#include <vector>

#ifdef _DEBUG
	#define dprintf printf
#else
	#define dprintf __noop
#endif

namespace Atlamillia
{
	class CSVLoader
	{
		private:
		protected:
		public:

			static std::vector<std::vector<int>> LoadCSVFile_int(const char* _filename);
			static std::vector<std::vector<std::string>> LoadCSVFile_str(const char * _filename);
	};
}