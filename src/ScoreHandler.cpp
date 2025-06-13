#include <raylib.h>
#include "ScoreHandler.h"
#include "Globals.h"


void ScoreHandler::displayScore() {
    DrawText(TextFormat("%i", PlayerScore), 3 * GetScreenWidth() / 4, 20, 80, WHITE);
    DrawText(TextFormat("%i", CpuScore), GetScreenWidth() / 4, 20, 80, WHITE);
}
