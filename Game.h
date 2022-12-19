#ifndef SOULSANCTUM_GAME_H
#define SOULSANCTUM_GAME_H

#include "States/Headers/MainMenuState.h"

class Game{
private:
    // PRIVATE FIELDS
    sf::RenderWindow *window;
    sf::Event sfEvent;
    std::vector<sf::VideoMode> videoModes;
    sf::ContextSettings windowSettings;
    bool fullscreen;
    float dt;
    sf::Clock dtClock;
    std::stack<State*> states;

public:
    // INITIALIZERS
    void initWindow();
    void initStates();

    // CONSTRUCTORS AND DESTRUCTORS
    Game();
    virtual ~Game();

    // UPDATE
    void updateDt();
    void updateSFMLEvents();
    void update();

    // RENDER
    void render();

    // RUN
    void run();
};


#endif //SOULSANCTUM_GAME_H
