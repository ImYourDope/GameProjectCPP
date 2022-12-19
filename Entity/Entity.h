#ifndef SOULSANCTUM_ENTITY_H
#define SOULSANCTUM_ENTITY_H

#include "../GUI/Headers/Icon.h"
class Icon;

class Entity {
private:
    // PRIVATE FIELDS
    sf::Font* font;
    Icon* icon;
    sf::RectangleShape hoverBox;
    std::map<std::string, TextBox*> hoverTextBoxes;

public:
    // PUBLIC FIELDS
    bool updated, dead;
    int bulky, strong, lucky, precise,  agile, swift, inspiring;
    int rank;
    std::string name;
    float HP, ATK, CR, CD, EV, SPD, LS;
    float current_HP;
    float timer, texttimer;
    float modifier;
    Entity* target;

    // INITIALIZERS
    void initHoverBox();

    // CONSTRUCTORS AND DESTRUCTORS
    Entity(Icon* icon, sf::Font* font, std::string name, int rank, int bulky, int strong, int lucky, int precise, int agile, int swift, int inspiring);
    ~Entity();

    // FUNCTIONS
    void dealDamage();

    // UPDATE
    void updateTimer(float dt);
    void updateTextTimer(float dt);
    void updateCharacteristics(std::string name, std::string texture_name, int rank, int bulky, int strong, int lucky, int precise, int agile, int swift, int inspiring);
    void updateStats();
    void updateTextBoxes();
    void update();

    // RENDER
    void render(sf::RenderTarget* target);

};


#endif //SOULSANCTUM_ENTITY_H
