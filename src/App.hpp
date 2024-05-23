//
// Created by zepi on 16.05.24.
//

#ifndef ATHENA_APP_HPP
#define ATHENA_APP_HPP

#include <string>

class App {
public:

    static void start();

private:
    static const int _windowWidth;
    static const int _windowHeight;
    static const std::string _title;
    static const int _frameRate;
};


#endif //ATHENA_APP_HPP
