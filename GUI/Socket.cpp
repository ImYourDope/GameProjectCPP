#include "Socket.h"

Socket::Socket(float x, float y, float size, sf::Color idleColor, float outline_thickness, sf::Color outlineColor, bool accessible_in, bool accessible_out) {
    this->idleColor = idleColor;
    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(size, size));
    this->shape.setFillColor(this->idleColor);
    this->shape.setOutlineThickness(outline_thickness);
    this->shape.setOutlineColor(outlineColor);
    this->occupied = false;
    this->ready = false;
    this->socketState = SCKT_IDLE;
    this->icon = nullptr;
    this->accessible_in = accessible_in;
    this->accessible_out = accessible_out;
}

Socket::~Socket() {

}

void Socket::render(sf::RenderTarget *target) {
    target->draw(shape);
}




