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
#include <iterator>
#include <map>
#include "IGraphicsModule.hpp"

class Ncurses : public IGraphicsModule
{
    public:
        Ncurses(void);
        ~Ncurses(void);

        std::string getName(void) const;
        void loadMap(std::vector<std::vector<char>> map);
        bool updateScore(int score);
        Keys keyPressed(void);
        void refreshMap(std::vector<std::vector<char>> map);

    private:
        std::string _name;
        WINDOW *_w_main;
        WINDOW *_w_score;
        WINDOW *_w_command;

        pos_t *getSizeOfMap(std::vector<std::vector<char>> vec) const;
        void initScreen(void);
};

#endif