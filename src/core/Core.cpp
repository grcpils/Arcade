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
    :   _graphicLib(NULL), _gameLib(NULL)
    {
        Log("New Core", 0);
        if (ac < 2) {
            this->usage();
            exit(84);
        }
        DLLoader<IGraphicsModule> *libptr = new DLLoader<IGraphicsModule>(av[1]);
        _graphicLib = libptr->getInstance();

        // anything with graphiclib

        libptr->destroyInstance();
    }

    Core::~Core(void)
    {}

    void Core::usage(void)
    {
        printf("./arcade <graphic library>\n");
    }

}