#ifndef _GAME_STATISTICS_SINGLETON_H_
#define _GAME_STATISTICS_SINGLETON_H_

class GameStatistics
{
public:
    GameStatistics();
    ~GameStatistics();

    void reset();

    void incScores();
    void incFails();
    void incSkips();

    int getScores();
    int getFails();
    int getSkips();
    int getAccuracy();

private:
    int scores;
    int fails;
    int skips;
};


#endif // _GAME_STATISTICS_SINGLETON_H_
