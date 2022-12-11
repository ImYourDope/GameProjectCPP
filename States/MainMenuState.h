#ifndef SOULSANCTUM_MAINMENUSTATE_H
#define SOULSANCTUM_MAINMENUSTATE_H

#include "TutorialState.h"

class MainMenuState: public State {
private:
    //VARIABLES
    sf::RectangleShape background;


public:
    //CONSTRUCTORS AND DESTRUCTORS
    MainMenuState(sf::RenderWindow* window, std::stack<State*>* states);
    ~MainMenuState() override;

    //FUNCTIONS

    // UPDATE
    void update(const float& dt) override;
    void updateButtons() override;

    // RENDER
    void render(sf::RenderTarget* target) override;
};


#endif //SOULSANCTUM_MAINMENUSTATE_H
