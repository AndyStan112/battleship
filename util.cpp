#include <string>
#include <Array>
#include <iostream>
#include <ctime>
#include <random>
#include <sstream>
#include <string>
#include <algorithm>
std::string get_uuid()
{
    static std::mt19937 rng(std::time(nullptr));
    std::uniform_int_distribution<int> dist(0, 15);

    const char *v = "0123456789abcdef";
    const bool dash[] = {0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0};

    std::string res;
    for (int i = 0; i < 16; i++)
    {
        if (dash[i])
            res += "-";
        res += v[dist(rng)];
        res += v[dist(rng)];
    }
    return res;
};
enum TileState
{
    MISS,
    HIT,
    WATER_TILE,
    SHIP
};
enum GameState
{
    MAIN,
    HOST,
    PLACING,
    JOIN,
    TURN,
    QUIT,
    WAITING,
};