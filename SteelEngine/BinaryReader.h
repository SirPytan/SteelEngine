#pragma once
#include <string>
#include <iostream>
#include <type_traits>
#include <iostream>
#include <fstream>
#include <regex>

class BinaryReader
{
public:
	//Please add complete filepath with correct file extension
	BinaryReader(const std::string& filepath);

	//True if opened correctly, false if not
	bool OpenFile();
	
	template<typename T>
	void Read(T& data);

	bool EndOfFile();
	bool IsOpen();
	//Closes filestream, if filestream was open and returns true, else it returns false and prints info message.
	bool CloseFile();
	

	//void ReadBinaryOBJFileToClass(const std::string& filename, OBJ& obj);

private:
	//int ReadNumberOfElements(std::ifstream& inputStream);

	std::string m_Filepath;
	std::ifstream m_Filestream;
};

template<typename T>
inline void BinaryReader::Read(T& data)
{
	m_Filestream.read((char*)&data, sizeof(data));
}
