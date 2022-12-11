#include "State.h"

// CONSTRUCTORS AND DESTRUCTORS
State::State(sf::RenderWindow* window, std::stack<State*>* states){
    this->window = window;
    this->states = states;
    this->quit = false;
    this->iconTaken = nullptr;
}

State::~State(){
    for (const auto& button: buttons){
        delete button.second;
    }
    buttons.clear();
    for (const auto& textbox: textboxes){
        delete textbox.second;
    }
    textboxes.clear();
    for (const auto& socket: sockets){
        delete socket.second;
    }
    sockets.clear();
    for (const auto& icon: icons){
        delete icon;
    }
    icons.clear();
    for (const auto& line: lines){
        delete line;
    }
    lines.clear();
}

// INITIALIZERS
void State::initFonts(const std::string& filename){
    this->font.loadFromFile(filename);
}

void State::initButtons(const std::string& filename){
    std::string elementType;
    std::ifstream ifs(filename);
    float x, y, width, height, text_size, outline_thickness;
    std::string text, name;
    int red, green, blue, alpha;
    sf::Color idleColor, hoverColor, activeColor, outlineColor;

    if (ifs.is_open()) {
        while (!ifs.eof()) {
            std::getline(ifs, elementType);
            if (elementType == "Button") {
                std::getline(ifs, name);
                std::getline(ifs, text);
                ifs >> x >> y >> width >> height;
                ifs >> text_size;
                ifs >> red >> green >> blue >> alpha;
                idleColor = sf::Color(red, green, blue, alpha);
                ifs >> red >> green >> blue >> alpha;
                hoverColor = sf::Color(red, green, blue, alpha);
                ifs >> outline_thickness;
                ifs >> red >> green >> blue >> alpha;
                outlineColor = sf::Color(red, green, blue, alpha);
                this->buttons[name] = new Button(x, y, width, height, &this->font, text, text_size, idleColor,
                                                 hoverColor, outline_thickness, outlineColor);
            }
        }
    }
    ifs.close();
}

void State::initTextboxes(const std::string &filename) {
    std::string elementType;
    std::ifstream ifs(filename);
    float x, y, width, height;
    int text_size;
    std::string text, name;

    if (ifs.is_open()) {
        while (!ifs.eof()) {
            std::getline(ifs, elementType);
            if (elementType == "Textbox") {
                std::getline(ifs, name);
                std::getline(ifs, text);
                ifs >> x >> y;
                ifs >> text_size;
                this->textboxes[name] = new TextBox(x, y, &this->font, text, text_size);
            }
        }
    }
    ifs.close();
}

void State::initSockets(const std::string &filename) {
    std::string elementType;
    std::ifstream ifs(filename);
    float x, y, size, outline_thickness;
    std::string name;
    int red, green, blue, alpha;
    sf::Color idleColor, outlineColor;
    bool accessible_in, accessible_out;

    if (ifs.is_open()) {
        while (!ifs.eof()) {
            std::getline(ifs, elementType);
            if (elementType == "Socket") {
                std::getline(ifs, name);
                ifs >> x >> y;
                ifs >> size;
                ifs >> red >> green >> blue >> alpha;
                idleColor = sf::Color(red, green, blue, alpha);
                ifs >> outline_thickness;
                ifs >> red >> green >> blue >> alpha;
                outlineColor = sf::Color(red, green, blue, alpha);
                ifs >> accessible_in >> accessible_out;
                sockets[name] = new Socket(x, y, size, idleColor, outline_thickness, outlineColor, accessible_in, accessible_out);
            }
        }
    }
    ifs.close();
}

void State::initIcons(const std::string &filename) {
    std::string elementType;
    std::ifstream ifs(filename);
    std::string name, socket_name, texture;

    if (ifs.is_open()) {
        while (!ifs.eof()) {
            std::getline(ifs, elementType);
            if (elementType == "Icon") {
                std::getline(ifs, name);
                std::getline(ifs, socket_name);
                std::getline(ifs, texture);
                this->icons.push_back(new Icon(&this->sockets, socket_name, &this->font, texture));
            }
        }
    }
    ifs.close();
}

void State::initLines(const std::string &filename) {
    std::string elementType;
    std::ifstream ifs(filename);
    std::string type;
    float x, y, length, thickness;
    int red, green, blue, alpha;
    sf::Color color;

    if (ifs.is_open()) {
        while (!ifs.eof()) {
            std::getline(ifs, elementType);
            if (elementType == "Line") {
                std::getline(ifs,type);
                ifs >> length;
                ifs >> x >> y;
                ifs >> thickness;
                ifs >> red >> green >> blue >> alpha;
                color = sf::Color(red, green, blue, alpha);
                this->lines.push_back(new Line(type, x, y, length, thickness, color));
            }
        }
    }
    ifs.close();
}

// FUNCTIONS
const bool &State::getQuit() const{
    return this->quit;
}



// UPDATE
void State::updateMousePositions() {
    this->mousePosScreen = sf::Mouse::getPosition();
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
    this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::updateButtonsState(const sf::Vector2f mousePosition) {
    for (const auto& button: buttons){
        button.second->update(mousePosition);
    }
}

void State::updateIcons(sf::Vector2f mousePosition){
    for (const auto& icon: icons){
        icon->update(mousePosition);
    }
}

void State::updateEntities(){
    for (const auto& icon: icons){
        icon->entity->update();
    }
}

void State::updateButtons(){

}


// RENDER
void State::renderButtons(sf::RenderTarget *target) {
    for (const auto& button: buttons){
        button.second->render(target);
    }
}

void State::renderTextboxes(sf::RenderTarget *target) {
    for (const auto& textbox: textboxes){
        textbox.second->render(target);
    }
}

void State::renderSockets(sf::RenderTarget *target) {
    for (const auto& socket: sockets){
        socket.second->render(target);
    }
}

void State::renderIcons(sf::RenderTarget *target) {
    for (const auto& icon: icons){
        icon->render(target);
    }
    for (const auto& icon: icons){
        if (icon->iconState == ICON_TAKEN)
            icon->render(target);
    }

}

void State::renderEntities(sf::RenderTarget *target) {
    for (const auto& icon: icons){
        icon->entity->render(target);
    }
}

void State::renderLines(sf::RenderTarget *target) {
    for (const auto& line: lines){
        line->render(target);
    }
}

void State::deleteIcon(Icon* icon_) {
    for (int i = 0; i<this->icons.size(); i++){
        if (icons[i] == icon_){
            icons.erase(icons.begin()+i);
        }
    }
    delete icon_;
}













