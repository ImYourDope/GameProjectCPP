#ifndef SOULSANCTUM_GAME_H
#define SOULSANCTUM_GAME_H

#include "States/MainMenuState.h"

class Game{
private:
    //VARIABLES
    sf::RenderWindow *window;
    sf::Event sfEvent;
    std::vector<sf::VideoMode> videoModes;
    sf::ContextSettings windowSettings;
    bool fullscreen;


    float dt;
    sf::Clock dtClock;

    std::stack<State*> states;

    std::map<std::string, int> supportedKeys;

    //INITIALIZERS
    void initWindow();
    void initStates();

public:
    //CONSTRUCTORS AND DESTRUCTORS
    Game();
    virtual ~Game();

    //FUNCTIONS
    void endApplication();

    //UPDATE
    void updateDt();
    void updateSFMLEvents();
    void update();

    //RENDER
    void render();

    //RUN
    void run();
};


#endif //SOULSANCTUM_GAME_H
