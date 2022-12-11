#ifndef SOULSANCTUM_TUTORIALSTATE_H
#define SOULSANCTUM_TUTORIALSTATE_H

#include "GameState.h"

class TutorialState: public State {
private:
    //VARIABLES
    sf::RectangleShape background;


public:
    //CONSTRUCTORS AND DESTRUCTORS
    TutorialState(sf::RenderWindow* window, std::stack<State*>* states);
    ~TutorialState() override;

    // UPDATE
    void update(const float& dt) override;
    void updateButtons() override;

    // RENDER
    void render(sf::RenderTarget* target) override;
};


#endif //SOULSANCTUM_TUTORIALSTATE_H
