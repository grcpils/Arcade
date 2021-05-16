/*
** EPITECH PROJECT, 2021
** # Scoreboard.hpp
** File description:
** Created 16/05/2021 10:00:55
*/

#ifndef SCOREBOARD_HPP_
#define SCOREBOARD_HPP_

#include "Arcade.hpp"
#include <algorithm>
#include <vector>
#include <tuple>
#include <iostream>
#include <fstream>
#include <string>

namespace Arcade
{

    class Scoreboard
    {
        public:
            Scoreboard(void);
            ~Scoreboard(void);

            bool setFile(char *filename);
            bool add(std::string playerName, int playerScore);
            std::vector<std::pair<std::string, int>> get(void);

        private:
            char* _scoreFilename;
            std::vector<std::pair<std::string, int>> _scores;

            bool extractFromFile(void);
            bool insertInFile(void);
            bool sort(void);
            // bool comparator(std::pair<std::string, int> &a, std::pair<std::string, int> &b);
            int findLowest(int current);
    };

} /* namespace Arcade */

#endif