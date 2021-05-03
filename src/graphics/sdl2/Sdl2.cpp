/*
** EPITECH PROJECT, 2021
** # Sdl2.cpp
** File description:
** Created 26/03/2021 11:41:57
*/

#include "Sdl2.hpp"

Sdl2::Sdl2(void)
:   _name("sdl2")
{}

Sdl2::~Sdl2(void)
{}

std::string Sdl2::getName(void) const
{
    return _name;
}

void Sdl2::loadMap(std::vector<std::vector<char>> map)
{}

void Sdl2::refreshMap(std::vector<std::vector<char>> map)
{}

enum Keys Sdl2::keyPressed(void)
{}


extern "C" {

    IGraphicsModule *getInstance(void)
    {
        IGraphicsModule *instance = new Sdl2();
        return instance;
    }

    void deleteInstance(IGraphicsModule *instance)
    {
        delete instance;
    }

}