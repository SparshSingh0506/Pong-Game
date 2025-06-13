#include <raylib.h>
#include "Ball.h"
#include "Globals.h"

void Ball::ResetPos() {
    X = GetScreenWidth() / 2;
    Y = GetScreenHeight() / 2;

    int ballDirections[2] = {-1, 1};
    speed_X *= ballDirections[GetRandomValue(0, 1)];
    speed_Y *= ballDirections[GetRandomValue(0, 1)];
}

void Ball::rebound() {
    if (Y + (radius + edge_spacing) >= GetScreenHeight() || Y - (radius + edge_spacing) <= 0) speed_Y *= -1;

    if (X + (radius + edge_spacing) >= GetScreenWidth()) {
        speed_X *= -1;
        CpuScore ++;
        ResetPos();
    } 

    if (X - (radius + edge_spacing) <= 0) {
        speed_X *= -1;
        PlayerScore ++;
        ResetPos();
    }
}

Ball::Ball(float radius, float speed) {
    X = GetScreenWidth() / 2;
    Y = GetScreenHeight() / 2;
    this -> radius = radius;
    speed_X = speed;
    speed_Y = speed;
}

float Ball::get_X() const { return X; }
float Ball::get_Y() const { return Y; }
float Ball::get_radius() const { return radius; }
float Ball::get_speed_X() const { return speed_X; }
float Ball::get_speed_Y() const {return speed_Y; }

void Ball::Draw() {
    DrawCircle(X, Y, radius, WHITE);
}

void Ball::Update() {
    X += speed_X; 
    Y += speed_Y;
    //ball moves SE direction at speed speed.

    rebound();
} 
