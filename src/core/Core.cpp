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
    :   _graphicLib(NULL), _gameLib(NULL), _graphicPtr(NULL), _gamePtr(NULL),
        _exitStatus(false)
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
    }

    Core::~Core(void)
    {
        _graphicPtr->destroyInstance();
        _gamePtr->destroyInstance();
        delete _gamePtr;
        delete _graphicPtr;
        Log("Core destroyed", 0);
    }

    int Core::gameloop(void)
    {
        std::vector<std::vector<char>> map = _gameLib->getMap("mapping/map.pcm");
        Keys input = NIL_KEY;
        if (map.empty() == 1)
            return (-1);
        _gameLib->init();
        _graphicLib->loadMap(map, _gameLib->getMetaMap());
        std::thread imanager(&Core::inputManager, this);
        fprintf(stderr, "Main loop Started.\n");
        while (_exitStatus != true) {
            _graphicLib->refreshMap(_gameLib->getUpdatedMap(), _gameLib->getMetaMap());
            _graphicLib->updateScore(_gameLib->getScore());
        }
        return (0);
    }

    void Core::inputManager(void)
    {
        Keys input = NIL_KEY;

        fprintf(stderr, "Input Manager Started.\n");
        while (input != NIL_KEY) {
            input = _graphicLib->keyPressed();
            _gameLib->keyInput(input);
        }
        _exitStatus = true;
    }

    void Core::usage(void)
    {
        printf("./arcade <graphic library>\n");
    }

}