#include "PauseState.h"

PauseState::PauseState(sf::RenderWindow* window, std::stack<State*>* states): State(window, states){
    this->initFonts("../Resources/DisposableDroidBB_bld.ttf");
    this->initButtons("../Config/PauseMenu/pausemenu_buttons.ini");
    this->initTextboxes("../Config/PauseMenu/pausemenu_textboxes.ini");
    this->shader.setSize(sf::Vector2f(float(window->getSize().x), float(window->getSize().y)));
    this->shader.setFillColor(sf::Color(20, 20, 20, 150));
    this->background.setSize(sf::Vector2f(float(800), float(1080)));
    this->background.setPosition(560, 0);
    this->background.setFillColor(sf::Color(57,79,137, 255));
    this->background.setOutlineThickness(3);
    this->background.setOutlineColor(sf::Color(97, 119, 177, 255));
}

PauseState::~PauseState(){
    State::~State();
}

void PauseState::updateButtons() {
    if (this->buttons["RESUME_BTN"]->isPressed()){
        this->states->top()->paused = false;
    }
    if (this->buttons["END_GAME_BTN"]->isPressed()){
        this->states->top()->paused = false;
        this->quit = true;
        this->states->top()->quit = true;
    }
}

void PauseState::update(const float &dt) {
    this->updateMousePositions();
    this->updateButtonsState(this->mousePosView);
    this->updateButtons();

}


void PauseState::render(sf::RenderTarget *target) {
    target->draw(shader);
    target->draw(background);
    this->renderButtons(target);
    this->renderTextboxes(target);

}
