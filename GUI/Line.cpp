#include "Headers/Line.h"

// CONSTRUCTORS AND DESTRUCTORS
Line::Line(const std::string& type, float x, float y, float length, float thickness, sf::Color color){
    if (type == "Horizontal") {
        this->line.setSize(sf::Vector2f(length, thickness));
    } else if (type == "Vertical"){
        this->line.setSize(sf::Vector2f(thickness, length));
    }
    this->line.setPosition(x, y);
    this->line.setFillColor(color);
}

Line::~Line() {

}

// RENDER
void Line::render(sf::RenderTarget *target) {
    target->draw(this->line);
}

