#include "CpuPaddle.h"

CpuPaddle::CpuPaddle() : Paddle() {}

Rectangle CpuPaddle::getRect() const {
    return {
        X_edge_spacing,
        Y - height / 2,
        width,
        height
    };
}

void CpuPaddle::Draw() { //Left side
    float center_X = X_edge_spacing;
    float center_Y = Y - height / 2;

    DrawRectangle((center_X), (center_Y), width, height, WHITE);
    //(X_pos, Y_pos, X_rec, Y_rec, Color). Y rec = screen height/2 - rec height / 2 -> aligns entire rec at center
    //Rectangle pivot -> rectangle's top left (0,0)
}

void CpuPaddle::Update(Ball ball) {
    float ball_Y = ball.get_Y();

    if (ball_Y <= Y - height / 2) Y -= speed * 1.255; //move UP
    if (ball_Y >= Y - height / 2) Y += speed * 1.255; //move DOWN
    
    limit_Y_movement();
}
