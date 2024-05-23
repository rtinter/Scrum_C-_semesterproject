#include "StyleManager.hpp"
#include "App.hpp"

int main() {
    commons::StyleManager::loadStyle();
    App::start();
    return 0;
}
