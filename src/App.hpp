#ifndef ATHENA_APP_HPP
#define ATHENA_APP_HPP

#include <string>

class App {

    static const int WINDOW_WIDTH;
    static const int WINDOW_HEIGHT;
    static const std::string TILE;
    static const int FRAME_RATE;
    static bool _showGame;

public:
    static void start();
};

#endif //ATHENA_APP_HPP
