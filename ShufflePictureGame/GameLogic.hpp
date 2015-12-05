#ifndef GAMELOGIC_HPP
#define GAMELOGIC_HPP

#include "MiniGame.hpp"
#include <vector>
#include <cstdint>

class GameLogic : public MiniGame
{
public:
    GameLogic();
    ~GameLogic();

    void Initialize()            override;
    void Click(float x, float y) override;
    bool IsComplete() const      override;
    void Render() const          override;
    void Restart()               override;

private:
    void ShuffleIndicies();

private:
    std::vector <std::vector <uint8_t>> m_pics_id;
};

#endif // GAMELOGIC_HPP
