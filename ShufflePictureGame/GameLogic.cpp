#include "GameLogic.hpp"
#include <ctime>
#include <cstdlib>
#include <iostream>

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
    //uint8_t counter = 0;
    for(size_t i = 0; i < cRows; ++i)
        for(size_t j = 0; j < cColumns; ++j)
            m_pics_id[i][j] = static_cast<uint8_t>(i * cColumns + j);
    ShuffleIndicies();
}

void GameLogic::Click(float x, float y)
{

}

bool GameLogic::IsComplete() const
{
    for(size_t i = 0; i < cRows; ++i)
        for(size_t j = 0; j < cColumns; ++j)
            if (m_pics_id[i][j] != i * cColumns + j)
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

void GameLogic::SwapBlocks(size_t ai, size_t aj, size_t bi, size_t bj)
{
    if (ai >= cRows || aj >= cColumns || bi >= cRows || bj >= cColumns)
        return;
    std::swap(m_pics_id[ai][aj], m_pics_id[bi][bj]);
}

uint8_t GameLogic::GetTextureId(size_t i, size_t j) const
{
    return m_pics_id[i][j];
}

void GameLogic::ShuffleIndicies()
{
    std::srand(std::time(0));
    for(size_t i = 0; i < cRows; ++i)
        for(size_t j = 0; j < cColumns; ++j)
        {
            uint8_t rand_i = std::rand() % cRows;
            uint8_t rand_j = std::rand() % (cColumns - 1) + std::rand() % 2;
            std::swap(m_pics_id[i][j], m_pics_id[rand_i][rand_j]);
        }
}

std::pair<uint8_t, uint8_t> CalcPosition(uint8_t i, uint8_t j, size_t window_height, size_t window_width, uint8_t block_height, uint8_t block_width)
{
    uint8_t x, y;
    x = i * window_height / block_height;
    y = j * window_width / block_width;
    return std::make_pair(x, y);
}
