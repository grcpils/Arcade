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

void Sdl2::loadMap(MapContainer map, MetaContainer meta)
{}

void Sdl2::refreshMap(MapContainer map, MetaContainer meta)
{}

enum Keys Sdl2::keyPressed(void)
{}

enum Keys Sdl2::viewMenu(LibCollection libs, std::string &playerName, std::vector<std::pair<std::string, int>> scores)
{}

void Sdl2::endGame(std::string text, int score)
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