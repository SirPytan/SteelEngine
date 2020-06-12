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



//void BinaryReader::ReadBinaryOBJFileToClass(const std::string& filename, OBJ& obj)
//{
//	std::regex regexFilname(".+\\.(bOBJ|bobj)$");
//	if (std::regex_match(filename, regexFilname))
//	{
//		std::ifstream inputStream(filename, std::ios::in | std::ios::binary);
//		if (!inputStream)
//		{
//			std::cerr << "Cannot open " << filename << std::endl;
//			return;
//		}
//		else
//		{
//
//			if (inputStream.is_open())
//			{
//				int numberOfElements{};
//				numberOfElements = ReadNumberOfElements(inputStream);
//
//				unsigned int commentLength;
//				for (int i{}; i < numberOfElements; i++)
//				{
//					Comment* pComment = new Comment();
//					inputStream.read((char*)(&commentLength), sizeof(commentLength));
//					pComment->comment.resize(commentLength);
//					inputStream.read((char*)pComment->comment.c_str(), commentLength); //Always use stringname.c_str() else it you try to read a pointer to the file
//					inputStream.read((char*)&pComment->line, sizeof(unsigned int));
//					obj.AddComment(pComment);
//				}
//
//				numberOfElements = ReadNumberOfElements(inputStream);
//				for (int i{}; i < numberOfElements; i++)
//				{
//					Vertex* pVertex = new Vertex();
//					pVertex->id = i + 1;
//					inputStream.read((char*)&pVertex->x, sizeof(float));
//					inputStream.read((char*)&pVertex->y, sizeof(float));
//					inputStream.read((char*)&pVertex->z, sizeof(float));
//					obj.AddVertex(pVertex);
//				}
//
//				numberOfElements = ReadNumberOfElements(inputStream);
//				for (int i{}; i < numberOfElements; i++)
//				{
//					VertexNormal* pVertexNormal = new VertexNormal();
//					pVertexNormal->id = i + 1;
//					inputStream.read((char*)&pVertexNormal->x, sizeof(float));
//					inputStream.read((char*)&pVertexNormal->y, sizeof(float));
//					inputStream.read((char*)&pVertexNormal->z, sizeof(float));
//					obj.AddVertexNormal(pVertexNormal);
//				}
//
//				numberOfElements = ReadNumberOfElements(inputStream);
//				bool readVertexTexture{ false };
//				bool readVertexNormal{ false };
//
//				inputStream.read((char*)&readVertexTexture, sizeof(readVertexTexture));
//				inputStream.read((char*)&readVertexNormal, sizeof(readVertexNormal));
//
//				for (int i{}; i < numberOfElements; i++)
//				{
//					Face* pFace = new Face();
//					pFace->id = i + 1;
//					inputStream.read((char*)&pFace->v1, sizeof(int));
//					inputStream.read((char*)&pFace->v2, sizeof(int));
//					inputStream.read((char*)&pFace->v3, sizeof(int));
//
//					if (readVertexTexture)
//					{
//						inputStream.read((char*)&pFace->vt1, sizeof(int));
//						inputStream.read((char*)&pFace->vt2, sizeof(int));
//						inputStream.read((char*)&pFace->vt3, sizeof(int));
//					}
//					else
//					{
//						pFace->vt1 = 0;
//						pFace->vt2 = 0;
//						pFace->vt3 = 0;
//					}
//
//					if (readVertexNormal)
//					{
//						inputStream.read((char*)&pFace->vn1, sizeof(int));
//						inputStream.read((char*)&pFace->vn2, sizeof(int));
//						inputStream.read((char*)&pFace->vn3, sizeof(int));
//					}
//					else
//					{
//						pFace->vn1 = 0;
//						pFace->vn2 = 0;
//						pFace->vn3 = 0;
//					}
//					obj.AddFace(pFace);
//				}
//				inputStream.close();
//			}
//		}
//	}
//}
//
//int BinaryReader::ReadNumberOfElements(std::ifstream& inputStream)
//{
//	int numberOfElements{};
//	inputStream.read((char*)&numberOfElements, sizeof(numberOfElements));
//	return numberOfElements;
//}
