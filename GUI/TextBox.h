#ifndef SOULSANCTUM_TEXTBOX_H
#define SOULSANCTUM_TEXTBOX_H

#include <vector>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <stack>
#include <map>
#include <utility>
#include <cmath>
#include <ctime>
#include <random>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>


class TextBox {
private:
    sf::Font* font;
    int text_size;
public:
    sf::Text text;
    float x, y;
    TextBox(float x, float y, sf::Font* font, const std::string& text, int text_size);
    ~TextBox();

    void setPos(float x, float y);

    void render(sf::RenderTarget * target);
};


#endif //SOULSANCTUM_TEXTBOX_H
