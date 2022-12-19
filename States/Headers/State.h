#ifndef SOULSANCTUM_STATE_H
#define SOULSANCTUM_STATE_H

#include "../../Entity/Entity.h"

class State {
private:


protected:
    // PROTECTED FIELDS
    std::stack<State*>* states;
    sf::RenderWindow* window;
    sf::Vector2f mousePosView;
    std::map<std::string, Button*> buttons;
    std::map<std::string, TextBox*> textboxes;
    std::map<std::string, Socket*> sockets;
    std::vector<Icon*> icons;
    std::vector<Line*> lines;
    std::vector<sf::Texture> textures;
    sf::Font font;
    float* dt;

public:
    // PUBLIC FIELDS
    Icon* iconTaken;
    bool quit;
    bool paused;

    // INITIALIZERS
    void initFonts(const std::string& filename);
    void initButtons(const std::string& filename);
    void initTextboxes(const std::string& filename);
    void initSockets(const std::string& filename);
    void initLines(const std::string& filename);

    // CONSTRUCTORS AND DESTRUCTORS
    State(sf::RenderWindow* window, std::stack<State*>* states, float* dt);
    virtual ~State();

    // DELETES
    void deleteIcon(Icon* icon);

    // FUNCTIONS
    const bool& getQuit() const;

    // UPDATE
    virtual void updateMousePositions();
    void updateButtonsState(sf::Vector2f mousePosition);
    virtual void updateButtons();
    void updateIcons(sf::Vector2f mousePosition);
    void updateEntities();
    virtual void update(const float& dt) = 0;

    // RENDER
    void renderButtons(sf::RenderTarget* target);
    void renderTextboxes(sf::RenderTarget* target);
    void renderSockets(sf::RenderTarget* target);
    void renderIcons(sf::RenderTarget* target);
    void renderEntities(sf::RenderTarget* target);
    void renderLines(sf::RenderTarget* target);
    virtual void render(sf::RenderTarget* target) = 0;
};


#endif //SOULSANCTUM_STATE_H
