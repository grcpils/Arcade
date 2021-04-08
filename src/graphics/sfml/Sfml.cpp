/*
** EPITECH PROJECT, 2021
** # Sfml.cpp
** File description:
** Created 26/03/2021 11:43:04
*/

#include "Sfml.hpp"

Sfml::Sfml(void)
:   _name("sfml")
{}

Sfml::~Sfml(void)
{}

std::string Sfml::getName(void) const
{
    return _name;
}


extern "C" {

    IGraphicsModule *getInstance(void)
    {
        IGraphicsModule *instance = new Sfml();
        return instance;
    }

    void deleteInstance(IGraphicsModule *instance)
    {
        delete instance;
    }

}