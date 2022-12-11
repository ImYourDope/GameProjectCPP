#ifndef SOULSANCTUM_ICON_H
#define SOULSANCTUM_ICON_H

#include "Button.h"
#include "Socket.h"
#include "../Entity/Entity.h"
class Socket;
class Entity;

enum icon_states{ICON_IDLE, ICON_HOVERED, ICON_TAKEN};

class Icon {
private:
    bool ready;
    float text_size;
    sf::Text text;
    sf::Font* font;
    std::map<std::string, Socket *>* sockets;
    float mouseX, mouseY;


public:
    std::string texturePath;
    sf::Sprite sprite;
    sf::Texture texture;
    sf::RectangleShape shape;
    Entity* entity;
    Socket* socket;
    short unsigned iconState;
    Icon(std::map<std::string, Socket*>* sockets, std::string socket_name, sf::Font* font, std::string texture);
    ~Icon();

    static void updateSize(Icon* icon, Socket* socket);
    void updatePosition();
    void update(sf::Vector2f mousePosition);
    void render(sf::RenderTarget* target);

};


#endif //SOULSANCTUM_ICON_H
