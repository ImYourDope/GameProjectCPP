#include "Headers/MainMenuState.h"

// CONSTRUCTOR AND DESTRUCTORS
MainMenuState::MainMenuState(sf::RenderWindow* window, std::stack<State*>* states, float* dt): State(window, states, dt){
    this->initFonts("../Resources/DisposableDroidBB_bld.ttf");
    this->initButtons("../Config/MainMenu/mainmenu_buttons.ini");
    this->initTextboxes("../Config/MainMenu/mainmenu_textboxes.ini");
    this->background.setSize(sf::Vector2f(float(window->getSize().x), float(window->getSize().y)));
    this->background.setFillColor(sf::Color(57,79,137, 255));
}

MainMenuState::~MainMenuState()= default;

// UPDATE
void MainMenuState::updateButtons() {
    if (this->buttons["NEW_GAME_BTN"]->isPressed()){
        this->states->push(new GameState(this->window, this->states, this->dt));
    }
    if (this->buttons["TUTORIAL_BTN"]->isPressed()){
        this->states->push(new TutorialState(this->window, this->states, this->dt));
    }
    if (this->buttons["QUIT_GAME_BTN"]->isPressed()){
        this->quit = true;
    }
}

void MainMenuState::update(const float& dt){
    this->updateMousePositions();
    this->updateButtonsState(this->mousePosView);
    this->updateButtons();
}

// RENDER
void MainMenuState::render(sf::RenderTarget* target){
    if (!target)
        target = this->window;
    target->draw(background);
    this->renderButtons(target);
    this->renderTextboxes(target);
}


