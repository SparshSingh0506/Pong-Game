#pragma once
#include "Paddle.h" //since raylib is included in Paddle.h no need to include here explicitly

class PlayerPaddle : public Paddle {
    friend class CollisionHandler; //friend no inherited so no sense to write in base paddle class

private:
    Rectangle getRect() const override;

public:
    PlayerPaddle();

    void Draw();

    void Update();
};