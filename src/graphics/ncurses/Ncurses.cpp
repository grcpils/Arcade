/*
** EPITECH PROJECT, 2021
** # Ncurses.cpp
** File description:
** Created 26/03/2021 11:34:48
*/

#include "Ncurses.hpp"

Ncurses::Ncurses(void)
:   _name("ncurses")
{
    initscr();
    noecho();
}

Ncurses::~Ncurses(void)
{
    endwin();
    std::cout << "ncurses destructed" << std::endl;
}

std::string Ncurses::getName(void) const
{
    return _name;
}

void Ncurses::loadMap(char **map)
{
    static int x, y = 0;

    for (int x = 0 ; map[x] != NULL ; x++)
        for (int y = 0 ; map[x][y] != '\0' ; y++)
            printw("%c", map[x][y]);
    getch();
}

extern "C" {

    IGraphicsModule *getInstance(void)
    {
        IGraphicsModule *instance = new Ncurses();
        return instance;
    }

    void deleteInstance(IGraphicsModule *instance)
    {
        delete instance;
    }

}