#ifndef SOULSANCTUM_GAMESTATE_H
#define SOULSANCTUM_GAMESTATE_H

#include "PauseState.h"

enum zone_states{FIGHTING, LOST, WON};

class GameState: public State {
private:
    // PRIVATE FIELDS
    sf::RectangleShape background, gameOverBackground;
    TextBox *gameOverTitle, *gameOverWave, *gameOverText, *gameOverCountdown;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    std::map<std::string, Button*> pause_buttons;
    State* pauseState;
    std::vector<sf::RectangleShape> lines;
    bool waveActive;
    short unsigned zone1_state, zone2_state, zone3_state, game_state;
    std::map<std::string, Socket*> pool;
    int gold, mine_income, mine_upgrade_price, mine_lvl, unite_price, wave;
    int zone1_hp, zone2_hp, zone3_hp;
    float gameOverTimer;


public:
    // INITIALIZERS
    void initEnemies();
    void initPoolIcons();

    // CONSTRUCTORS AND DESTRUCTORS
    GameState(sf::RenderWindow* window, std::stack<State*>* states, float* dt);
    ~GameState() override;

    // FUNCTIONS
    void targeting();
    void enemyCheck();
    void rollEnemies();
    void rollPool();
    void startWave();
    void checkForWaveEnd();
    void endWave();

    // UPDATE
    void updateCountdown();
    void updateFightBars();
    void updateModifiers();
    void updateWaveNumber();
    void updatePool();
    void updateMine();
    void updateLocationsHP();
    void updateUnite();
    void updateUniteIcon();
    void updateGold(int n);
    void updateButtons() override;
    void update(const float& dt) override;

    // RENDER
    void renderFightBars(sf::RenderTarget* target);
    void render(sf::RenderTarget* target) override;
};

#endif //SOULSANCTUM_GAMESTATE_H
