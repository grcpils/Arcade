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
        void loadMap(MapContainer map, MetaContainer meta);
        bool updateScore(int score);
        Keys keyPressed(void);
        void refreshMap(MapContainer map, MetaContainer meta);

        enum Keys viewMenu(LibCollection libs, std::string &playerName);

        void setCurrentGame(std::string currentGame);

    private:
        std::string _name;
        std::string _currentGame;
        WINDOW *_w_main;
        WINDOW *_w_score;
        WINDOW *_w_menu;

        pos_t *getSizeOfMap(MapContainer map) const;
        void initScreen(void);
};

#endif