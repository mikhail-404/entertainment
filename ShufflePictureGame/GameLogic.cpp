#include "GameLogic.hpp"
#include <ctime>
#include <cstdlib>

GameLogic::GameLogic(size_t width, size_t height)
    : m_window_width(width)
    , m_window_height(height)
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

void GameLogic::SwapBlocks(uint8_t first_block, uint8_t second_block)
{
    std::pair <uint8_t, uint8_t> a = CalcPosition(first_block / cColumns,
                                                  first_block % cColumns,
                                                  m_window_height,
                                                  m_window_width,
                                                  cRows, cColumns);

    std::pair <uint8_t, uint8_t> b = CalcPosition(second_block / cColumns,
                                                  second_block % cColumns,
                                                  m_window_height,
                                                  m_window_width,
                                                  cRows, cColumns);

    std::swap(m_pics_id[a.first][a.second], m_pics_id[b.first][b.second]);
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
