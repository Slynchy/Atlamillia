#include "CSVLoader.h"
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

unsigned int SplitString(const std::string &txt2, std::vector<std::string> &strs, char ch, bool remove = true)
{
	std::string txt = txt2;
	unsigned int pos = txt.find(ch);
	unsigned int initialPos = 0;
	strs.clear();

	// Decompose statement
	while (pos != std::string::npos) {
		strs.push_back(txt.substr(initialPos, pos - initialPos + 1));
		if (remove)
			strs.back().pop_back();
		initialPos = pos + 1;

		pos = txt.find(ch, initialPos);
	}

	// Add the last one
	strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

	return strs.size();
};

bool iscomma(char &i)
{
	if (i == ',')
		return true;
	else return false;
}

std::vector<std::vector<std::string>> Atlamillia::CSVLoader::LoadCSVFile_str(const char * _filename)
{
	std::vector<std::vector<std::string>> output;

	dprintf("[CSVLoader] Loading: %s\n", _filename);
	std::ifstream input(_filename);
	if (input)
	{
		// Get the line count
		std::string tempStr;
		int linecount = 0;
		for (int i = 0; std::getline(input, tempStr); ++i)
		{
			linecount = i;
		}
		input.clear();
		input.seekg(0, std::ios::beg);

		// Initialize the splitstring array
		std::vector<std::string> tempArr;

		// Get the line and split it by comma
		//std::getline(input, tempStr);
		//SplitString(tempStr, tempArr, ',');

		for (int line = 0; line <= linecount; line++)
		{
			std::getline(input, tempStr);
			SplitString(tempStr, tempArr, ',',true);
			std::vector<std::string> tempVec;
			for (size_t i = 0; i < tempArr.size(); i++)
			{
				tempArr.at(i).erase(std::remove_if(tempArr.at(i).begin(), tempArr.at(i).end(), iscomma));
				//std::stringstream convert(tempArr.at(i));
				//int temp;
				//convert >> temp;
				tempVec.push_back(tempArr.at(i));
			}
			output.push_back(tempVec);
		};
		input.close();
	}
	else
	{
		dprintf("[CSVLoader] Failed to load: %s\n", _filename);
	}

	return output;
}


std::vector<std::vector<std::vector<int>>> Atlamillia::CSVLoader::Load3DCSVFile_int(const char * _filename)
{
	std::vector<std::vector<std::vector<int>>> output;

	dprintf("[CSVLoader] Loading: %s\n", _filename);
	std::ifstream input(_filename);

	if (input)
	{
		// Get the line count
		std::string tempStr;
		int linecount = 0;
		for (int i = 0; std::getline(input, tempStr); ++i)
		{
			linecount = i;
		}
		input.clear();
		input.seekg(0, std::ios::beg);

		// Initialize the splitstring array
		std::vector<std::string> tempArr;

		for (int line = 0; line <= linecount; line++)
		{
			std::getline(input, tempStr);
			SplitString(tempStr, tempArr, ',');
			std::vector<std::vector<int>> tempVec;
			for (size_t i = 0; i < tempArr.size(); i++)
			{
				if (tempArr.at(i).front() == '{')
				{
					tempVec.push_back(std::vector<int>());
					tempArr.at(i).erase(tempArr.at(i).begin());
					tempArr.at(i).pop_back();
					std::vector<std::string> parentStrArr;
					SplitString(tempArr.at(i), parentStrArr, '|', true);
					for (size_t y = 0; y < parentStrArr.size(); y++)
					{
						std::stringstream convert(parentStrArr.at(y));
						int temp;
						convert >> temp;
						tempVec.back().push_back(temp);
					}
				}
				else
				{
					std::stringstream convert(tempArr.at(i));
					int temp;
					convert >> temp;
					tempVec.push_back(std::vector<int>());
					tempVec.back().push_back(temp);
				}
			}
			output.push_back(tempVec);
		};
		input.close();
	}
	else
	{
		dprintf("[CSVLoader] Failed to load: %s\n", _filename);
	}

	return output;
}


std::vector<std::vector<int>> Atlamillia::CSVLoader::LoadCSVFile_int(const char * _filename)
{
	std::vector<std::vector<int>> output;

	dprintf("[CSVLoader] Loading: %s\n", _filename);
	std::ifstream input(_filename);
	if (input)
	{
		// Get the line count
		std::string tempStr;
		int linecount = 0;
		for (int i = 0; std::getline(input, tempStr); ++i)
		{
			linecount = i;
		}
		input.clear();
		input.seekg(0, std::ios::beg);

		// Initialize the splitstring array
		std::vector<std::string> tempArr;

		for (int line = 0; line <= linecount; line++)
		{
			std::getline(input, tempStr);
			SplitString(tempStr, tempArr, ',');
			std::vector<int> tempVec;
			for (size_t i = 0; i < tempArr.size(); i++)
			{
				std::stringstream convert(tempArr.at(i));
				int temp;
				convert >> temp;
				tempVec.push_back(temp);
			}
			output.push_back(tempVec);
		};
		input.close();
	}
	else 
	{
		dprintf("[CSVLoader] Failed to load: %s\n", _filename);
	}

	return output;
}
