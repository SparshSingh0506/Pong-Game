#include "PlayerPaddle.h"

PlayerPaddle::PlayerPaddle() : Paddle() {} //calling parent's constructor to recieve screenwidth and hieght

Rectangle PlayerPaddle::getRect() const {//Rectangle(x, y, width, height) these can be accessed by .x . y etc
    return {
        X - X_edge_spacing - width,
        Y - height / 2,
        width,
        height
    };
}

void PlayerPaddle::Draw() { //Right side
    float center_X = X - X_edge_spacing - width;
    float center_Y = Y - height / 2;

    DrawRectangle((center_X), (center_Y), width, height, WHITE);
    //IMPORTANT!!!NOTE: X & Y args have set the origin of rectangle at centre now. Not top left anymore
    //-15 for right distance, and - 25 since rec drawn from top left so its width will be considered for spacing
}

void PlayerPaddle::Update() {
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) Y -= speed;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) Y += speed;

    limit_Y_movement();        
}
