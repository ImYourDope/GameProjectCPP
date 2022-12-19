#include "Headers/Icon.h"

// CONSTRUCTORS AND DESTRUCTORS
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
    this->hpBoxBack.setFillColor(sf::Color(132, 8, 16));
    this->hpBoxFront.setFillColor(sf::Color(0, 155, 119));
    this->timerBoxBack.setFillColor(sf::Color(169, 169, 169));
    this->timerBoxFront.setFillColor(sf::Color(225, 225, 225));
    this->hpBoxBack.setOutlineThickness(3);
    this->hpBoxBack.setOutlineColor(sf::Color(97, 119, 177));
    this->timerBoxBack.setOutlineThickness(3);
    this->timerBoxBack.setOutlineColor(sf::Color(97, 119, 177));
}

Icon::~Icon() {
    this->socket->icon = nullptr;
}

// UPDATE
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

void Icon::updateBars(){
    this->hpBoxBack.setSize(sf::Vector2f(this->shape.getSize().x, 20));
    this->hpBoxBack.setPosition(sf::Vector2f(this->shape.getPosition().x, this->shape.getPosition().y+this->shape.getSize().y+10));
    if (this->entity != nullptr)
        this->hpBoxFront.setSize(sf::Vector2f(this->shape.getSize().x * this->entity->current_HP / this->entity->HP, 20));
    this->hpBoxFront.setPosition(sf::Vector2f(this->shape.getPosition().x, this->shape.getPosition().y+this->shape.getSize().y+10));
    this->timerBoxBack.setSize(sf::Vector2f(this->shape.getSize().x, 20));
    this->timerBoxBack.setPosition(sf::Vector2f(this->shape.getPosition().x, this->shape.getPosition().y-this->timerBoxBack.getSize().y-10));
    if (this->entity != nullptr)
        this->timerBoxFront.setSize(sf::Vector2f(this->shape.getSize().x*this->entity->timer/100*this->entity->SPD, 20));
    this->timerBoxFront.setPosition(sf::Vector2f(this->shape.getPosition().x, this->shape.getPosition().y-this->timerBoxFront.getSize().y-10));

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

// RENDER
void Icon::renderBars(sf::RenderTarget *target) {
    if (this->shape.getPosition() == this->socket->shape.getPosition()) {
        target->draw(this->hpBoxBack);
        target->draw(this->timerBoxBack);
        target->draw(this->hpBoxFront);
        target->draw(this->timerBoxFront);
    }
}

void Icon::render(sf::RenderTarget *target) {
    target->draw(this->sprite);
    target->draw(this->text);
}


