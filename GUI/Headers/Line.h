#ifndef SOULSANCTUM_LINE_H
#define SOULSANCTUM_LINE_H

#include "TextBox.h"

class Line {
private:
    // PRIVATE FIELDS
    sf::RectangleShape line;

public:
    // CONSTRUCTORS AND DESTRUCTORS
    Line(const std::string& type, float x, float y, float length, float thickness, sf::Color color);
    ~Line();

    // RENDER
    void render(sf::RenderTarget* target);
};


#endif //SOULSANCTUM_LINE_H
