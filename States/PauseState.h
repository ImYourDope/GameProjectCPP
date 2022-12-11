#ifndef SOULSANCTUM_PAUSESTATE_H
#define SOULSANCTUM_PAUSESTATE_H

#include "State.h"

class PauseState: public State {
private:
    sf::RectangleShape background;
    sf::RectangleShape shader;

public:
    PauseState(sf::RenderWindow* window, std::stack<State*>* states);
    ~PauseState() override;

    void updateButtons() override;
    void update(const float& dt) override;

    void render(sf::RenderTarget* target) override;
};


#endif //SOULSANCTUM_PAUSESTATE_H
