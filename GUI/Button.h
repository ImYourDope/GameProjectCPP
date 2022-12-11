#ifndef SOULSANCTUM_BUTTON_H
#define SOULSANCTUM_BUTTON_H

#include "Line.h"


enum button_states{BTN_IDLE = 0, BTN_ACTIVE, BTN_HOVERED};

class Button {
private:
    short unsigned buttonState;
    bool ready;
    sf::Font* font;
    sf::Color idleColor;
    sf::Color hoverColor;



public:
    int textSize, outlineThickness;
    sf::Text text;
    sf::RectangleShape shape;
    // CONSTRUCTORS AND DESTRUCTORS
    Button(float x, float y, float width, float height, sf::Font* font, const std::string& text, float text_size, sf::Color idleColor, sf::Color hoverColor, float outline_thickness, sf::Color outlineColor);
    virtual ~Button();

    // FUNCTIONS
    bool isPressed() const;

    // UPDATE
    void update(sf::Vector2f mousePosition);

    // RENDER
    void render(sf::RenderTarget* target);

};


#endif //SOULSANCTUM_BUTTON_H
