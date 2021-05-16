/*
** EPITECH PROJECT, 2021
** # Sfml.cpp
** File description:
** Created 26/03/2021 11:43:04
*/

/*!
** @file Sfml.cpp
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
** @version 0.1
** @date 2021-05-10
**
** @copyright Copyright (c) 2021
*/

#include "Sfml.hpp"

namespace Sfml
{

/*!
** @brief Construct a new Sfml object
**
*/
Sfml::Sfml(void)
:   _name("sfml"), _window(sf::VideoMode(1280, 720), "Arcade::Window", sf::Style::Titlebar | sf::Style::Close)
{
    auto desktop = sf::VideoMode::getDesktopMode();
    unsigned int x = desktop.width/2 - _window.getSize().x/2;
    unsigned int y = desktop.height/2 - _window.getSize().y/2;
    _window.setPosition(sf::Vector2i(x, y));
    _shapeRatio.x = 30.f;
    _shapeRatio.y = 10.f;
    if (!_defaultFont.loadFromFile("./resources/default.ttf")) {
        fprintf(stderr, "Can't load font.\n");
        return;
    }
    _window.display();
}

/*!
** @brief Destroy the Sfml object
**
*/
Sfml::~Sfml(void)
{
    _window.close();
}

/*!
** @brief get name of current lib
**
** @return std::string
*/
std::string Sfml::getName(void) const
{
    return _name;
}

/*!
** @brief Setup the current game name
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
** @param currentGame
**
*/
void Sfml::setCurrentGame(std::string currentGame)
{
    _currentGame = currentGame;
}

/*!
** @brief Update the score
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
** @param score
**
** @return true
** @return false
*/
bool Sfml::updateScore(int score)
{
    sf::Text labelScore;
    sf::Text textScore;

    labelScore.setFont(_defaultFont);
    labelScore.setString("Score: ");
    labelScore.setPosition(sf::Vector2f(10.f, 15.f));
    labelScore.setCharacterSize(16);
    labelScore.setFillColor(sf::Color::White);

    textScore.setFont(_defaultFont);
    textScore.setString(std::to_string(score));
    textScore.setPosition(sf::Vector2f(115.f, 10.f));
    textScore.setCharacterSize(24);
    textScore.setFillColor(sf::Color::White);

    _window.draw(labelScore);
    _window.draw(textScore);
    _window.display();
}

/*!
** @brief Load map with MapContainer and MetaContainer
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
** @param map
** @param meta
**
*/
void Sfml::loadMap(MapContainer map, MetaContainer meta)
{
    this->contructShapedMap(map, meta);
    this->printShapedMap();

    _window.display();
}

/*!
** @brief Contruct map with sf::RectangleShape
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
** @param map
** @param meta
**
** @return ShapedMapContainer
*/
ShapedMapContainer Sfml::contructShapedMap(MapContainer map, MetaContainer meta)
{
    _ShapeMap.clear();
    pixel_t pixel;
    const float xf = _shapeRatio.x;
    const float yf = _shapeRatio.y;
    posf_t pos = this->getCenterPosition(map);
    const float savey = pos.y;

    for (int x = 0 ; x < map.size() ; x++) {
        for (int y = 0 ; y < map.at(x).size() ; y++) {
            switch (meta.at(x).at(y)) {
                case WALL:
                    pixel.meta = WALL;
                    pixel.shape.setPosition(sf::Vector2f(pos.y, pos.x));
                    pixel.shape.setSize(sf::Vector2f(yf, xf));
                    pixel.shape.setFillColor(sf::Color(0, 35, 240));
                    _ShapeMap.push_back(pixel);
                    break;
                case IWALL:
                pixel.meta = IWALL;
                    pixel.shape.setPosition(sf::Vector2f(pos.y, pos.x));
                    pixel.shape.setSize(sf::Vector2f(yf, xf));
                    pixel.shape.setFillColor(sf::Color::Black);
                    _ShapeMap.push_back(pixel);
                    break;
                case PLAYER:
                    pixel.meta = PLAYER;
                    pixel.shape.setPosition(sf::Vector2f(pos.y - 5.f, pos.x + 5.f));
                    pixel.shape.setSize(sf::Vector2f(yf + 10.f, xf - 10.f));
                    pixel.shape.setFillColor(sf::Color(255, 225, 0));
                    _ShapeMap.push_back(pixel);
                    break;
                case BONUS:
                    pixel.meta = BONUS;
                    pixel.shape.setPosition(sf::Vector2f(pos.y, pos.x + 10.f));
                    pixel.shape.setSize(sf::Vector2f(yf, xf - 20.f));
                    pixel.shape.setFillColor(sf::Color(255, 0, 0));
                    _ShapeMap.push_back(pixel);
                    break;
                case MONSTER:
                    pixel.meta = MONSTER;
                    pixel.shape.setPosition(sf::Vector2f(pos.y - 5.f, pos.x + 5.f));
                    pixel.shape.setSize(sf::Vector2f(yf + 10.f, xf - 10.f));
                    pixel.shape.setFillColor(sf::Color(0, 255, 255));
                    _ShapeMap.push_back(pixel);
                    break;
                case KMONSTER:
                    pixel.meta = MONSTER;
                    pixel.shape.setPosition(sf::Vector2f(pos.y - 5.f, pos.x + 5.f));
                    pixel.shape.setSize(sf::Vector2f(yf + 10.f, xf - 10.f));
                    pixel.shape.setFillColor(sf::Color(255, 0, 0));
                    _ShapeMap.push_back(pixel);
                    break;
                case PATH:
                    pixel.meta = PATH;
                    pixel.shape.setPosition(sf::Vector2f(pos.y, pos.x));
                    pixel.shape.setSize(sf::Vector2f(yf, xf));
                    pixel.shape.setFillColor(sf::Color::Black);
                    _ShapeMap.push_back(pixel);
                    break;
                case PPATH:
                    pixel.meta = PPATH;
                    pixel.shape.setPosition(sf::Vector2f(pos.y + 2.5f, pos.x + 12.5f));
                    pixel.shape.setSize(sf::Vector2f(yf - 5.f, xf - 25.f));
                    pixel.shape.setFillColor(sf::Color(255, 225, 0));
                    _ShapeMap.push_back(pixel);
                    break;
                default:
                    break;
            }
            pos.y += yf;
        }
        pos.y = savey;
        pos.x += xf;
    }
    return _ShapeMap;
}

void Sfml::printShapedMap(void)
{
    char *tips[5] = { "n for the next graphic library",
                      "p for the previous graphic library",
                      "c for the next game",
                      "v for the previous game", NULL };
    sf::Text tipsText;
    float h = 50.f;

     _window.clear(sf::Color::Black);

    tipsText.setFont(_defaultFont);
    tipsText.setOrigin(tipsText.getLocalBounds().width/2.f, tipsText.getLocalBounds().height/2.f);
    tipsText.setCharacterSize(12);
    tipsText.setFillColor(sf::Color::White);
    for (int x = 0 ; tips[x] != NULL ; x++) {
        tipsText.setPosition(sf::Vector2f(10.f, h));
        tipsText.setString(tips[x]);
        _window.draw(tipsText);
        h += 15.f;
        if (x == 1)
            h += 15.f;
    }
    for (int x = 0 ; x < _ShapeMap.size() ; x++) {
        _window.draw(_ShapeMap.at(x).shape);
    }
    for (int x = 0 ; x < _ShapeMap.size() ; x++) {
        if (_ShapeMap.at(x).meta == PLAYER || _ShapeMap.at(x).meta == MONSTER)
            _window.draw(_ShapeMap.at(x).shape);
    }
}

/*!
** @brief Refresh map from MapContainer and MetaContainer
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
** @param map
** @param meta
**
*/
void Sfml::refreshMap(MapContainer map, MetaContainer meta)
{
    if (!_window.isOpen())
        return;

    this->contructShapedMap(map, meta);
    this->printShapedMap();

    _window.display();
}

/*!
** @brief Return actual pressed Key in Arcade Standard Keys Type
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
**
** @return Keys
*/
enum Keys Sfml::keyPressed(void)
{
    if (_window.pollEvent(_events)) {
        switch (_events.type) {
        case sf::Event::Closed:
            return MENU_KEY;
            break;
        case sf::Event::KeyPressed:
            return this->readKeyInput(_events.key.code);
        default:
            return this->keyPressed();
            break;
        }
    }
    return NIL_KEY;
}

/*!
** @brief Transform sf::Keyboard::Key to an Arcade standard Keys
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
** @param keyCode
**
** @return enum Keys
*/
enum Keys Sfml::readKeyInput(sf::Keyboard::Key keyCode)
{
    switch (keyCode)
    {
    case sf::Keyboard::Up:
        return UP_KEY;
        break;
    case sf::Keyboard::Down:
        return DOWN_KEY;
        break;
    case sf::Keyboard::Left:
        return LEFT_KEY;
        break;
    case sf::Keyboard::Right:
        return RIGHT_KEY;
        break;
    case sf::Keyboard::Escape:
        return MENU_KEY;
        break;
    case sf::Keyboard::Enter:
        return ENTER_KEY;
        break;
    case sf::Keyboard::N:
        return NEXTLIB_KEY;
        break;
    case sf::Keyboard::P:
        return PREVLIB_KEY;
        break;
    default:
        return NIL_KEY;
        break;
    }
}

/*!
** @brief Get position of the center of the screen for given map
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
** @param map
**
** @return posf_t
*/
posf_t Sfml::getCenterPosition(MapContainer map)
{
    posf_t pos;
    pos_t size;

    for (size.x = 0 ; size.x < map.size() ; size.x++) {
        for (size.y = 0 ; size.y < map.at(size.x).size() ; size.y++) {}
    }
    pos.x = (_window.getSize().y / 2) - ((_shapeRatio.x * size.x) / 2);
    pos.y = (_window.getSize().x / 2) - ((_shapeRatio.y * size.y) / 2);
    return pos;
}

void Sfml::endGame(std::string text, int score)
{
    sf::Text yscore;
    sf::Text title;
    sf::Text tips;
    char yourScore[255];

    title.setFont(_defaultFont);
    title.setString(text);
    title.setOrigin(title.getLocalBounds().width/2.f, title.getLocalBounds().height/2.f);
    title.setPosition(sf::Vector2f((_window.getSize().x/2.f) - title.getLocalBounds().width/2.f, 300.f));
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Yellow);

    sprintf(yourScore, "Score: %d", score);
    yscore.setFont(_defaultFont);
    yscore.setString(yourScore);
    yscore.setOrigin(title.getLocalBounds().width/2.f, title.getLocalBounds().height/2.f);
    yscore.setPosition(sf::Vector2f((_window.getSize().x/2.f) - 50.f, 260.f));
    yscore.setCharacterSize(20);
    yscore.setFillColor(sf::Color::Green);

    tips.setFont(_defaultFont);
    tips.setString("Press escape to return at menu");
    tips.setOrigin(tips.getLocalBounds().width/2.f, tips.getLocalBounds().height/2.f);
    tips.setPosition(sf::Vector2f((_window.getSize().x/2.f) + 200.f, 365.f));
    tips.setCharacterSize(14);
    tips.setFillColor(sf::Color::White);

    _window.clear();
    _window.draw(title);
    _window.draw(yscore);
    _window.draw(tips);
    _window.display();
}

/*!
** @brief Print and refresh menu before start any game
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
** @param libs
**
** @return enum Keys
*/
enum Keys Sfml::viewMenu(LibCollection libs, std::string &playerName, std::vector<std::pair<std::string, int>> scores)
{
    if (_menu.empty())
        _menu = this->buildMenu(libs, playerName);
    Keys input = NIL_KEY;
    sf::Text menuHeader;
    sf::Text scoreheader;
    sf::Text scoreLine;
    char scoreBuffer[255];
    float scorelinepos = 145.f;
    static int select = 2;
    _window.clear();

    menuHeader.setFont(_defaultFont);
    menuHeader.setString("ARCADE");
    menuHeader.setOrigin(menuHeader.getLocalBounds().width/2.f, menuHeader.getLocalBounds().height/2.f);
    menuHeader.setPosition(sf::Vector2f((_window.getSize().x/2.f) - menuHeader.getLocalBounds().width/2.f, 75.f));
    menuHeader.setCharacterSize(50);
    menuHeader.setFillColor(sf::Color::White);

    scoreheader.setFont(_defaultFont);
    scoreheader.setString("Scoreboard");
    scoreheader.setOrigin(menuHeader.getLocalBounds().width/2.f, menuHeader.getLocalBounds().height/2.f);
    scoreheader.setPosition(sf::Vector2f(210.f, 103.f));
    scoreheader.setCharacterSize(22);
    scoreheader.setFillColor(sf::Color::Green);

    scoreLine.setFont(_defaultFont);
    scoreLine.setOrigin(menuHeader.getLocalBounds().width/2.f, menuHeader.getLocalBounds().height/2.f);
    scoreLine.setPosition(sf::Vector2f(210.f, 105.f));
    scoreLine.setCharacterSize(18);
    scoreLine.setFillColor(sf::Color::White);

    for (int x = 0 ; x < scores.size() ; x++) {
        sprintf(scoreBuffer, "%s..........%d", scores.at(x).first.c_str(), scores.at(x).second);
        scoreLine.setString(scoreBuffer);
        scoreLine.setPosition(sf::Vector2f(210.f, scorelinepos));
        _window.draw(scoreLine);
        scorelinepos += 35.f;
    }

    _window.draw(menuHeader);
    _window.draw(scoreheader);
    for (int x = 0 ; x < _menu.size() ; x++) {
        _window.draw(_menu.at(x).text);
    }

    input = this->keyPressed();
    switch (input) {
        case DOWN_KEY:
            if ((select + 1) < _menu.size()) {
                select++;
                if ((select + 1) < _menu.size() && _menu.at(select).n == 0)
                    select++;
            }
            break;
        case UP_KEY:
            if (select > 0 && (select - 1 ) != 0) {
                select--;
                if ((select - 1) < _menu.size() && _menu.at(select).n == 0)
                    select--;
            }
            break;
        case ENTER_KEY:
            if (strcmp(_menu.at(select).lib.name, "ncurses") == 0)
                return NC_KEY;
            if (strcmp(_menu.at(select).lib.name, "sfml") == 0)
                return SF_KEY;
            if (strcmp(_menu.at(select).lib.name, "pacman") == 0)
                return PCM_KEY;
            if (strcmp(_menu.at(select).lib.name, "nibbler") == 0)
                return NBL_KEY;
            if (_menu.at(select).lib.type == PSEUDO) {
                _menu.at(select).text = this->getNewPlayerName(_menu.at(select).text, playerName);
                return NIL_KEY;
            }
            break;
        default:
            for (int x = 0 ; x < _menu.size() ; x++) {
                if (x != select && _menu.at(x).n != 0) {
                    _menu.at(x).text.setFillColor(sf::Color::White);
                }
            }
            break;
    }

    _menu.at(select).text.setFillColor(sf::Color::Magenta);
    _window.draw(_menu.at(select).text);

    _window.display();
    return input;
}

sf::Text Sfml::getNewPlayerName(sf::Text currentName, std::string &playerName)
{
    sf::String playerInput;
    sf::Text tips;
    sf::RectangleShape rec;

    tips.setFont(_defaultFont);
    tips.setString("spacebar to exit input mode");
    tips.setOrigin(tips.getLocalBounds().width/2, tips.getLocalBounds().height/2);
    tips.setPosition(sf::Vector2f((_window.getSize().x - 390.f), 180.f));
    tips.setCharacterSize(12);
    tips.setFillColor(sf::Color::Red);
    rec.setPosition(sf::Vector2f(500.f, 120.f));
    rec.setSize(sf::Vector2f(500.f, 40.f));
    rec.setFillColor(sf::Color::Black);

    currentName.setFillColor(sf::Color::Black);
    _window.draw(currentName);
    _window.draw(tips);
    _window.draw(rec);
    _window.display();
    currentName.setFillColor(sf::Color::Blue);

    while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (_window.pollEvent(_events) && _events.type == sf::Event::TextEntered)
        {
            if (isalnum(_events.text.unicode) != 0)
                playerInput += _events.text.unicode;
            if (_events.text.unicode =='\b') {
                if (!playerInput.isEmpty()) {
                    playerInput.erase(playerInput.getSize() - 1, 1);
                    currentName.setFillColor(sf::Color::Black);
                    _window.draw(rec);
                    _window.draw(currentName);
                    currentName.setFillColor(sf::Color::Blue);
                }
            }
        }
        currentName.setString(playerInput);
        _window.draw(currentName);
        _window.display();
    }
    if (playerInput == " ") {
        currentName.setString("Player");
        _window.draw(currentName);
    }
    _window.display();
    playerName = std::string(playerInput);
    return currentName;
}

/*!
** @brief Build menu collection with file detected in lib folder
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
** @param libs
**
** @return MenuCollection
*/
MenuCollection Sfml::buildMenu(LibCollection libs, std::string playerName)
{
    MenuCollection menuCol;
    text_t newEntry;
    float space = 100.f;

    newEntry.text = this->newText(playerName, (space += 50.f), sf::Color::Blue);
    newEntry.lib = libs.at(libs.size() - 1);
    newEntry.n = 3;
    menuCol.push_back(newEntry);
    newEntry.text = this->newText("Games:", (space += 50.f), sf::Color::Green);
    newEntry.n = 0;
    menuCol.push_back(newEntry);
    for (int x = 0 ; x < libs.size() ; x++) {
        if (libs.at(x).type == GAME) {
            newEntry.lib = libs.at(x);
            newEntry.n = 1;
            newEntry.text = newText(libs.at(x).name, (space += 40.f));
            menuCol.push_back(newEntry);
        }
    }

    newEntry.text = this->newText("Graphics:", (space += 60.f), sf::Color::Green);
    newEntry.n = 0;
    menuCol.push_back(newEntry);
    for (int x = 0 ; x < libs.size() ; x++) {
        if (libs.at(x).type == GRAPHIC) {
            newEntry.lib = libs.at(x);
            newEntry.n = 2;
            newEntry.text = newText(libs.at(x).name, (space += 40.f));
            menuCol.push_back(newEntry);
        }
    }
    return menuCol;
}

sf::Text Sfml::newText(std::string text, float height, sf::Color color)
{
    sf::Text newT;

    newT.setFont(_defaultFont);
    newT.setString(text);
    newT.setOrigin(newT.getLocalBounds().width/2, newT.getLocalBounds().height/2);
    newT.setPosition(sf::Vector2f((_window.getSize().x/2.f), height));
    newT.setCharacterSize(24);
    newT.setFillColor(color);
    return newT;
}

} /* end of Sfml namespace */

extern "C" {

    IGraphicsModule *getInstance(void)
    {
        IGraphicsModule *instance = new Sfml::Sfml();
        return instance;
    }

    void deleteInstance(IGraphicsModule *instance)
    {
        delete instance;
    }

}