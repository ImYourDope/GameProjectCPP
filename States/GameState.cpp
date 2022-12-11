#include "GameState.h"

std::default_random_engine defEngine(time(nullptr));
std::uniform_int_distribution<int> intDistro(1,100);
std::string poolNames[5] = {"ROLL_1", "ROLL_2", "ROLL_3", "ROLL_4", "ROLL_5"};
std::string upgradeNames[3]= {"UPGRADE_1", "UPGRADE_2", "UPGRADE_3"};
std::string textureNames[12] = {"../Textures/Icons_01.png", "../Textures/Icons_02.png", "../Textures/Icons_03.png", "../Textures/Icons_13.png",
                                "../Textures/Icons_14.png", "../Textures/Icons_15.png", "../Textures/Icons_16.png", "../Textures/Icons_17.png",
                                "../Textures/Icons_18.png", "../Textures/Icons_32.png", "../Textures/Icons_33.png", "../Textures/Icons_36.png"};
std::uniform_int_distribution<int> intTexture(0,11);
std::string heroNames[20] = {"Bobby", "Stas", "Vlad", "Abdul", "Joseph", "Hafthor", "Eddy", "Yakamoto", "Hugo", "Pablo", "Alexander", "Pierre",
                           "Magnus", "Amar", "Ludwig", "Felix", "Michael", "Jonathan", "Akira", "Jack"};
std::uniform_int_distribution<int> intName(0,19);
enum pool_states{POOL_SELLING, POOL_BOUGHT};
short unsigned poolStates[5] = {POOL_SELLING, POOL_SELLING, POOL_SELLING, POOL_SELLING, POOL_SELLING};
int unit_price = 5;



// CONSTRUCTOR AND DESTRUCTORS
GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states): State(window, states){
    this->initFonts("../Resources/DisposableDroidBB_bld.ttf");
    this->initButtons("../Config/Game/game_buttons.ini");
    this->initTextboxes("../Config/Game/game_textboxes.ini");
    this->initSockets("../Config/Game/game_sockets.ini");
    this->initLines("../Config/Game/game_lines.ini");
    this->background.setSize(sf::Vector2f(float(window->getSize().x), float(window->getSize().y)));
    this->background.setFillColor(sf::Color(57,79,137, 255));
    this->background.setPosition(0, 500);
    this->backgroundTexture.loadFromFile("../Textures/background.png");
    this->backgroundSprite.setTexture(this->backgroundTexture);
    this->backgroundSprite.setPosition(0, -1);
    this->paused = false;
    this->pauseState = new PauseState(window, states);
    this->waveActive = false;
    this->gold = 0;
    this->unite_price = 0;
    initPoolIcons();
    updateGold(30);
    rollPool();
}

GameState::~GameState(){
    this->paused = false;
    delete this->pauseState;
    State::~State();
}

void GameState::initPoolIcons(){
    for (auto & poolName : poolNames){
        if (this->sockets[poolName]->icon == nullptr){
            this->sockets[poolName]->icon = new Icon(&this->sockets, poolName, &this->font, "../Textures/Icons_01.png");
            this->sockets[poolName]->icon->entity = new Entity(this->sockets[poolName]->icon, &this->font, " ", 1, 0, 0, 0, 0, 0, 0, 0);
            this->icons.push_back( this->sockets[poolName]->icon);
        }
    }
}

void GameState::rollPool(){
    int random;
    for (auto & poolName : poolNames){
        int characteristics[7];
        for (auto & characteristic: characteristics){
            random = intDistro(defEngine);
            if (random <= 3)
                characteristic = -4;
            else if (random <= 8)
                characteristic = -3;
            else if (random <= 24)
                characteristic = -2;
            else if (random <= 40)
                characteristic = -1;
            else if (random <= 60)
                characteristic = 0;
            else if (random <= 76)
                characteristic = 1;
            else if (random <= 92)
                characteristic = 2;
            else if (random <= 97)
                characteristic = 3;
            else
                characteristic = 4;
        }
        int randomTexture = intTexture(defEngine);
        int randomName = intName(defEngine);
        this->sockets[poolName]->icon->entity->updateCharacteristics(heroNames[randomName], textureNames[randomTexture], 1, characteristics[0], characteristics[1], characteristics[2], characteristics[3], characteristics[4], characteristics[5], characteristics[6] );
    }
    for (unsigned short & poolState : poolStates)
        poolState = POOL_SELLING;
}

void GameState::updatePool(){
    for (int i = 0; i<5; i++){
        if (this->sockets["ROLL_"+std::to_string(i+1)]->icon == nullptr && poolStates[i] == POOL_SELLING){
            updateGold(this->gold-unit_price);
            poolStates[i] = POOL_BOUGHT;
        }
    }

}


void GameState::updateButtons() {
    if (this->buttons["PAUSE_BTN"]->isPressed()){
        this->paused = true;
    }
    if (this->buttons["START_WAVE_BTN"]->isPressed()){
    }
    if (this->buttons["REROLL_BTN"]->isPressed() && this->gold >= 3){
        updateGold(this->gold-3);
        initPoolIcons();
        rollPool();
    }
    if (this->buttons["UNITE_BTN"]->isPressed() && this->unite_price != 0 && this->gold >= this->unite_price){
        this->sockets["UPGRADE_4"]->accessible_out = true;
        this->sockets["UPGRADE_1"]->accessible_in = false;
        this->sockets["UPGRADE_2"]->accessible_in = false;
        this->sockets["UPGRADE_3"]->accessible_in = false;
        updateGold(this->gold - this->unite_price);
        this->icons.push_back(this->sockets["UPGRADE_4"]->icon);
        delete this->sockets["UPGRADE_1"]->icon->entity;
        delete this->sockets["UPGRADE_2"]->icon->entity;
        delete this->sockets["UPGRADE_3"]->icon->entity;
        deleteIcon( this->sockets["UPGRADE_1"]->icon);
        deleteIcon( this->sockets["UPGRADE_2"]->icon);
        deleteIcon( this->sockets["UPGRADE_3"]->icon);
    }
}

void GameState::updateUnite(){
    if (this->unite_price != 0){
        this->unite_price = 0;
        this->buttons["UNITE_BTN"]->text.setString("Unite");
        this->buttons["UNITE_BTN"]->text.setPosition(this->buttons["UNITE_BTN"]->shape.getPosition().x+(this->buttons["UNITE_BTN"]->shape.getGlobalBounds().width-2*this->buttons["UNITE_BTN"]->outlineThickness)/2.f-this->buttons["UNITE_BTN"]->text.getGlobalBounds().width/2.f, this->buttons["UNITE_BTN"]->shape.getPosition().y+(this->buttons["UNITE_BTN"]->shape.getGlobalBounds().height-2*this->buttons["UNITE_BTN"]->outlineThickness)/2.f-this->buttons["UNITE_BTN"]->textSize*11/40-this->buttons["UNITE_BTN"]->textSize*9/20);
    }
    if (this->sockets["UPGRADE_1"]->icon != nullptr && this->sockets["UPGRADE_2"]->icon != nullptr && this->sockets["UPGRADE_3"]->icon != nullptr){
        if ((this->sockets["UPGRADE_1"]->icon->entity->rank == this->sockets["UPGRADE_2"]->icon->entity->rank) && (this->sockets["UPGRADE_1"]->icon->entity->rank == this->sockets["UPGRADE_3"]->icon->entity->rank)){
            this->unite_price = 10*pow(3,(this->sockets["UPGRADE_1"]->icon->entity->rank-1));
            this->buttons["UNITE_BTN"]->text.setString("Unite ("+std::to_string(unite_price)+"G)");
            this->buttons["UNITE_BTN"]->text.setPosition(this->buttons["UNITE_BTN"]->shape.getPosition().x+(this->buttons["UNITE_BTN"]->shape.getGlobalBounds().width-2*this->buttons["UNITE_BTN"]->outlineThickness)/2.f-this->buttons["UNITE_BTN"]->text.getGlobalBounds().width/2.f, this->buttons["UNITE_BTN"]->shape.getPosition().y+(this->buttons["UNITE_BTN"]->shape.getGlobalBounds().height-2*this->buttons["UNITE_BTN"]->outlineThickness)/2.f-this->buttons["UNITE_BTN"]->textSize*11/40-this->buttons["UNITE_BTN"]->textSize*9/20);
            if (this->sockets["UPGRADE_4"]->icon == nullptr) {
                this->sockets["UPGRADE_4"]->icon = new Icon(&this->sockets, "UPGRADE_4", &this->font,
                                                            this->sockets["UPGRADE_1"]->icon->texturePath);
                this->sockets["UPGRADE_4"]->icon->entity = new Entity(this->sockets["UPGRADE_4"]->icon, &this->font,
                                                                      this->sockets["UPGRADE_1"]->icon->entity->name,
                                                                      this->sockets["UPGRADE_1"]->icon->entity->rank +
                                                                      1,0, 0, 0, 0, 0, 0, 0);
            } else {
                updateUniteIcon();
            }
        }
    } else if (this->sockets["UPGRADE_4"]->icon != nullptr && !this->sockets["UPGRADE_4"]->accessible_out){
        delete this->sockets["UPGRADE_4"]->icon->entity;
        deleteIcon( this->sockets["UPGRADE_4"]->icon);
    }
    if (this->sockets["UPGRADE_4"]->icon == nullptr){
        this->sockets["UPGRADE_1"]->accessible_in = true;
        this->sockets["UPGRADE_2"]->accessible_in = true;
        this->sockets["UPGRADE_3"]->accessible_in = true;
        this->sockets["UPGRADE_4"]->accessible_out = false;
    }
}

void GameState::updateUniteIcon(){
    this->sockets["UPGRADE_4"]->icon->entity->updateCharacteristics(this->sockets["UPGRADE_1"]->icon->entity->name, this->sockets["UPGRADE_1"]->icon->texturePath, this->sockets["UPGRADE_1"]->icon->entity->rank+1,
                                                                    this->sockets["UPGRADE_1"]->icon->entity->bulky + this->sockets["UPGRADE_2"]->icon->entity->bulky + this->sockets["UPGRADE_3"]->icon->entity->bulky,
                                                                    this->sockets["UPGRADE_1"]->icon->entity->strong + this->sockets["UPGRADE_2"]->icon->entity->strong + this->sockets["UPGRADE_3"]->icon->entity->strong,
                                                                    this->sockets["UPGRADE_1"]->icon->entity->lucky + this->sockets["UPGRADE_2"]->icon->entity->lucky + this->sockets["UPGRADE_3"]->icon->entity->lucky,
                                                                    this->sockets["UPGRADE_1"]->icon->entity->precise + this->sockets["UPGRADE_2"]->icon->entity->precise + this->sockets["UPGRADE_3"]->icon->entity->precise,
                                                                    this->sockets["UPGRADE_1"]->icon->entity->agile + this->sockets["UPGRADE_2"]->icon->entity->agile + this->sockets["UPGRADE_3"]->icon->entity->agile,
                                                                    this->sockets["UPGRADE_1"]->icon->entity->swift + this->sockets["UPGRADE_2"]->icon->entity->swift + this->sockets["UPGRADE_3"]->icon->entity->swift,
                                                                    this->sockets["UPGRADE_1"]->icon->entity->inspiring + this->sockets["UPGRADE_2"]->icon->entity->inspiring + this->sockets["UPGRADE_3"]->icon->entity->inspiring

    );
}

void GameState::updateGold(int n){
    this->gold = n;
    this->textboxes["GOLD_VALUE"]->text.setString(std::to_string(n));
    if (this->gold >= 5){
        for (auto & poolName : poolNames) {
            this->sockets[poolName]->accessible_out = true;
        }
    } else {
        for (auto & poolName : poolNames) {
            this->sockets[poolName]->accessible_out = false;
        }
    }
}

void GameState::update(const float& dt){
    if(!this->paused) {
        this->updateMousePositions();
        this->updateButtonsState(this->mousePosView);
        this->updateButtons();
        this->updateIcons(this->mousePosView);
        if (this->sockets["UPGRADE_4"]->icon != nullptr) {
            this->sockets["UPGRADE_4"]->icon->update(mousePosView);
            this->sockets["UPGRADE_4"]->icon->entity->update();
        }
        this->updateEntities();
        this->updatePool();
        this->updateUnite();
    }
    else
    {
        this->pauseState->update(dt);
    }
}

// RENDER
void GameState:: render(sf::RenderTarget* target){
    if (!target)
        target = this->window;
    target->draw(this->backgroundSprite);
    target->draw(this->background);
    this->renderLines(target);
    this->renderButtons(target);
    this->renderTextboxes(target);
    this->renderSockets(target);
    if (this->sockets["UPGRADE_4"]->icon != nullptr)
        this->sockets["UPGRADE_4"]->icon->render(target);
    this->renderIcons(target);
    if (this->sockets["UPGRADE_4"]->icon != nullptr)
        this->sockets["UPGRADE_4"]->icon->entity->render(target);
    this->renderEntities(target);
    if (this->paused){
        this->pauseState->render(target);
    }
}


