#ifndef SOULSANCTUM_SOCKET_H
#define SOULSANCTUM_SOCKET_H

#include "Icon.h"
class Icon;

enum socket_states{SCKT_IDLE, SCKT_HOVERED};

class Socket {
private:
    // PRIVATE FIELDS
    short unsigned socketState;
    bool ready;
    sf::Color idleColor;

public:
    // PUBLIC FIELDS
    bool occupied, accessible_in, accessible_out;
    bool saved_in, saved_out;
    Icon* icon;
    sf::RectangleShape shape;

    // CONSTRUCTORS AND DESTRUCTORS
    Socket(float x, float y, float size, sf::Color idleColor, float outline_thickness, sf::Color outlineColor, bool accessible_in, bool accessible_out);
    ~Socket();

    // RENDER
    void render(sf::RenderTarget* target);

};

#endif //SOULSANCTUM_SOCKET_H