#include <raylib.h>
#include "Background.h"

Background::Background() {
    X_0 = GetScreenWidth() / 2;
    Y_0 = 0;
    X_1 = GetScreenWidth() / 2;
    Y_1 = GetScreenHeight();
    center_x = GetScreenWidth() / 2;
    center_y = GetScreenHeight() / 2;
    radius = 100;
    }

void Background::Draw() {
    ClearBackground(BLACK);
    DrawLine(X_0, Y_0, X_1, Y_1, WHITE); //(X_start, Y_start, X_end, Y_end)
    DrawCircleLines(center_x, center_y, radius, WHITE);
}
