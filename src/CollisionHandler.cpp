#include "CollisionHandler.h"

void CollisionHandler::HandleCollision(Ball& ball, Paddle& paddle) { //Base Paddle as argument also allows child classes to be passed
    const Rectangle paddleRect = paddle.getRect();
    const Vector2 ballDim = {ball.X, ball.Y};
    static const int reboundRadius = ball.radius + 10;// static to avoid redeclaration every frame

    if (CheckCollisionCircleRec(ballDim, reboundRadius, paddleRect)) {
        ball.speed_X *= -1;   
    } 
}