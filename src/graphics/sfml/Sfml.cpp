/*
** EPITECH PROJECT, 2021
** # Sfml.cpp
** File description:
** Created 26/03/2021 11:43:04
*/

#include "Sfml.hpp"

namespace Sfml
{

Sfml::Sfml(void)
:   _name("sfml")
{
    sf::RenderWindow _window(sf::VideoMode(1080, 720), "SFML works!");
    while (_window.isOpen())
    {
        while (_window.pollEvent(_events))
        {
            if (_events.type == sf::Event::Closed)
                _window.close();
        }

        _window.clear();
        _window.display();
    }
}

Sfml::~Sfml(void)
{}

std::string Sfml::getName(void) const
{
    return _name;
}

void Sfml::setCurrentGame(std::string currentGame)
{
    _currentGame = currentGame;
}

void Sfml::loadMap(MapContainer map, MetaContainer meta)
{}

void Sfml::refreshMap(MapContainer map, MetaContainer meta)
{}

enum Keys Sfml::keyPressed(void)
{}

}

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