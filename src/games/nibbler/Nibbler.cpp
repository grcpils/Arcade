/*
** EPITECH PROJECT, 2021
** # Nibbler.cpp
** File description:
** Created 26/03/2021 11:45:12
*/

#include "Nibbler.hpp"
#include "Logger.hpp"

Nibbler::Nibbler(void)
    : _name("nibbler"), _lastInput(RIGHT_KEY), _status(RUN), _score(0)
{}

Nibbler::~Nibbler(void)
{}

std::string Nibbler::getName(void) const
{
    return _name;
}

enum Status Nibbler::getStatus(void) const
{
    return _status;
}

void Nibbler::init(void)
{}

bool Nibbler::keyInput(Keys key)
{}

int Nibbler::getScore(void) const
{
    return _score;
}

MapContainer Nibbler::getMap(char *filename)
{}

MapContainer Nibbler::getUpdatedMap(void)
{}

MetaContainer Nibbler::getMetaMap(void)
{}

extern "C" {

    IGamesModule *getInstance(void)
    {
        IGamesModule *instance = new Nibbler();
        return instance;
    }

    void deleteInstance(IGamesModule *instance)
    {
        delete instance;
    }

}