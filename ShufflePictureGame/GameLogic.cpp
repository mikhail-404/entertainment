#include "GameLogic.hpp"
#include <ctime>
#include <cstdlib>

GameLogic::GameLogic()
{
    std::vector <std::vector <uint8_t> > temp(cRows, std::vector <uint8_t>(cColumns));
    m_pics_id.swap(temp);

    Initialize();
}

GameLogic::~GameLogic()
{

}

void GameLogic::Initialize()
{
    for(size_t i = 0; i < cRows; ++i)
        for(size_t j = 0; j < cColumns; ++j)
            m_pics_id[i][j] = i * cRows + j;
    ShuffleIndicies();
}

void GameLogic::Click(float x, float y)
{

}

bool GameLogic::IsComplete() const
{
    for(size_t i = 0; i < cRows; ++i)
        for(size_t j = 0; j < cColumns; ++j)
            if (m_pics_id[i][j] != i * cRows + j)
                return false;
    return true;
}

void GameLogic::Render() const
{

}

void GameLogic::Restart()
{
    Initialize();
}

void GameLogic::ShuffleIndicies()
{
    std::srand(std::time(0));
    for(size_t i = 0; i < cRows; ++i)
        for(size_t j = 0; j < cColumns; ++j)
        {
            uint8_t rand_i = std::rand() % cRows;
            uint8_t rand_j = std::rand() % (cColumns - 1) + std::rand % 2;
            std::swap(m_pics_id[i][j], m_pics_id[rand_i][rand_j]);
        }
}

