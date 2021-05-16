/*
** EPITECH PROJECT, 2021
** # Core.hpp
** File description:
** Created 06/04/2021 10:49:34
*/

#ifndef CORE_HPP
#define CORE_HPP

#include "Arcade.hpp"

namespace Arcade {

    class Core
    {
        public:
            Core(int ac, char **av);
            ~Core(void);

            void usage(void);
            int gameloop(const char *filemap);
            int menu(void);
            int checkGameStatus(void);

        private:
            Scoreboard _scoreboard;
            DLLoader<IGraphicsModule> *_graphicPtr;
            DLLoader<IGamesModule> *_gamePtr;
            IGraphicsModule *_graphicLib;
            IGamesModule *_gameLib;
            LibCollection _libraries;
            std::string _playerName;
            int _score;

            void inputManager(void);
            void loadLibsFromFolder(void);
            int startGame(const char *gameLib, const char *gameMap);
            int changeGraphics(const char *graphicLib);
            int updateScoreBoard(void);
    };

}

#endif