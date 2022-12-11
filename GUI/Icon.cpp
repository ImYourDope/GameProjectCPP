#include "Icon.h"

Icon::Icon(std::map<std::string, Socket*>* sockets, std::string socket_name, sf::Font *font, std::string texturePath) {
    this->socket = sockets->at(socket_name);
    this->iconState = ICON_IDLE;
    this->sockets = sockets;
    this->font = font;
    this->text.setFont(*this->font);
    this->text.setFillColor(sf::Color::White);
    this->text_size = this->socket->shape.getSize().x*8/15;
    this->text.setCharacterSize(text_size);
    this->texturePath = texturePath;
    this->texture.loadFromFile(texturePath);
    this->sprite.setTexture(this->texture);
    this->shape = this->socket->shape;
    this->text.setPosition(this->shape.getPosition().x+(this->shape.getGlobalBounds().width-this->socket->shape.getOutlineThickness()*2)/2.f-this->text.getGlobalBounds().width*9/8/2.f, this->shape.getPosition().y+(this->shape.getGlobalBounds().height-this->socket->shape.getOutlineThickness()*2)/2.f-this->text.getGlobalBounds().height/2.f-text_size/2);
    this->sprite.setPosition(this->shape.getPosition().x, this->shape.getPosition().y);
    this->sprite.setScale((this->shape.getSize().x+this->socket->shape.getOutlineThickness())/this->texture.getSize().x, (this->shape.getSize().y+this->socket->shape.getOutlineThickness())/this->texture.getSize().y);
    this->socket->icon = this;
    this->socket->occupied = true;
    this->ready = false;
}

Icon::~Icon() {
    this->socket->icon = nullptr;
}

void Icon::updateSize(Icon* icon_, Socket* socket_){
    icon_->shape.setSize(socket_->shape.getSize());
    icon_->text_size = socket_->shape.getSize().x*8/15;
    icon_->text.setCharacterSize(icon_->text_size);
    icon_->sprite.setPosition(icon_->shape.getPosition().x, icon_->shape.getPosition().y);
    icon_->sprite.setScale((icon_->shape.getSize().x+icon_->socket->shape.getOutlineThickness())/icon_->texture.getSize().x, (icon_->shape.getSize().y+icon_->socket->shape.getOutlineThickness())/icon_->texture.getSize().x);
}

void Icon::updatePosition(){
    this->shape.setPosition(this->socket->shape.getPosition());
    this->sprite.setPosition(this->shape.getPosition().x, this->shape.getPosition().y);
    this->text.setPosition(this->socket->shape.getPosition().x+(this->shape.getGlobalBounds().width-this->socket->shape.getOutlineThickness()*2)/2.f-this->text.getGlobalBounds().width*9/8/2.f, this->socket->shape.getPosition().y+(this->shape.getGlobalBounds().height-this->socket->shape.getOutlineThickness()*2)/2.f-this->text.getGlobalBounds().height/2.f-text_size/2);

}

void Icon::update(sf::Vector2f mousePosition){
    if (this->iconState == ICON_TAKEN && (sf::Mouse::isButtonPressed(sf::Mouse::Left))){
        this->iconState = ICON_TAKEN;
    } else if (this->iconState == ICON_TAKEN) {
        this->iconState = ICON_IDLE;
        for (const auto& element: *this->sockets){
            if (element.second->shape.getGlobalBounds().contains(mousePosition)){
                if (element.second->icon == nullptr && this->socket->accessible_out && element.second->accessible_in){
                    this->socket->icon = nullptr;
                    this->socket = element.second;
                    this->socket->icon = this;
                    updateSize(this, this->socket);
                    updatePosition();
                } else  if (this->socket->accessible_in && this->socket->accessible_out && element.second->accessible_in && element.second->accessible_out){
                    this->socket->icon = element.second->icon;
                    updateSize(element.second->icon, this->socket);
                    this->socket->icon->socket = this->socket;
                    this->socket = element.second;
                    this->socket->icon = this;
                    updateSize(this, this->socket);
                }
            }
        }
    } else {
        if (this->shape.getGlobalBounds().contains(mousePosition)) {
            this->iconState = ICON_HOVERED;
            if (!sf::Mouse::isButtonPressed(sf::Mouse::Left))
                this->ready = true;
            if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && this->ready) {
                this->iconState = ICON_TAKEN;
                this->mouseX = mousePosition.x - this->shape.getPosition().x;
                this->mouseY = mousePosition.y - this->shape.getPosition().y;
            }
        } else {
            this->iconState = BTN_IDLE;
            this->ready = false;
        }
    }
    if (iconState == ICON_TAKEN && this->socket->accessible_out){
        this->shape.setPosition(mousePosition.x-mouseX, mousePosition.y-mouseY);
        this->sprite.setPosition(this->shape.getPosition().x, this->shape.getPosition().y);
        this->text.setPosition(this->shape.getPosition().x+(this->shape.getGlobalBounds().width-this->socket->shape.getOutlineThickness()*2)/2.f-this->text.getGlobalBounds().width*9/8/2.f, this->shape.getPosition().y+(this->shape.getGlobalBounds().height-this->socket->shape.getOutlineThickness()*2)/2.f-this->text.getGlobalBounds().height/2.f-text_size/2);
    } else {
        updatePosition();
    }
}

void Icon::render(sf::RenderTarget *target) {
    target->draw(this->sprite);
    target->draw(this->text);
}

