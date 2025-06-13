//No need to include raylib anymore as all headerfiles have it implemented
#include <string>
#include "GameInit.h"
#include "Globals.h"
#include "Ball.h"
#include "Background.h"
#include "Paddle.h"
#include "PlayerPaddle.h"
#include "CpuPaddle.h"
#include "CollisionHandler.h"
#include "ScoreHandler.h"

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

        EndDrawing();
    }

    CloseWindow();

    return 0;
}