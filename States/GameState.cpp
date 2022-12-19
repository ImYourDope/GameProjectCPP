#include "Headers/GameState.h"

// SUPPORT
std::default_random_engine defEngine(time(nullptr));
std::uniform_int_distribution<int> intDistro(1,100);
int enemyTiers[20][3] = {{1, 0, 0}, {2, 0, 0}, {3, 0, 0}, {1, 1, 0}, {2, 1, 0},
                         {3, 1, 0}, {2, 2, 0}, {3, 2, 0}, {2, 3, 0}, {3, 3, 0},
                         {2, 4, 0}, {1, 5, 0}, {4, 2, 1}, {1, 4, 1}, {1, 5, 1},
                         {0, 3, 2}, {0, 4, 2}, {0, 3, 3}, {0, 4, 3}, {0, 4, 4}};
std::string poolSockets[5] = {"ROLL_1", "ROLL_2", "ROLL_3", "ROLL_4", "ROLL_5"};
std::string fightSockets[24] = {"ZONE1_1", "ZONE1_2", "ZONE1_3", "ZONE1_4", "ZONE1_5", "ZONE1_6", "ZONE1_7", "ZONE1_8",
                                "ZONE2_1", "ZONE2_2", "ZONE2_3", "ZONE2_4", "ZONE2_5", "ZONE2_6", "ZONE2_7", "ZONE2_8",
                                "ZONE3_1", "ZONE3_2", "ZONE3_3", "ZONE3_4", "ZONE3_5", "ZONE3_6", "ZONE3_7", "ZONE3_8"};
std::string enemySockets[12] = {"ZONE1_1", "ZONE1_2", "ZONE1_3", "ZONE1_4",
                                "ZONE2_1", "ZONE2_2", "ZONE2_3", "ZONE2_4",
                                "ZONE3_1", "ZONE3_2", "ZONE3_3", "ZONE3_4"};
std::string heroSockets[12] = { "ZONE1_5", "ZONE1_6", "ZONE1_7", "ZONE1_8",
                                "ZONE2_5", "ZONE2_6", "ZONE2_7", "ZONE2_8",
                                "ZONE3_5", "ZONE3_6", "ZONE3_7", "ZONE3_8"};
std::string upgradeNames[3]= {"UPGRADE_1", "UPGRADE_2", "UPGRADE_3"};
std::string heroTextureNames[11] = {"../Textures/Icons_01.png", "../Textures/Icons_03.png", "../Textures/Icons_13.png",
                                    "../Textures/Icons_14.png", "../Textures/Icons_15.png", "../Textures/Icons_16.png", "../Textures/Icons_17.png",
                                    "../Textures/Icons_18.png", "../Textures/Icons_32.png", "../Textures/Icons_33.png", "../Textures/Icons_36.png"};
std::uniform_int_distribution<int> intHeroTexture(0, 10);
std::string heroNames[20] = {"Bobby", "Stas", "Vlad", "Abdul", "Joseph", "Hafthor", "Eddy", "Yakamoto", "Hugo", "Pablo", "Alexander", "Pierre",
                           "Magnus", "Amar", "Ludwig", "Felix", "Michael", "Jonathan", "Akira", "Jack"};
std::uniform_int_distribution<int> intHeroName(0, 19);
std::string enemyNames[18] = {"Gray Wolf", "Bear", "Spider", "Boar", "Horned Beetle", "Bat", "Goblin Warrior", "Goblin Archer", "Toxic Slime",
                            "Rhino Beetle", "Cursed Boar","Bee Queen",  "Goblin Warlord", "Golden Fairy", "Mimic","Cultist", "Rocky",   "Tentacle"};
std::uniform_int_distribution<int> intTier1EnemyName(0,5);
std::uniform_int_distribution<int> intTier2EnemyName(6,11);
std::uniform_int_distribution<int> intTier3EnemyName(12,17);
std::uniform_int_distribution<int> intEnemyPosition(0, 11);
std::string enemyTextureNames[18] = {"../Textures/Icons_06.png", "../Textures/Icons_21.png", "../Textures/Icons_22.png", "../Textures/Icons_30.png", "../Textures/Icons_38.png", "../Textures/Icons_40.png", "../Textures/Icons_08.png", "../Textures/Icons_09.png", "../Textures/Icons_04.png",
                                     "../Textures/Icons_31.png", "../Textures/Icons_35.png", "../Textures/Icons_07.png", "../Textures/Icons_10.png", "../Textures/Icons_19.png", "../Textures/Icons_20.png", "../Textures/Icons_24.png", "../Textures/Icons_26.png", "../Textures/Icons_37.png"};
enum pool_states{POOL_SELLING, POOL_BOUGHT};
short unsigned poolStates[5] = {POOL_SELLING, POOL_SELLING, POOL_SELLING, POOL_SELLING, POOL_SELLING};
int unit_price = 5;
int mine[6] = {5, 8, 12, 17, 23, 30};
int mine_upgrade[5] = {8, 15, 25, 40, 50};

// INITIALIZERS
void GameState::initEnemies(){
    int enemy;
    int position;
    int i;
    for (i = 0; i<enemyTiers[this->wave-1][0]; i++){
        enemy = intTier1EnemyName(defEngine);
        position = intEnemyPosition(defEngine);
        while (this->sockets[enemySockets[position]]->icon != nullptr){
            if (position == 11)
                position = 0;
            else
                position += 1;
        }
        this->sockets[enemySockets[position]]->icon = new Icon(&this->sockets, enemySockets[position], &this->font, enemyTextureNames[enemy]);
        this->icons.push_back(this->sockets[enemySockets[position]]->icon);
        if (enemy == 0)
            this->sockets[enemySockets[position]]->icon->entity = new Entity(this->sockets[enemySockets[position]]->icon, &this->font, enemyNames[enemy], 1,
                                                                             -5, 5, 0, 0, 0, 0, 0);
        else if (enemy == 1)
            this->sockets[enemySockets[position]]->icon->entity = new Entity(this->sockets[enemySockets[position]]->icon, &this->font, enemyNames[enemy], 1,
                                                                             5, -5, 0, 0, 0, 0, 0);
        else if (enemy == 2)
            this->sockets[enemySockets[position]]->icon->entity = new Entity(this->sockets[enemySockets[position]]->icon, &this->font, enemyNames[enemy], 1,
                                                                             0, -5, 5, 0, 0, 0, 0);
        else if (enemy == 3)
            this->sockets[enemySockets[position]]->icon->entity = new Entity(this->sockets[enemySockets[position]]->icon, &this->font, enemyNames[enemy], 1,
                                                                             0, -5, 0, 5, 0, 0, 0);
        else if (enemy == 4)
            this->sockets[enemySockets[position]]->icon->entity = new Entity(this->sockets[enemySockets[position]]->icon, &this->font, enemyNames[enemy], 1,
                                                                             -5, 0, 0, 0, 0, 5, 0);
        else if (enemy == 5)
            this->sockets[enemySockets[position]]->icon->entity = new Entity(this->sockets[enemySockets[position]]->icon, &this->font, enemyNames[enemy], 1,
                                                                             -5, 0, 0, 0, 5, 0, 0);
    }

    for (i = 0; i<enemyTiers[this->wave-1][1]; i++){
        enemy = intTier2EnemyName(defEngine);
        position = intEnemyPosition(defEngine);
        while (this->sockets[enemySockets[position]]->icon != nullptr){
            if (position == 11)
                position = 0;
            else
                position += 1;
        }
        this->sockets[enemySockets[position]]->icon = new Icon(&this->sockets, enemySockets[position], &this->font, enemyTextureNames[enemy]);
        this->icons.push_back(this->sockets[enemySockets[position]]->icon);
        if (enemy == 6)
            this->sockets[enemySockets[position]]->icon->entity = new Entity(this->sockets[enemySockets[position]]->icon, &this->font, enemyNames[enemy], 2,
                                                                             5, 10, 0, 0, 0, 0, 0);
        else if (enemy == 7)
            this->sockets[enemySockets[position]]->icon->entity = new Entity(this->sockets[enemySockets[position]]->icon, &this->font, enemyNames[enemy], 2,
                                                                             0, 0, 10, 5, 0, 0, 0);
        else if (enemy == 8)
            this->sockets[enemySockets[position]]->icon->entity = new Entity(this->sockets[enemySockets[position]]->icon, &this->font, enemyNames[enemy], 2,
                                                                             10, 0, 0, 0, 5, 0, 0);
        else if (enemy == 9)
            this->sockets[enemySockets[position]]->icon->entity = new Entity(this->sockets[enemySockets[position]]->icon, &this->font, enemyNames[enemy], 2,
                                                                             0, 0, 5, 0, 0, 10, 0);
        else if (enemy == 10)
            this->sockets[enemySockets[position]]->icon->entity = new Entity(this->sockets[enemySockets[position]]->icon, &this->font, enemyNames[enemy], 2,
                                                                             5, 5, 0, 10, 0, 5, 0);
        else if (enemy == 11)
            this->sockets[enemySockets[position]]->icon->entity = new Entity(this->sockets[enemySockets[position]]->icon, &this->font, enemyNames[enemy], 2,
                                                                             0, 0, 0, 0, 10, 5, 0);
    }
    for (i = 0; i<enemyTiers[this->wave-1][2]; i++){
        enemy = intTier3EnemyName(defEngine);
        position = intEnemyPosition(defEngine);
        while (this->sockets[enemySockets[position]]->icon != nullptr){
            if (position == 11)
                position = 0;
            else
                position += 1;
        }
        this->sockets[enemySockets[position]]->icon = new Icon(&this->sockets, enemySockets[position], &this->font, enemyTextureNames[enemy]);
        this->icons.push_back(this->sockets[enemySockets[position]]->icon);
        if (enemy == 12)
            this->sockets[enemySockets[position]]->icon->entity = new Entity(this->sockets[enemySockets[position]]->icon, &this->font, enemyNames[enemy], 3,
                                                                             10, 15, 0, 5, 0, 0, 0);
        else if (enemy == 13)
            this->sockets[enemySockets[position]]->icon->entity = new Entity(this->sockets[enemySockets[position]]->icon, &this->font, enemyNames[enemy], 3,
                                                                             0, 0, 10, 0, 15, 5, 0);
        else if (enemy == 14)
            this->sockets[enemySockets[position]]->icon->entity = new Entity(this->sockets[enemySockets[position]]->icon, &this->font, enemyNames[enemy], 3,
                                                                             5, 0, 15, 10, 0, 0, 0);
        else if (enemy == 15)
            this->sockets[enemySockets[position]]->icon->entity = new Entity(this->sockets[enemySockets[position]]->icon, &this->font, enemyNames[enemy], 3,
                                                                             0, 0, 0, 15, 5, 10, 0);
        else if (enemy == 16)
            this->sockets[enemySockets[position]]->icon->entity = new Entity(this->sockets[enemySockets[position]]->icon, &this->font, enemyNames[enemy], 3,
                                                                             15, 10, 5, 0, 0, 0, 0);
        else if (enemy == 17)
            this->sockets[enemySockets[position]]->icon->entity = new Entity(this->sockets[enemySockets[position]]->icon, &this->font, enemyNames[enemy], 3,
                                                                             0, 5, 0, 0, 10, 15, 0);
    }
}

void GameState::initPoolIcons(){
    for (auto & poolName : poolSockets){
        if (this->sockets[poolName]->icon == nullptr){
            this->sockets[poolName]->icon = new Icon(&this->sockets, poolName, &this->font, "../Textures/Icons_01.png");
            this->sockets[poolName]->icon->entity = new Entity(this->sockets[poolName]->icon, &this->font, " ", 1, 0, 0, 0, 0, 0, 0, 0);
            this->icons.push_back( this->sockets[poolName]->icon);
        }
    }
}

// CONSTRUCTOR AND DESTRUCTORS
GameState::GameState(sf::RenderWindow* window, std::stack<State*>* states, float* dt): State(window, states, dt){
    this->initFonts("../Resources/DisposableDroidBB_bld.ttf");
    this->initButtons("../Config/Game/game_buttons.ini");
    this->initTextboxes("../Config/Game/game_textboxes.ini");
    this->initSockets("../Config/Game/game_sockets.ini");
    this->initLines("../Config/Game/game_lines.ini");
    this->wave = 1;
    this->gold = 0;
    this->unite_price = 0;
    this->gameOverTimer = 10;
    this->gameOverTitle = new TextBox(735, 100, &this->font, "FAILURE", 150);
    this->gameOverText = new TextBox(460, 300, &this->font, "The Last City has fallen!", 100);
    this->gameOverWave = new TextBox(610, 500, &this->font, "Waves beaten: " + std::to_string(this->wave - 1), 100);
    this->gameOverCountdown = new TextBox(385, 950, &this->font, "Returning to main menu in " + std::to_string(int(gameOverTimer)), 100);
    this->background.setSize(sf::Vector2f(float(window->getSize().x), float(window->getSize().y)));
    this->background.setFillColor(sf::Color(57,79,137, 255));
    this->background.setPosition(0, 500);
    this->backgroundTexture.loadFromFile("../Textures/background.png");
    this->backgroundSprite.setTexture(this->backgroundTexture);
    this->backgroundSprite.setPosition(0, -1);
    this->gameOverBackground.setSize(sf::Vector2f(float(window->getSize().x), float(window->getSize().y)));
    this->gameOverBackground.setPosition(0,0);
    this->gameOverBackground.setFillColor(sf::Color(57,79,137, 255));
    this->paused = false;
    this->pauseState = new PauseState(window, states, dt);
    this->waveActive = false;
    this->game_state = FIGHTING;
    this->zone1_state = FIGHTING;
    this->zone2_state = FIGHTING;
    this->zone3_state = FIGHTING;
    this->zone1_hp = 3;
    this->zone2_hp = 3;
    this->zone3_hp = 3;
    this->mine_income = mine[0];
    this->mine_lvl = 0;
    this->mine_upgrade_price = mine_upgrade[0];
    updateMine();
    initPoolIcons();
    updateGold(10);
    rollPool();
    initEnemies();
}

GameState::~GameState(){
    this->paused = false;
    delete this->pauseState;
    this->game_state = FIGHTING;
    delete this->gameOverTitle;
    delete this->gameOverWave;
    delete this->gameOverCountdown;
    delete this->gameOverText;
    State::~State();
}

// FUNCTIONS
void GameState::targeting() {
    for (int i = 0; i < 12; i++) {
        if (this->sockets[enemySockets[i]]->icon != nullptr) {
            if (this->sockets[heroSockets[i]]->icon != nullptr) {
                if (!this->sockets[heroSockets[i]]->icon->entity->dead) {
                    this->sockets[enemySockets[i]]->icon->entity->target = this->sockets[heroSockets[i]]->icon->entity;
                    this->sockets[heroSockets[i]]->icon->entity->target = this->sockets[enemySockets[i]]->icon->entity;
                }
            } else
                this->sockets[enemySockets[i]]->icon->entity->target = nullptr;
        }
    }
    for (int i = 0; i < 12; i++) {
        if (this->sockets[enemySockets[i]]->icon != nullptr) {
            if (this->sockets[enemySockets[i]]->icon->entity->target == nullptr) {
                for (int j = 0; j < 4; j++) {
                    if (this->sockets[heroSockets[(i / 4) * 4 + j]]->icon != nullptr) {
                        if (!this->sockets[heroSockets[(i / 4) * 4 + j]]->icon->entity->dead &&
                            (this->sockets[heroSockets[(i / 4) * 4 + j]]->icon->entity->target == nullptr) &&
                            (this->sockets[enemySockets[(i / 4) * 4 + j]]->icon == nullptr)) {
                            this->sockets[enemySockets[i]]->icon->entity->target = this->sockets[heroSockets[(i / 4) * 4 +j]]->icon->entity;
                            this->sockets[heroSockets[(i / 4) * 4 +j]]->icon->entity->target = this->sockets[enemySockets[i]]->icon->entity;
                            this->sockets[enemySockets[(i / 4) * 4 + j]]->icon = this->sockets[enemySockets[i]]->icon;
                            this->sockets[enemySockets[i]]->icon->socket = this->sockets[enemySockets[(i / 4) * 4 + j]];
                            this->sockets[enemySockets[i]]->icon = nullptr;
                            break;
                        }
                    }
                }
            }
        }

    }
}

void GameState::enemyCheck(){
    for (auto & enemySocket: enemySockets){
        if (this->sockets[enemySocket]->icon != nullptr){
            if (this->sockets[enemySocket]->icon->entity->dead){
                this->sockets[enemySocket]->icon->entity->target->target = nullptr;
                delete this->sockets[enemySocket]->icon->entity;
                deleteIcon(this->sockets[enemySocket]->icon);
            }
        }
    }
}



void GameState::rollEnemies(){
    for (auto & enemySocket: enemySockets){
        if (this->sockets[enemySocket]->icon != nullptr){
            delete this->sockets[enemySocket]->icon->entity;
            deleteIcon(this->sockets[enemySocket]->icon);
        }
    }
    initEnemies();
}

void GameState::rollPool(){
    int random;
    for (auto & poolName : poolSockets){
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
        int randomTexture = intHeroTexture(defEngine);
        int randomName = intHeroName(defEngine);
        this->sockets[poolName]->icon->entity->updateCharacteristics(heroNames[randomName], heroTextureNames[randomTexture], 1, characteristics[0], characteristics[1], characteristics[2], characteristics[3], characteristics[4], characteristics[5], characteristics[6] );
    }
    for (unsigned short & poolState : poolStates)
        poolState = POOL_SELLING;
}

void GameState::startWave(){
    this->waveActive = true;
    for (auto & socket: sockets){
        socket.second->saved_in = socket.second->accessible_in;
        socket.second->saved_out = socket.second->accessible_out;
        socket.second->accessible_in = false;
        socket.second->accessible_out = false;
    }
}

void GameState::checkForWaveEnd(){
    bool flag_wave = true;
    bool flag_enemy = true;
    bool flag_hero = true;
    if (zone1_state == FIGHTING) {
        for (int i = 0; i < 4; i++) {
            if (this->sockets[enemySockets[i]]->icon != nullptr)
                flag_hero = false;
            if (this->sockets[heroSockets[i]]->icon != nullptr) {
                if (!this->sockets[heroSockets[i]]->icon->entity->dead)
                    flag_enemy = false;
            }
        }
        if (flag_hero)
            this->zone1_state = WON;
        else if (flag_enemy){
            this->zone1_hp -= 1;
            this->zone1_state = LOST;
        }
        if (!flag_hero)
            flag_wave = false;
    }
    flag_enemy = true;
    flag_hero = true;
    if (zone2_state == FIGHTING) {
        for (int i = 4; i < 8; i++) {
            if (this->sockets[enemySockets[i]]->icon != nullptr)
                flag_hero = false;
            if (this->sockets[heroSockets[i]]->icon != nullptr) {
                if (!this->sockets[heroSockets[i]]->icon->entity->dead)
                    flag_enemy = false;
            }
        }
        if (flag_hero)
            this->zone2_state = WON;
        else if (flag_enemy){
            this->zone2_hp -= 1;
            this->zone2_state = LOST;
        }
        if (!flag_hero)
            flag_wave = false;
    }
    flag_enemy = true;
    flag_hero = true;
    if (zone3_state == FIGHTING) {
        for (int i = 8; i < 12; i++) {
            if (this->sockets[enemySockets[i]]->icon != nullptr)
                flag_hero = false;
            if (this->sockets[heroSockets[i]]->icon != nullptr) {
                if (!this->sockets[heroSockets[i]]->icon->entity->dead)
                    flag_enemy = false;
            }
        }
        if (flag_hero)
            this->zone3_state = WON;
        else if (flag_enemy){
            this->zone3_hp -= 1;
            this->zone3_state = LOST;
        }
        if (!flag_hero)
            flag_wave = false;
    }
    if (this->zone1_state != FIGHTING && this->zone2_state != FIGHTING && this->zone3_state != FIGHTING){
        if (flag_wave)
            updateWaveNumber();
        endWave();
        this->zone1_state = FIGHTING;
        this->zone2_state = FIGHTING;
        this->zone3_state = FIGHTING;
        if (this->zone1_hp == 0 || this->zone2_hp == 0 || this->zone3_hp == 0){
            this->game_state = LOST;


        }
    }
}

void GameState::endWave(){
    this->waveActive = false;
    updateLocationsHP();
    for (auto & socket: sockets){
        socket.second->accessible_in = socket.second->saved_in;
        socket.second->accessible_out = socket.second->saved_out;
    }
    updateGold(this->gold + this->mine_income);
    rollEnemies();
    for (auto & heroSocket: heroSockets){
        if (this->sockets[heroSocket]->icon != nullptr) {
            this->sockets[heroSocket]->icon->entity->current_HP = this->sockets[heroSocket]->icon->entity->HP;
            this->sockets[heroSocket]->icon->entity->timer = 0;
            this->sockets[heroSocket]->icon->entity->texttimer = 0;
            this->sockets[heroSocket]->icon->text.setString("");
            this->sockets[heroSocket]->icon->entity->target = nullptr;
        }
    }
}

// UPDATE
void GameState::updateCountdown(){
    this->gameOverTimer -= *this->dt;
    this->gameOverCountdown->text.setString("Returning to main menu in " + std::to_string(int(gameOverTimer)));
    if (this->gameOverTimer <= 0)
        this->quit = true;
}

void GameState::updateFightBars(){
    for (auto & fightSocket: fightSockets){
        if (this->sockets[fightSocket]->icon != nullptr){
            this->sockets[fightSocket]->icon->updateBars();
        }
    }
}

void GameState::updateModifiers(){
    float zoneLS = 0;
    if (!this->waveActive){
        for (auto & icon: icons){
            if (icon->entity->modifier != 1){
                icon->entity->modifier = 1;
                icon->entity->updateStats();
            }
        }
        for (int i = 0; i<4; i++){
            if (this->sockets[heroSockets[i]]->icon != nullptr)
                zoneLS += this->sockets[heroSockets[i]]->icon->entity->LS;
        }
        for (int i = 0; i<4; i++){
            if (this->sockets[heroSockets[i]]->icon != nullptr) {
                this->sockets[heroSockets[i]]->icon->entity->modifier = 1 + (zoneLS - this->sockets[heroSockets[i]]->icon->entity->LS)/ 100;
                this->sockets[heroSockets[i]]->icon->entity->updateStats();
            }
        }
        zoneLS = 0;
        for (int i = 4; i<8; i++){
            if (this->sockets[heroSockets[i]]->icon != nullptr)
                zoneLS += this->sockets[heroSockets[i]]->icon->entity->LS;
        }
        for (int i = 4; i<8; i++){
            if (this->sockets[heroSockets[i]]->icon != nullptr) {
                this->sockets[heroSockets[i]]->icon->entity->modifier = 1 + (zoneLS - this->sockets[heroSockets[i]]->icon->entity->LS) / 100;
                this->sockets[heroSockets[i]]->icon->entity->updateStats();
            }
        }
        zoneLS = 0;
        for (int i = 8; i<12; i++){
            if (this->sockets[heroSockets[i]]->icon != nullptr)
                zoneLS += this->sockets[heroSockets[i]]->icon->entity->LS;
        }
        for (int i = 8; i<12; i++){
            if (this->sockets[heroSockets[i]]->icon != nullptr) {
                this->sockets[heroSockets[i]]->icon->entity->modifier = 1 + (zoneLS - this->sockets[heroSockets[i]]->icon->entity->LS) / 100;
                this->sockets[heroSockets[i]]->icon->entity->updateStats();
            }
        }
    }
}

void GameState::updateWaveNumber(){
    if (this->wave < 20) {
        this->wave = this->wave + 1;
        this->textboxes["WAVE_VALUE"]->text.setString(std::to_string(this->wave));
    } else {
        this->game_state = WON;
        this->gameOverTitle->text.setString("Victory!");
        this->gameOverText->text.setString("The Last City has stood!");
    }
}

void GameState::updatePool(){
    for (int i = 0; i<5; i++){
        if (this->sockets["ROLL_"+std::to_string(i+1)]->icon == nullptr && poolStates[i] == POOL_SELLING){
            updateGold(this->gold-unit_price);
            poolStates[i] = POOL_BOUGHT;
        }
    }

}

void GameState::updateMine(){
    this->mine_lvl += 1;
    this->mine_income = mine[this->mine_lvl - 1];
    this->textboxes["MINE_LVL"]->text.setString(std::to_string(this->mine_lvl));
    this->textboxes["MINE_INCOME_VALUE"]->text.setString(std::to_string(this->mine_income));
    if (this->mine_lvl == 6){
      this->buttons["MINE_UPGRADE_BTN"]->text.setString("LVL MAX");
        this->buttons["MINE_UPGRADE_BTN"]->updateTextPosition();
    } else {
       this->mine_upgrade_price = mine_upgrade[this->mine_lvl-1];
       this->buttons["MINE_UPGRADE_BTN"]->text.setString("Upgrade (" + std::to_string(this->mine_upgrade_price)+"G)");
       this->buttons["MINE_UPGRADE_BTN"]->updateTextPosition();
    }
}

void GameState::updateLocationsHP() {
    this->textboxes["FOREST"]->text.setString("Forest ("+ std::to_string(this->zone1_hp)+"HP)");
    this->textboxes["CASTLE"]->text.setString("Forest ("+ std::to_string(this->zone2_hp)+"HP)");
    this->textboxes["HILLS"]->text.setString("Forest ("+ std::to_string(this->zone3_hp)+"HP)");
}

void GameState::updateUnite(){
    if (this->unite_price != 0){
        this->unite_price = 0;
        this->buttons["UNITE_BTN"]->text.setString("Unite");
        this->buttons["UNITE_BTN"]->updateTextPosition();
    }
    if (this->sockets["UPGRADE_1"]->icon != nullptr && this->sockets["UPGRADE_2"]->icon != nullptr && this->sockets["UPGRADE_3"]->icon != nullptr){
        if ((this->sockets["UPGRADE_1"]->icon->entity->rank == this->sockets["UPGRADE_2"]->icon->entity->rank) && (this->sockets["UPGRADE_1"]->icon->entity->rank == this->sockets["UPGRADE_3"]->icon->entity->rank)){
            this->unite_price = 10*pow(3,(this->sockets["UPGRADE_1"]->icon->entity->rank-1));
            this->buttons["UNITE_BTN"]->text.setString("Unite ("+std::to_string(unite_price)+"G)");
            this->buttons["UNITE_BTN"]->updateTextPosition();
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
        for (auto & poolName : poolSockets) {
            this->sockets[poolName]->accessible_out = true;
        }
    } else {
        for (auto & poolName : poolSockets) {
            this->sockets[poolName]->accessible_out = false;
        }
    }
}

void GameState::updateButtons() {
    if (this->buttons["PAUSE_BTN"]->isPressed()){
        this->paused = true;
    }
    if (this->buttons["START_WAVE_BTN"]->isPressed()){
        startWave();
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
    if (this->buttons["MINE_UPGRADE_BTN"]->isPressed() && this->gold >= this->mine_upgrade_price && this->mine_lvl < 6){
        updateGold(this->gold-this->mine_upgrade_price);
        updateMine();
    }
}

void GameState::update(const float& dt){
    if (this->game_state == FIGHTING) {
        if (!this->paused) {
            this->updateMousePositions();
            this->updateButtonsState(this->mousePosView);
            this->updateButtons();
            this->updateIcons(this->mousePosView);
            if (this->sockets["UPGRADE_4"]->icon != nullptr) {
                this->sockets["UPGRADE_4"]->icon->update(mousePosView);
                this->sockets["UPGRADE_4"]->icon->entity->update();
            }
            this->updateModifiers();
            this->updateEntities();
            this->updatePool();
            this->updateUnite();
            this->updateFightBars();
            if (this->waveActive) {
                for (auto &fightSocket: fightSockets) {
                    if (this->sockets[fightSocket]->icon != nullptr) {
                        this->sockets[fightSocket]->icon->entity->updateTimer(*this->dt);
                        this->sockets[fightSocket]->icon->entity->updateTextTimer(*this->dt);
                    }
                }
                this->enemyCheck();
                this->targeting();
                this->checkForWaveEnd();
            }
        } else {
            this->pauseState->update(dt);
        }
    } else {
        this->updateCountdown();
    }
}


// RENDER
void GameState::renderFightBars(sf::RenderTarget* target){
    for (auto & fightSocket: fightSockets){
        if (this->sockets[fightSocket]->icon != nullptr){
            this->sockets[fightSocket]->icon->renderBars(target);
        }
    }
}

// RENDER
void GameState:: render(sf::RenderTarget* target){
    if (this->game_state == FIGHTING) {
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
        this->renderFightBars(target);
        this->renderEntities(target);
        if (this->paused) {
            this->pauseState->render(target);
        }
    } else {
        target->draw(this->gameOverBackground);
        this->gameOverTitle->render(target);
        this->gameOverText->render(target);
        this->gameOverWave->render(target);
        this->gameOverCountdown->render(target);
    }
}
