#pragma once

#include <raylib.h>

class Paddle {
    friend class CollisionHandler; // to allow access of variables to handler

protected:
    float X, Y;
    static float width, height, speed; //static means common for all paddle & its child objects
    static const int X_edge_spacing = 15, Y_edge_spacing = 15; //only const will make these unique for each object, but common needed - static.
    
    Paddle();

    void limit_Y_movement();

    virtual Rectangle getRect() const = 0; //pure virtual function for child to define. needed to pass in collision handler.
    //under protected so that child classes have access to override

public:
    static void setPaddleSpeed(int speed);
};