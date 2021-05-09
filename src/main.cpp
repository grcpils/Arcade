/*
** EPITECH PROJECT, 2021
** # main.cpp
** File description:
** Created 25/03/2021 15:01:28
*/

#include "Arcade.hpp"
#include "Core.hpp"

int main(int ac, char **av)
{
    Log("Init arcade",0);
    Arcade::Core *core = new Arcade::Core(ac, av);

    if (core->gameloop() == -1) {
        delete core;
        return (84);
    }
    delete core;
    return (0);
}