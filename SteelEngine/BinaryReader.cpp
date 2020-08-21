#include "SteelEnginePCH.h"
#include "BinaryReader.h"

BinaryReader::BinaryReader(const std::string& filepath)
	: m_Filepath{filepath}
{}

bool BinaryReader::OpenFile()
{
	m_Filestream = std::ifstream(m_Filepath, std::ios::in | std::ios::binary);
	if (!m_Filestream)
	{
		std::cerr << "Cannot open " << m_Filepath << std::endl;
		return false;
	}

	if (m_Filestream.is_open())
	{
		return true;
	}

	std::cerr << "Cannot open " << m_Filepath << std::endl;
	return false;
}


bool BinaryReader::IsOpen()
{
	return m_Filestream.is_open();
}

bool BinaryReader::EndOfFile()
{
	if (m_Filestream.is_open())
	{
		int flag{};
		flag = m_Filestream.peek();
		if (flag == EOF)
		{
			//std::cout << "End of file!\n";
			return true;
		}
		else
			return false;
	}
	else
	{
		std::cout << "No file is open. Returning true.\n";
		return true;
	}

}

bool BinaryReader::CloseFile()
{
	if (m_Filestream.is_open())
	{
		m_Filestream.close();
		return true;
	}
	std::cout << m_Filepath << " was not open." << std::endl;
	return false;
}

