#include "Button.h"

// CONSTRUCTORS AND DESTRUCTORS

Button::Button(float x, float y, float width, float height, sf::Font* font, const std::string& text, float text_size, sf::Color idleColor, sf::Color hoverColor, float outline_thickness, sf::Color outlineColor){
    this->buttonState = BTN_IDLE;
    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->textSize = text_size;
    this->outlineThickness = outline_thickness;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(this->idleColor);
    this->shape.setOutlineThickness(outline_thickness);
    this->shape.setOutlineColor(outlineColor);

    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(text_size);
    this->text.setPosition(this->shape.getPosition().x+(this->shape.getGlobalBounds().width-2*outline_thickness)/2.f-this->text.getGlobalBounds().width/2.f, this->shape.getPosition().y+(this->shape.getGlobalBounds().height-2*outline_thickness)/2.f-text_size*11/40-text_size*9/20);
    this->buttonState = BTN_IDLE;

}

Button::~Button(){

}

// FUNCTIONS
bool Button::isPressed() const{
    if(this->buttonState == BTN_ACTIVE)
        return true;
    return false;
}

// UPDATE
void Button::update(const sf::Vector2f mousePosition){
    if(this->shape.getGlobalBounds().contains(mousePosition)){
        this->buttonState = BTN_HOVERED;
        if(!sf::Mouse::isButtonPressed(sf::Mouse::Left))
            this->ready = true;
        if((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && this->ready){
            this->buttonState = BTN_ACTIVE;
            this->ready = false;
        }
    } else {
        this->buttonState = BTN_IDLE;
        this->ready = false;
    }

    switch(this->buttonState){
        case BTN_IDLE:
            this->shape.setFillColor(this->idleColor);
            break;
        case BTN_HOVERED:
            this->shape.setFillColor(this->hoverColor);
            break;
        case BTN_ACTIVE:
            this->shape.setFillColor(this->hoverColor);
            break;
        default:
            this->shape.setFillColor(sf::Color::Red);
            break;
    }
}

// RENDER
void Button::render(sf::RenderTarget* target){
    target->draw(this->shape);
    target->draw(this->text);
}