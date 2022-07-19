/*
    3180082 - KOLOKYTHA ATHANASIA
    3180084 - KORILI GKOLFO-GEORGIA
*/

#include "graphics.h"
#include "game.h"
#include "config.h"

void update(float ms)
{
    Game* game = reinterpret_cast<Game*>(graphics::getUserData());
    if (game)
        game->update();
}

void draw()
{
    Game* game = reinterpret_cast<Game*>(graphics::getUserData());
    if (game)
        game->draw();
}

int main()
{
    Game mygame;
    // Name of the window
    graphics::createWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Space Invaders");

    graphics::setUserData(&mygame);

    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    mygame.init();
    graphics::startMessageLoop();

    return 0;
}