/*
** EPITECH PROJECT, 2021
** # ncurses.hpp
** File description:
** Created 26/03/2021 11:34:43
*/

#ifndef NCURSES_HPP
#define NCURSES_HPP

#include <iostream>
#include <ncurses.h>
#include <string.h>
#include "IGraphicsModule.hpp"

class Ncurses : public IGraphicsModule
{
    public:
        Ncurses(void);
        ~Ncurses(void);

        std::string getName(void) const;

    private:
        std::string _name;
};

#endif