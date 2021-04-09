/*
** EPITECH PROJECT, 2021
** # Core.cpp
** File description:
** Created 06/04/2021 10:51:35
*/

#include "Core.hpp"
#include "Logger.hpp"

namespace Arcade {

    Core::Core(int ac, char **av)
    :   _graphicLib(NULL), _gameLib(NULL), _graphicPtr(NULL), _gamePtr(NULL)
    {
        Log("New Core", 0);
        if (ac < 2) {
            this->usage();
            exit(84);
        }
        _graphicPtr = new DLLoader<IGraphicsModule>(av[1]);
        _graphicLib = _graphicPtr->getInstance();

        _gamePtr = new DLLoader<IGamesModule>("lib/arcade_pacman.so");
        _gameLib = _gamePtr->getInstance();

        this->gameloop();
    }

    Core::~Core(void)
    {
        _graphicPtr->destroyInstance();
        _gamePtr->destroyInstance();
        Log("Core destroyed", 0);
    }

    int Core::gameloop(void)
    {
        char **map = _gameLib->getMap("mapping/map1.nbl");
        Log("Stating gameloop", 0);
        _graphicLib->loadMap(map);
        return (0);
    }

    void Core::usage(void)
    {
        printf("./arcade <graphic library>\n");
    }

}