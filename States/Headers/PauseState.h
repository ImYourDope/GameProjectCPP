#ifndef SOULSANCTUM_PAUSESTATE_H
#define SOULSANCTUM_PAUSESTATE_H

#include "State.h"

class PauseState: public State {
private:
    // PRIVATE FIELDS
    sf::RectangleShape background;
    sf::RectangleShape shader;

public:
    // CONSTRUCTORS AND DESTRUCTORS
    PauseState(sf::RenderWindow* window, std::stack<State*>* states, float* dt);
    ~PauseState() override;

    // UPDATE
    void updateButtons() override;
    void update(const float& dt) override;

    // RENDER
    void render(sf::RenderTarget* target) override;
};

#endif //SOULSANCTUM_PAUSESTATE_H
