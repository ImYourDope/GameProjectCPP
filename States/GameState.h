#ifndef SOULSANCTUM_GAMESTATE_H
#define SOULSANCTUM_GAMESTATE_H

#include "PauseState.h"

class GameState: public State {
private:
    //VARIABLES
    sf::RectangleShape background;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    std::map<std::string, Button*> pause_buttons;
    State* pauseState;
    std::vector<sf::RectangleShape> lines;
    bool waveActive;
    std::map<std::string, Socket*> pool;
    int gold, unite_price;


public:
    //CONSTRUCTORS AND DESTRUCTORS
    GameState(sf::RenderWindow* window, std::stack<State*>* states);
    ~GameState() override;

    //INITIALIZERS
    void initPoolIcons();

    //SUPPORT
    void rollPool();

    // UPDATE
    void updateUnite();
    void updateUniteIcon();
    void updatePool();
    void updateGold(int n);
    void updateButtons() override;
    void update(const float& dt) override;

    // RENDER
    void render(sf::RenderTarget* target) override;
};


#endif //SOULSANCTUM_GAMESTATE_H
