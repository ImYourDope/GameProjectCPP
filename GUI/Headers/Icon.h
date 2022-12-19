#ifndef SOULSANCTUM_ICON_H
#define SOULSANCTUM_ICON_H

#include "Button.h"
#include "Socket.h"
#include "../../Entity/Entity.h"
class Socket;
class Entity;

enum icon_states{ICON_IDLE, ICON_HOVERED, ICON_TAKEN};

class Icon {
private:
    // PRIVATE FIELDS
    bool ready;
    float text_size;
    sf::Font* font;
    std::map<std::string, Socket *>* sockets;
    float mouseX, mouseY;


public:
    // PUBLIC FIELDS
    sf::Text text;
    std::string texturePath;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::RectangleShape shape, hpBoxBack, hpBoxFront, timerBoxBack, timerBoxFront;
    Entity* entity;
    Socket* socket;
    short unsigned iconState;

    // CONSTRUCTORS AND DESTRUCTORS
    Icon(std::map<std::string, Socket*>* sockets, std::string socket_name, sf::Font* font, std::string texture);
    ~Icon();

    // UPDATE
    void updateBars();
    static void updateSize(Icon* icon, Socket* socket);
    void updatePosition();
    void update(sf::Vector2f mousePosition);

    // RENDER
    void renderBars(sf::RenderTarget* target);
    void render(sf::RenderTarget* target);

};


#endif //SOULSANCTUM_ICON_H
