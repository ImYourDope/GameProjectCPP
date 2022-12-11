#include "Entity.h"

#include <utility>


Entity::Entity(Icon* icon, sf::Font* font, std::string name, int rank, int bulky, int strong, int lucky, int precise, int agile, int swift, int inspiring) {
    this->font = font;
    this->updated = false;
    this->icon = icon;
    this->icon->entity = this;
    this->name = std::move(name);
    this->rank = rank;
    this->bulky = bulky;
    this->strong = strong;
    this->lucky = lucky;
    this->precise = precise;
    this->agile = agile;
    this->swift = swift;
    this->inspiring = inspiring;
    updateStats();
    this->current_HP = HP;
    initHoverBox();
}

Entity::~Entity() {
    for (const auto& textbox: hoverTextBoxes){
        delete textbox.second;
    }
    hoverTextBoxes.clear();
    this->icon->entity = nullptr;
}

void Entity::updateCharacteristics(std::string name_, std::string texture_name, int rank_, int bulky_, int strong_, int lucky_, int precise_, int agile_, int swift_, int inspiring_){
    this->name = std::move(name_);
    this->icon->texturePath = std::move(texture_name);
    this->icon->texture.loadFromFile(this->icon->texturePath);
    this->icon->sprite.setTexture(this->icon->texture);
    this->rank = rank_;
    this->bulky = bulky_;
    this->strong = strong_;
    this->lucky = lucky_;
    this->precise = precise_;
    this->agile = agile_;
    this->swift = swift_;
    this->inspiring = inspiring_;
    updateStats();
    updateTextBoxes();
}


void Entity::updateStats(){
    this->HP = 100*pow(2, rank)*(1+0.2*(bulky/5));
    this->ATK = 10*pow(2, rank)*(1+0.1*(strong/5));
    if (5*rank+10*abs(lucky/5)*(lucky/5) > 100)
        this->CR = 100;
    else if (5*rank+10*(lucky/5) < 0)
        this->CR = 0;
    else
        this->CR = 10*rank+10*(lucky/5);
    if (100+20*(rank-1)+30*(precise/5) < 0)
        this->CD = 0;
    else this->CD = 20*rank+30*(precise/5);
    if (5*rank+10*(agile/5) < 0)
        this->EV = 0;
    else this->EV = 10*rank+10*(agile/5);
    this->SPD = 90+10*rank+20*(swift/5);
    this->LS = 100+10*(inspiring/5);
}

void Entity::updateTextBoxes(){
    this->hoverTextBoxes["Name"]->text.setString(name);
    this->hoverTextBoxes["Rank"]->text.setString("Rank: "+std::to_string(rank));
    this->hoverTextBoxes["HP"]->text.setString("HP: "+std::to_string(int(HP)));
    this->hoverTextBoxes["ATK"]->text.setString("ATK: "+std::to_string(int(ATK)));
    this->hoverTextBoxes["CR"]->text.setString("CR: "+std::to_string(int(CR)));
    this->hoverTextBoxes["CD"]->text.setString("CD: "+std::to_string(int(CD)));
    this->hoverTextBoxes["EV"]->text.setString("EV: "+std::to_string(int(EV)));
    this->hoverTextBoxes["SPD"]->text.setString("SPD: "+std::to_string(int(SPD)));
    this->hoverTextBoxes["LS"]->text.setString("LS: "+std::to_string(int(LS)));
    this->hoverTextBoxes["Bulky"]->text.setString("Bulky: "+std::to_string(bulky)+" "+"(LVL" + std::to_string(bulky/5)+")");
    this->hoverTextBoxes["Strong"]->text.setString("Strong: "+std::to_string(strong)+" "+"(LVL" + std::to_string(strong/5)+")");
    this->hoverTextBoxes["Lucky"]->text.setString("Lucky: "+std::to_string(lucky)+" "+"(LVL" + std::to_string(lucky/5)+")");
    this->hoverTextBoxes["Precise"]->text.setString("Precise: "+std::to_string(precise)+" "+"(LVL" + std::to_string(precise/5)+")");
    this->hoverTextBoxes["Agile"]->text.setString("Agile: "+std::to_string(agile)+" "+"(LVL" + std::to_string(agile/5)+")");
    this->hoverTextBoxes["Swift"]->text.setString("Swift: "+std::to_string(swift)+" "+"(LVL" + std::to_string(swift/5)+")");
    this->hoverTextBoxes["Inspiring"]->text.setString("Inspiring: "+std::to_string(inspiring)+" "+"(LVL" + std::to_string(inspiring/5)+")");

}

void Entity::update() {
    float xpos, ypos;
    xpos = 0;
    ypos = 0;
    this->updated = false;
    if (this->icon->iconState == ICON_HOVERED){
        this->updated = true;
        if ((this->icon->shape.getPosition().x < 960) && (this->icon->shape.getPosition().y < 540)){
            xpos = this->icon->shape.getPosition().x+this->icon->shape.getSize().x;
            ypos = this->icon->shape.getPosition().y+this->icon->shape.getSize().y;
        } else if ((this->icon->shape.getPosition().x >= 960) && (this->icon->shape.getPosition().y < 540)){
            xpos = this->icon->shape.getPosition().x-this->hoverBox.getSize().x;
            ypos = this->icon->shape.getPosition().y+this->icon->shape.getSize().x;
        } else if ((this->icon->shape.getPosition().x < 960) && (this->icon->shape.getPosition().y >= 540)){
            xpos = this->icon->shape.getPosition().x+this->icon->shape.getSize().x;
            ypos = this->icon->shape.getPosition().y-this->hoverBox.getSize().y;
        } else if ((this->icon->shape.getPosition().x >= 960) && (this->icon->shape.getPosition().y >= 540)){
            xpos = this->icon->shape.getPosition().x-this->hoverBox.getSize().x;
            ypos = this->icon->shape.getPosition().y-this->hoverBox.getSize().y;
        }
        this->hoverBox.setPosition(xpos, ypos);
        this->hoverTextBoxes.at("Name")->setPos(5+xpos, 5+ypos);
        this->hoverTextBoxes.at("HP")->setPos(5+xpos, 45+ypos);
        this->hoverTextBoxes.at("ATK")->setPos(5+xpos, 85+ypos);
        this->hoverTextBoxes.at("CR")->setPos(5+xpos, 125+ypos);
        this->hoverTextBoxes.at("CD")->setPos(5+xpos, 165+ypos);
        this->hoverTextBoxes.at("EV")->setPos(5+xpos, 205+ypos);
        this->hoverTextBoxes.at("SPD")->setPos(5+xpos, 245+ypos);
        this->hoverTextBoxes.at("LS")->setPos(5+xpos, 285+ypos);
        this->hoverTextBoxes.at("Rank")->setPos(350+xpos, 5+ypos);
        this->hoverTextBoxes.at("Bulky")->setPos(200+xpos, 45+ypos);
        this->hoverTextBoxes.at("Strong")->setPos(200+xpos, 85+ypos);
        this->hoverTextBoxes.at("Lucky")->setPos(200+xpos, 125+ypos);
        this->hoverTextBoxes.at("Precise")->setPos(200+xpos, 165+ypos);
        this->hoverTextBoxes.at("Agile")->setPos(200+xpos, 205+ypos);
        this->hoverTextBoxes.at("Swift")->setPos(200+xpos, 245+ypos);
        this->hoverTextBoxes.at("Inspiring")->setPos(200+xpos, 285+ypos);
    }
}

void Entity::initHoverBox() {
    this->hoverBox.setSize(sf::Vector2f(670, 320));
    this->hoverBox.setPosition(this->icon->socket->shape.getPosition());
    this->hoverBox.setFillColor(sf::Color(57,79,137, 255));
    this->hoverBox.setOutlineThickness(3);
    this->hoverBox.setOutlineColor(sf::Color(97, 119, 177, 255));
    this->hoverTextBoxes["Name"] = new TextBox(0, 0, this->font, name, 55);
    this->hoverTextBoxes["Rank"] = new TextBox(0, 0, this->font, "Rank: "+std::to_string(rank), 55);
    this->hoverTextBoxes["HP"] = new TextBox(0, 0, this->font, "HP: "+std::to_string(int(HP)), 55);
    this->hoverTextBoxes["ATK"] = new TextBox(0, 0, this->font, "ATK: "+std::to_string(int(ATK)), 55);
    this->hoverTextBoxes["CR"] = new TextBox(0, 0, this->font, "CR: "+std::to_string(int(CR)), 55);
    this->hoverTextBoxes["CD"] = new TextBox(0, 0, this->font, "CD: "+std::to_string(int(CD)), 55);
    this->hoverTextBoxes["EV"] = new TextBox(0, 0, this->font, "EV: "+std::to_string(int(EV)), 55);
    this->hoverTextBoxes["SPD"] = new TextBox(0, 0, this->font, "SPD: "+std::to_string(int(SPD)), 55);
    this->hoverTextBoxes["LS"] = new TextBox(0, 0, this->font, "LS: "+std::to_string(int(LS)), 55);
    this->hoverTextBoxes["Bulky"] = new TextBox(0, 0, this->font, "Bulky: "+std::to_string(bulky)+" "+"(LVL" + std::to_string(bulky/5)+")", 55);
    this->hoverTextBoxes["Strong"] = new TextBox(0, 0, this->font, "Strong: "+std::to_string(strong)+" "+"(LVL" + std::to_string(strong/5)+")", 55);
    this->hoverTextBoxes["Lucky"] = new TextBox(0, 0, this->font, "Lucky: "+std::to_string(lucky)+" "+"(LVL" + std::to_string(lucky/5)+")", 55);
    this->hoverTextBoxes["Precise"] = new TextBox(0, 0, this->font, "Precise: "+std::to_string(precise)+" "+"(LVL" + std::to_string(precise/5)+")", 55);
    this->hoverTextBoxes["Agile"] = new TextBox(0, 0, this->font, "Agile: "+std::to_string(agile)+" "+"(LVL" + std::to_string(agile/5)+")", 55);
    this->hoverTextBoxes["Swift"] = new TextBox(0, 0, this->font, "Swift: "+std::to_string(swift)+" "+"(LVL" + std::to_string(swift/5)+")", 55);
    this->hoverTextBoxes["Inspiring"] = new TextBox(0, 0, this->font, "Inspiring: "+std::to_string(inspiring)+" "+"(LVL" + std::to_string(inspiring/5)+")", 55);

}

void Entity::render(sf::RenderTarget *target) {
    if (this->icon->iconState == ICON_HOVERED && this->updated){
        target->draw(this->hoverBox);
        for (const auto& textbox: hoverTextBoxes){
            textbox.second->render(target);
        }
    }
}


