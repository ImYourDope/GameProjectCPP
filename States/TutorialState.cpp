#include "Headers/TutorialState.h"

// CONSTRUCTORS AND DESTRUCTORS
TutorialState::TutorialState(sf::RenderWindow *window,
                             std::stack<State *> *states, float* dt) : State(window, states, dt) {
    this->initFonts("../Resources/DisposableDroidBB_bld.ttf");
    this->initButtons("../Config/Tutorial/tutorial_buttons.ini");
    this->initTextboxes("../Config/Tutorial/tutorial_textboxes.ini");
    this->background.setSize(sf::Vector2f(float(window->getSize().x), float(window->getSize().y)));
    this->background.setFillColor(sf::Color(57,79,137, 255));
}

TutorialState::~TutorialState() = default;

// UPDATE
void TutorialState::updateButtons() {
    if (this->buttons["BACK_TO_MENU_BTN"]->isPressed()){
        this->quit = true;
    }
}

void TutorialState::update(const float &dt) {
    this->updateMousePositions();
    this->updateButtonsState(this->mousePosView);
    this->updateButtons();
}

// RENDER
void TutorialState::render(sf::RenderTarget *target) {
    if (!target)
        target = this->window;
    target->draw(background);
    this->renderButtons(target);
    this->renderTextboxes(target);
}


