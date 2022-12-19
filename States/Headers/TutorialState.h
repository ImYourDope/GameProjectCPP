#ifndef SOULSANCTUM_TUTORIALSTATE_H
#define SOULSANCTUM_TUTORIALSTATE_H

#include "GameState.h"

class TutorialState: public State {
private:
    // PRIVATE FIELDS
    sf::RectangleShape background;

public:
    // CONSTRUCTORS AND DESTRUCTORS
    TutorialState(sf::RenderWindow* window, std::stack<State*>* states, float* dt);
    ~TutorialState() override;

    // UPDATE
    void updateButtons() override;
    void update(const float& dt) override;

    // RENDER
    void render(sf::RenderTarget* target) override;
};


#endif //SOULSANCTUM_TUTORIALSTATE_H
