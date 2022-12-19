#ifndef SOULSANCTUM_TEXTBOX_H
#define SOULSANCTUM_TEXTBOX_H

#include "Includes.h"

class TextBox {
private:
    // PRIVATE FIELDS
    sf::Font* font;
    int text_size;

public:
    // PUBLIC FIELDS
    sf::Text text;
    float x, y;

    // CONSTRUCTORS AND DESTRUCTORS
    TextBox(float x, float y, sf::Font* font, const std::string& text, int text_size);
    ~TextBox();

    // FUNCTIONS
    void setPos(float x, float y);

    // RENDER
    void render(sf::RenderTarget * target);
};


#endif //SOULSANCTUM_TEXTBOX_H
