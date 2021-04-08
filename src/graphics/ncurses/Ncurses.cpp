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
    curs_set(0);
    move(LINES / 2, (COLS / 2) - strlen(_name.c_str()));
    printw(_name.c_str());
    refresh();
    getch();
    std::cout << "ncurses initied" << std::endl;
}

Ncurses::~Ncurses(void)
{
    endwin();
    std::cout << "ncurses destroyed" << std::endl;
}

std::string Ncurses::getName(void) const
{
    return _name;
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