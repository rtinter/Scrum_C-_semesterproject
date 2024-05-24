#ifndef ATHENA_APP_HPP
#define ATHENA_APP_HPP

#include <string>

class App {

    static const int kWINDOW_WIDTH;
    static const int kWINDOW_HEIGHT;
    static const std::string kTITLE;
    static const int kFRAME_RATE;
    static bool _showGame;

public:
    static void start();
};

#endif //ATHENA_APP_HPP
