#include <raylib.h>
#include "GameInit.h"

void GameInit() {
    const int screen_width = 1280;
    const int screen_height = 800;
    const char* screen_title = "PONG!";
    
    InitWindow(screen_width, screen_height, screen_title);
    SetTargetFPS(60);
}