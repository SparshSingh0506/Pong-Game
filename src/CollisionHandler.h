#pragma once
#include "Ball.h"
#include "Paddle.h"

class CollisionHandler {    
public:
    void HandleCollision(Ball& ball, Paddle& paddle);
};