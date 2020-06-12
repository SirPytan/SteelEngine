#include "LevelReader.h"
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <bitset>

//#define PRINT_LEVELS
//#define PRINT_ENEMIES

LevelReader::LevelReader()
{
    m_LevelBitmask[0] = 0b10000000;
    m_LevelBitmask[1] = 0b01000000;
    m_LevelBitmask[2] = 0b00100000;
    m_LevelBitmask[3] = 0b00010000;
    m_LevelBitmask[4] = 0b00001000;
    m_LevelBitmask[5] = 0b00000100;
    m_LevelBitmask[6] = 0b00000010;
    m_LevelBitmask[7] = 0b00000001;

    m_EnemyBitmask[0] = 0b00000000; //Zen chan
    m_EnemyBitmask[1] = 0b00000110; //Mighta
    m_EnemyBitmask[2] = 0b00000100; //Monsta
    m_EnemyBitmask[3] = 0b00000011; //Pulpul
    m_EnemyBitmask[4] = 0b00000010; //Banebou
    m_EnemyBitmask[5] = 0b00000001; //Hidegons
    m_EnemyBitmask[6] = 0b00000101; //Drunk
    m_EnemyBitmask[7] = 0b00000111; //Invader

    m_EnemyTypes[0] = EnemyType::ZenChan;
    m_EnemyTypes[1] = EnemyType::Mighta;
    m_EnemyTypes[2] = EnemyType::Monsta;
    m_EnemyTypes[3] = EnemyType::Pulpul;
    m_EnemyTypes[4] = EnemyType::Banebou;
    m_EnemyTypes[5] = EnemyType::Hidegons;
    m_EnemyTypes[6] = EnemyType::Drunk;
    m_EnemyTypes[7] = EnemyType::Invader;
}

bool LevelReader::ReadLevels()
{
    #ifdef PRINT_LEVELS
    _setmode(_fileno(stdout), _O_U16TEXT);//Sets print mode to unicode
    #endif // PRINT_LEVELS
    BinaryReader br(m_DataPath + "SeperatedLevelData.dat");
    if (br.OpenFile())
    {
        //Iterate over the 100 Levels
        for (unsigned int l{}; l < 100; l++)
        {
            LevelData newLevel{ l };
            unsigned int row{};
            unsigned int column{};
            //Iterate over the 25 lines per Level
            for (unsigned int k{}; k < 25; k++)
            {
                //Iterate through the 4 bytes per row
                for (unsigned int i{}; i < 4; i++)
                {
                    unsigned char byte;
                    br.Read(byte);

                    //Iterate through each byte to get the Level
                    for (unsigned int j{}; j < 8; j++)
                    {
                        if (byte & m_LevelBitmask[j])
                        {
                            newLevel.AddTilePos(TilePos(column, row));
                            #ifdef PRINT_LEVELS
                            wprintf(L"\x2588");
                            //std::cout << "X";
                            #endif // PRINT_LEVELS
                        }
                        else
                        {
                            #ifdef PRINT_LEVELS
                            wprintf(L" ");
                            //std::cout << " ";
                            #endif // PRINT_LEVELS
                        }
                        ++column;
                    }
                }
                #ifdef PRINT_LEVELS
                wprintf(L"\n");
                //std::cout << "\n";
                #endif // PRINT_LEVELS
                ++row;
            }
            m_Levels.push_back(newLevel);
            #ifdef PRINT_LEVELS
            wprintf(L"\n\n");
            //std::cout << "\n\n";
            #endif // PRINT_LEVELS
        }
        br.CloseFile();
        #ifdef PRINT_LEVELS
        _setmode(_fileno(stdout), _O_TEXT); //Sets print mode back to normal
        #endif // PRINT_LEVELS
        std::cout << "Levels successful read.\n";
        return true;
    }
    std::cout << "Levels failed to read.\n";
    return false;
}

bool LevelReader::ReadEnemies()
{
    BinaryReader br(m_DataPath + "SeperatedEnemyData.dat");
    if (br.OpenFile())
    {
        unsigned int level{1};
        unsigned int enemyCounter{};

        #ifdef PRINT_ENEMIES
        std::cout << "---------BeginOfLevel " << level << "------------\n";
        #endif 

        bool activ = true;
        while (activ)
        {
            if (!br.EndOfFile())
            {
                std::uint_fast8_t byte{};
                br.Read(byte);
                if (byte == m_ZeroBitmask)
                {
                    #ifdef PRINT_ENEMIES
                    std::cout << "---------EndOfLevel " << level << "------------\n\n";
                    #endif
                    
                    ++level;
                    enemyCounter = 0;

                    #ifdef PRINT_ENEMIES
                    if (level <= 100)
                        std::cout << "---------BeginOfLevel " << level << "------------\n";
                    #endif
                }
                else
                {
                    enemyCounter++;
                    //Get Enemy type from first byte
                    EnemyType type = EnemyType::ZenChan;
                    std::uint_fast8_t enemyType{ static_cast<std::uint_fast8_t>(byte & m_EnemyTypeMask)};
                    for (int i{}; i < 8; ++i)
                    {
                        if (enemyType == m_EnemyBitmask[i])
                        {
                            type = m_EnemyTypes[i];
                            break;
                        }
                    }

                    //Print Enemy head information
                    #ifdef PRINT_ENEMIES
                    std::cout << "-----Level(" << level << ") Enemy(" << enemyCounter << ") Type(";
                    switch (type)
                    {
                    case EnemyType::ZenChan: std::cout << "ZenChan"; break;
                    case EnemyType::Mighta: std::cout << "Mighta"; break;
                    case EnemyType::Monsta: std::cout << "Monsta"; break;
                    case EnemyType::Pulpul: std::cout << "Pulpul"; break;
                    case EnemyType::Banebou: std::cout << "Banebou"; break;
                    case EnemyType::Hidegons: std::cout << "Hidegons"; break;
                    case EnemyType::Drunk: std::cout << "Drunk"; break;
                    case EnemyType::Invader: std::cout << "Invader"; break;
                    default: std::cout << "Not existing"; break;
                    }
                    std::cout << ")--------\n";
                    std::cout << "      Byte1[" << std::bitset<8>(byte) << "]\n";
                    #endif // PRINT_ENEMIES

                    //Mask the column value and save value
                    std::uint_fast8_t columnByte{ static_cast<std::uint_fast8_t>((byte & m_ColumnAndRowMask) >> 3) };
                    unsigned int column = (unsigned int)columnByte;


                    //Read second byte (row and unknown bit flags)
                    br.Read(byte);

                    #ifdef PRINT_ENEMIES
                    std::cout << "      Byte2[" << std::bitset<8>(byte) << "]\n";
                    #endif

                    std::uint_fast8_t rowByte{ static_cast<std::uint_fast8_t>((byte & m_ColumnAndRowMask) >> 3) };
                    unsigned int row = (unsigned int)rowByte;

                    
                    //Read third byte (direction and delay)
                    br.Read(byte);

                    #ifdef PRINT_ENEMIES
                    std::cout << "      Byte3[" << std::bitset<8>(byte) << "]\n";
                    #endif

                    std::uint_fast8_t delayByte{ static_cast<std::uint_fast8_t>((byte & m_DelayMask) << 1) };
                    unsigned int delayFrames = (unsigned int)delayByte;
                    float delay = delayFrames * m_ApproxTimePerFrame;


                    #ifdef PRINT_ENEMIES
                    std::cout << "      Column/Row[" << column << "/" << row << "]\n";
                    #endif

                    //Direction
                    Direction direction{};
                    if (byte & m_DirectionMask)
                    {
                        direction = Direction::Left;

                        #ifdef PRINT_ENEMIES
                        std::cout << "      Direction[Left]\n";
                        #endif
                    }
                    else
                    {
                        direction = Direction::Right;

                        #ifdef PRINT_ENEMIES
                        std::cout << "      Direction[Right]\n";
                        #endif
                    }

                    #ifdef PRINT_ENEMIES
                    std::cout << "      Delay[" << delay << "]\n\n";
                    #endif
                    
                    if(!m_Levels.empty())
                        m_Levels[level-1].AddEnemy(EnemyData(type, EnemyPos(column, row), direction, delay));
                }
            }
            else
            {
                activ = false;
            }
        }

        br.CloseFile();
        std::cout << "Enemies successful read.\n";
        return true;
    }
    std::cout << "Enemies failed to read.\n";
    return false;
}
