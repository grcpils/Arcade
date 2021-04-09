/*
** EPITECH PROJECT, 2021
** # Nibbler.hpp
** File description:
** Created 26/03/2021 11:45:07
*/

#ifndef PACMAN_HPP
#define PACMAN_HPP

#include <string.h>
#include <iostream>
#include <iterator>
#include <map>
#include "IGamesModule.hpp"

class Pacman : public IGamesModule
{
    public:
        Pacman(void);
        ~Pacman(void);

        virtual std::string getName(void) const;
        enum Status getStatus(void) const;

        void init(void);
        bool keyInput(void);

        char **getMap(char *filename);

    private:
        std::string _name;
        char **_map;
        std::map<int, int> _mapCoordonate;
        std::map<std::map<int, int>, char**> _mapMetadata;

        bool checkMapFileValidity(char *filename, FILE *file);
        int *getMapSize(FILE *file);
};

#endif