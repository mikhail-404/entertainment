#ifndef MINIGAME_HPP
#define MINIGAME_HPP

class MiniGame
{
public:
    virtual ~MiniGame()                  = 0;
    virtual void Initialize()            = 0;
    virtual void Click(float x, float y) = 0;
    virtual bool IsComplete() const      = 0;
    virtual void Render() const          = 0;
    virtual void Restart()               = 0;

public:
    static const int cTextureId = 0;
    static const int cColumns   = 2;
    static const int cRows      = 2;
};

inline MiniGame::~MiniGame() {}

#endif // MINIGAME_HPP

