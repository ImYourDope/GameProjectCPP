#include "Game.h"

//STATIC

//INITIALIZERS
void Game::initWindow() {

    std::ifstream ifs("../Config/window.ini");
    this->videoModes = sf::VideoMode::getFullscreenModes();

    std::string title = "Soul Sanctum";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    this->fullscreen = false;
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    unsigned antialiasing_level = 0;

    if (ifs.is_open()){
        std::getline(ifs, title);
        ifs >> fullscreen;
        ifs >> window_bounds.width >> window_bounds.height;
        ifs >> framerate_limit;
        ifs >> vertical_sync_enabled;
        ifs >> antialiasing_level;
    }

    ifs.close();

    this->windowSettings.antialiasingLevel = antialiasing_level;
    if (this->fullscreen)
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, this->windowSettings);
    else
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, this->windowSettings);
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);

}



void Game:: initStates(){
    this->states.push(new MainMenuState(this->window, &this->states));
}



//CONSTRUCTORS AND DESTRUCTORS
Game::Game() {
    this->initWindow();
    this->initStates();
}

Game::~Game(){
    delete this->window;

    while(!this->states.empty()) {
        delete this->states.top();
        this->states.pop();
    }
}

//FUNCTIONS

void Game::endApplication(){

}

//UPDATE
void Game::updateDt() {
    this->dt = this->dtClock.restart().asSeconds();

}

void Game::updateSFMLEvents() {
    while(this->window->pollEvent(this->sfEvent)){
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
}

void Game::update() {
    this->updateSFMLEvents();

    if (!this->states.empty()) {
        this->states.top()->update(this->dt);
        if(this->states.top()->getQuit()){
            delete this->states.top();
            this->states.pop();
        }
    }
    else {
        this->endApplication();
        this->window->close();
    }
}

//RENDER
void Game::render() {
    this->window->clear();

    if(!this->states.empty())
        this->states.top()->render(this->window);

    this->window->display();
}

//RUN
void Game::run() {
    while (this->window->isOpen()){
        this->updateDt();
        this->update();
        this->render();
    }
}



