#include <raylib.h>
#include <string>

void GameInit();

short int PlayerScore = 0, CpuScore = 0;

template<typename T>
void DebugText(T text, int X = 100, int Y = 100);

unsigned short int PlayerScore = 0, CpuScore = 0; //range 0 - 65k

class Background {
private:
    int X_0, Y_0, X_1, Y_1;
    int center_x, center_y, radius;

public:
    Background() {
        X_0 = GetScreenWidth() / 2;
        Y_0 = 0;
        X_1 = GetScreenWidth() / 2;
        Y_1 = GetScreenHeight();
        center_x = GetScreenWidth() / 2;
        center_y = GetScreenHeight() / 2;
        radius = 100;
        }

    void Draw() {
        ClearBackground(BLACK);
        DrawLine(X_0, Y_0, X_1, Y_1, WHITE); //(X_start, Y_start, X_end, Y_end)
        DrawCircleLines(center_x, center_y, radius, WHITE);
    }
};

class Ball {
    friend class CollisionHandler;
    
private:    
    float X, Y, radius, speed_X, speed_Y;
    const int edge_spacing = 5;

    void ResetPos() {
        X = GetScreenWidth() / 2;
        Y = GetScreenHeight() / 2;

        int ballDirections[2] = {-1, 1};
        speed_X *= ballDirections[GetRandomValue(0, 1)];
        speed_Y *= ballDirections[GetRandomValue(0, 1)];
    }

    void rebound() {
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
    
public:
    Ball(float radius, float speed) {
        X = GetScreenWidth() / 2;
        Y = GetScreenHeight() / 2;
        this -> radius = radius;
        speed_X = speed;
        speed_Y = speed;
    }

    float get_X() const { return X; }
    float get_Y() const { return Y; }
    float get_radius() const { return radius; }
    float get_speed_X() const { return speed_X; }
    float get_speed_Y() const {return speed_Y; }

    void Draw() {
        DrawCircle(X, Y, radius, WHITE);
    }

    void Update() {
        X += speed_X; 
        Y += speed_Y;
        //ball moves SE direction at speed speed.

        rebound();
    } 
};

class Paddle {
    friend class CollisionHandler; // to allow access of variables to handler

protected:
    float X, Y;
    static float width, height, speed; //static means common for all paddle & its child objects
    static const int X_edge_spacing = 15, Y_edge_spacing = 15; //only const will make these unique for each object, but common needed - static.
    
    Paddle() { // since protected, child classes wont call it unless explictly made to
        X = GetScreenWidth();
        Y = GetScreenHeight() / 2; // so that division overhead every frame while updating is prevented
    }

    void limit_Y_movement() {
        if (Y - (height / 2 + Y_edge_spacing) <= 0) Y = height / 2 + Y_edge_spacing; 

        if (Y + (height / 2 + Y_edge_spacing) >= GetScreenHeight()) Y = GetScreenHeight() - (height / 2 + Y_edge_spacing);
    }

    virtual Rectangle getRect() const = 0; //pure virtual function for child to define. needed to pass in collision handler.
    //under protected so that child classes have access to override

public:
    static void setPaddleSpeed(int speed) {
        Paddle::speed = speed;
    }
};

class PlayerPaddle : public Paddle {
    friend class CollisionHandler; //friend no inherited so no sense to write in base paddle class

private:
    Rectangle getRect() const override {//Rectangle(x, y, width, height) these can be accessed by .x . y etc
        return {
            X - X_edge_spacing - width,
            Y - height / 2,
            width,
            height
        };
    }

public:
    PlayerPaddle() : Paddle() {} //calling parent's constructor to recieve screenwidth and hieght

    void Draw() { //Right side
        float center_X = X - X_edge_spacing - width;
        float center_Y = Y - height / 2;

        DrawRectangle((center_X), (center_Y), width, height, WHITE);
        //IMPORTANT!!!NOTE: X & Y args have set the origin of rectangle at centre now. Not top left anymore
        //-15 for right distance, and - 25 since rec drawn from top left so its width will be considered for spacing
    }

    void Update() {
        if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) Y -= speed;
        if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) Y += speed;

        limit_Y_movement();        
    }
};

class CpuPaddle : public Paddle {
    friend class CollisionHandler;

private:
    Rectangle getRect() const override {
        return {
            X_edge_spacing,
            Y - height / 2,
            width,
            height
        };
    }

public:
    CpuPaddle() : Paddle() {}

    void Draw() { //Left side
        float center_X = X_edge_spacing;
        float center_Y = Y - height / 2;

        DrawRectangle((center_X), (center_Y), width, height, WHITE);
        //(X_pos, Y_pos, X_rec, Y_rec, Color). Y rec = screen height/2 - rec height / 2 -> aligns entire rec at center
        //Rectangle pivot -> rectangle's top left (0,0)
    }

    void Update(Ball ball) {
        float ball_Y = ball.get_Y();

        if (ball_Y <= Y - height / 2) Y -= speed * 1.255; //move UP
        if (ball_Y >= Y - height / 2) Y += speed * 1.255; //move DOWN
        
        limit_Y_movement();
    }
};

class CollisionHandler {    
public:
    void HandleCollision(Ball& ball, Paddle& paddle) { //Base Paddle as argument also allows child classes to be passed
        const Rectangle paddleRect = paddle.getRect();
        const Vector2 ballDim = {ball.X, ball.Y};
        static const int reboundRadius = ball.radius + 10;// static to avoid redeclaration every frame

        if (CheckCollisionCircleRec(ballDim, reboundRadius, paddleRect)) {
            ball.speed_X *= -1;   
        } 
    }
};

class ScoreHandler {
public:
    void displayScore() {
        DrawText(TextFormat("%i", PlayerScore), 3 * GetScreenWidth() / 4, 20, 80, WHITE);
        DrawText(TextFormat("%i", CpuScore), GetScreenWidth() / 4, 20, 80, WHITE);
    }
};

float Paddle::width = 25;
float Paddle::height = 150;
float Paddle::speed = 5; //static variable needs to be assigned globally

int main() {
    GameInit();

    Paddle::setPaddleSpeed(5);// paddle speed can be set like this & will override default value above
    Background Bg;
    Ball ball(20, 6.65);
    PlayerPaddle player;
    CpuPaddle AI;
    CollisionHandler collHandle;
    ScoreHandler scrHandle;
    
    while (!WindowShouldClose()) { //runs 60 times/s due to FPS set to 60
        BeginDrawing();

        Bg.Draw();
        ball.Draw();
        player.Draw();
        AI.Draw();

        ball.Update();
        player.Update();
        AI.Update(ball); 

        collHandle.HandleCollision(ball, player);
        collHandle.HandleCollision(ball, AI);

        scrHandle.displayScore();

        //DebugText(int(ball.get_Y()));

        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void GameInit() {
    const int screen_width = 1280, screen_height = 800;
    const char* screen_title = "PONG!";
    
    InitWindow(screen_width, screen_height, screen_title);
    SetTargetFPS(60);
}

template<typename T> //can also use auto for C++20+
void DebugText(T text, int X, int Y) {//NOTE: default arguments only need to be in function declaration
    std::string str = std::to_string(text);
    DrawText(str.c_str(), X, Y, 20, RED);
}