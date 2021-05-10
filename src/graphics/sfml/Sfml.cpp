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
:   _name("sfml"), _window(sf::VideoMode(1280, 720), "Arcade::Window")
{

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
{}

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
    _ShapeMap = this->contructShapedMap(map, meta);

    for (int x = 0 ; x < _ShapeMap.size() ; x++) {
        _window.draw(_ShapeMap.at(x));
    }

    _window.display();
}

ShapedMapContainer Sfml::contructShapedMap(MapContainer map, MetaContainer meta)
{
    ShapedMapContainer newShapedMap;
    sf::RectangleShape pixel;
    const float xf = 30.f;
    const float yf = 10.f;
    float xs, ys;

    xs = xf;
    ys = yf;
    for (int x = 0 ; x < map.size() ; x++) {
        for (int y = 0 ; y < map.at(x).size() ; y++) {
            switch (meta.at(x).at(y)) {
                case WALL:
                    pixel.setPosition(sf::Vector2f(ys, xs));
                    pixel.setSize(sf::Vector2f(yf, xf));
                    pixel.setFillColor(sf::Color(0, 35, 240));
                    newShapedMap.push_back(pixel);
                    break;
                case IWALL:
                    pixel.setPosition(sf::Vector2f(ys, xs));
                    pixel.setSize(sf::Vector2f(yf, xf));
                    pixel.setFillColor(sf::Color::Black);
                    newShapedMap.push_back(pixel);
                    break;
                case PLAYER:
                    pixel.setPosition(sf::Vector2f(ys + 2.5f, xs + 7.5f));
                    pixel.setSize(sf::Vector2f(yf + 5.f, xf - 15.f));
                    pixel.setFillColor(sf::Color(255, 225, 0));
                    newShapedMap.push_back(pixel);
                    break;
                default:
                    break;
            }
            ys += yf;
        }
        ys = yf;
        xs += xf;
    }
    return newShapedMap;
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
    _window.clear(sf::Color::Black);

    _ShapeMap = this->contructShapedMap(map, meta);

    for (int x = 0 ; x < _ShapeMap.size() ; x++) {
        _window.draw(_ShapeMap.at(x));
    }

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
    default:
        break;
    }
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