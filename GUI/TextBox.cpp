#include "TextBox.h"

TextBox::TextBox(float x, float y, sf::Font* font, const std::string& text, int text_size) {
    this->text_size = text_size;
    this->font = font;
    this->text.setFont(*this->font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(text_size);
    this->text.setPosition(x, y-text_size*9/20);
}

TextBox::~TextBox() {

}

void TextBox::setPos(float x, float y){
    this->text.setPosition(x, y-text_size*9/20);
}

void TextBox::render(sf::RenderTarget *target) {
    target->draw(text);
}
