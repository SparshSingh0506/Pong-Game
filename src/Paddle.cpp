#include <raylib.h>
#include "Paddle.h"
    
Paddle::Paddle() { // since protected, child classes wont call it unless explictly made to
    X = GetScreenWidth();
    Y = GetScreenHeight() / 2; // so that division overhead every frame while updating is prevented
}

void Paddle::limit_Y_movement() {
    if (Y - (height / 2 + Y_edge_spacing) <= 0) Y = height / 2 + Y_edge_spacing; 

    if (Y + (height / 2 + Y_edge_spacing) >= GetScreenHeight()) Y = GetScreenHeight() - (height / 2 + Y_edge_spacing);
}

void Paddle::setPaddleSpeed(int speed) {
    Paddle::speed = speed;
}

float Paddle::width = 25;
float Paddle::height = 150;
float Paddle::speed = 5;