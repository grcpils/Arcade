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
{}

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
    // pos.x = xf;
    // pos.y = yf;
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
                    pixel.shape.setFillColor(sf::Color(255, 0, 255));
                    _ShapeMap.push_back(pixel);
                    break;
                case MONSTER:
                    pixel.meta = MONSTER;
                    pixel.shape.setPosition(sf::Vector2f(pos.y - 5.f, pos.x + 5.f));
                    pixel.shape.setSize(sf::Vector2f(yf + 10.f, xf - 10.f));
                    pixel.shape.setFillColor(sf::Color(0, 200, 255));
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
                    pixel.shape.setFillColor(sf::Color(255, 150, 0));
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
     _window.clear(sf::Color::Black);
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
            _window.close();
            return EXIT_KEY;
            break;
        case sf::Event::KeyPressed:
            return this->readKeyInput(_events.key.code);
        default:
            return NIL_KEY;
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
    case sf::Keyboard::Enter:
        return EXIT_KEY;
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