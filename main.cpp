#include "gamecontext.hpp"

#include "splashstate.hpp"
#include "menustate.hpp"
#include "gamestate.hpp"
#include "statisticsstate.hpp"
#include "finalscreenstate.hpp"
#include "log.hpp"

int main(int argc, char* argv[])
{
    plog::init(plog::debug, "log.txt");

    PLOG_DEBUG << "START LOGGING";

    Context* thegame = new GameContext;

    thegame->addState(new Splash);
    thegame->addState(new Menu);
    thegame->addState(new Game);
    thegame->addState(new StatisticsState);
    thegame->addState(new FinalScreen);

    if (thegame->setState("splash")) {
        thegame->run();
    }

    delete thegame;

    return EXIT_SUCCESS;
}
