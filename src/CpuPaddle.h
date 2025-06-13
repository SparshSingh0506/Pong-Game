#pragma once
#include "Paddle.h"
#include "Ball.h"

class CpuPaddle : public Paddle {
    friend class CollisionHandler;

private:
    Rectangle getRect() const override;

public:
    CpuPaddle();
    
    void Draw();

    void Update(Ball ball);
};