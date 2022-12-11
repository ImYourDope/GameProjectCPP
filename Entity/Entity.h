#ifndef SOULSANCTUM_ENTITY_H
#define SOULSANCTUM_ENTITY_H

#include "../GUI/Icon.h"
class Icon;

class Entity {
private:
    sf::Font* font;
    Icon* icon;
    float current_HP;
    sf::RectangleShape hoverBox;
    std::map<std::string, TextBox*> hoverTextBoxes;

public:
    bool updated;
    int bulky, strong, lucky, precise,  agile, swift, inspiring;
    int rank;
    std::string name;
    float HP, ATK, CR, CD, EV, SPD, LS;

    Entity(Icon* icon, sf::Font* font, std::string name, int rank, int bulky, int strong, int lucky, int precise, int agile, int swift, int inspiring);
    ~Entity();

    void initHoverBox();

    void updateCharacteristics(std::string name, std::string texture_name, int rank, int bulky, int strong, int lucky, int precise, int agile, int swift, int inspiring);
    void updateStats();
    void updateTextBoxes();
    void update();
    void render(sf::RenderTarget* target);

};


#endif //SOULSANCTUM_ENTITY_H
