#ifndef GAMELOGIC_HPP
#define GAMELOGIC_HPP

#include "MiniGame.hpp"
#include <vector>
#include <cstdint>
#include <cstddef>

class GameLogic : public MiniGame
{
public:
    GameLogic();
    ~GameLogic();

    //
    void Initialize()            override;
    void Click(float x, float y) override;
    bool IsComplete() const      override;
    void Render() const          override;
    void Restart()               override;
    //
    void SwapBlocks(size_t ai, size_t aj, size_t bi, size_t bj);
    uint8_t GetTextureId(size_t i, size_t j) const;

private:
    void ShuffleIndicies();

private:
    std::vector <std::vector <uint8_t>> m_pics_id;
};

std::pair <uint8_t, uint8_t> CalcPosition(uint8_t i,
                                          uint8_t j,
                                          size_t  window_height,
                                          size_t  window_width,
                                          uint8_t block_height,
                                          uint8_t block_width);

#endif // GAMELOGIC_HPP
