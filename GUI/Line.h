#ifndef SOULSANCTUM_LINE_H
#define SOULSANCTUM_LINE_H

#include "TextBox.h"

class Line {
private:
    sf::RectangleShape line;

public:
    Line(const std::string& type, float x, float y, float length, float thickness, sf::Color color);
    ~Line();

    void render(sf::RenderTarget* target);
};


#endif //SOULSANCTUM_LINE_H
