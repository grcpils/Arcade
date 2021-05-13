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

#define BLANK_INPUT "       "

#define MENU_HEADER 101
#define MENU_SELECT 102

#define GAME_PLAYER 201
#define GAME_MONSTER 202
#define GAME_WALL 203
#define GAME_IWALL 204
#define GAME_BONUS 205
#define GAME_PATH 206
#define GAME_PPATH 207


namespace Ncurses
{
    typedef struct entry_s
    {
        char *text;
        lib_t lib;
        int n;
    } entry_t;

    typedef std::vector<entry_t> MenuCollection;

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
            void endGame(std::string text);

            enum Keys viewMenu(LibCollection libs, std::string &playerName);

            void setCurrentGame(std::string currentGame);

        private:
            std::string _name;
            std::string _currentGame;
            WINDOW *_w_main;
            WINDOW *_w_score;
            WINDOW *_w_menu;
            MenuCollection _menu;

            pos_t *getSizeOfMap(MapContainer map) const;
            void initScreen(void);

            void initColorPair(void);

            int printMenu(LibCollection libs, int select);
            int buildMenu(LibCollection libs, std::string playerName);
            char *getNewPlayerName(char *currentName, std::string &playerName);
    };

}

#endif