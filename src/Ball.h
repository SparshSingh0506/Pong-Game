#pragma once

class Ball {
    friend class CollisionHandler;
    
private:    
    float X, Y, radius, speed_X, speed_Y;
    static const int edge_spacing = 5;

    void ResetPos();

    void rebound();
    
public:
    Ball(float radius, float speed);

    float get_X() const;
    float get_Y() const;
    float get_radius() const;
    float get_speed_X() const;
    float get_speed_Y() const;

    void Draw();

    void Update();
};