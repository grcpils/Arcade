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
#include <random>
#include "IGamesModule.hpp"

typedef enum MapMetadata { NIL, WALL, PATH, PLAYER, MONSTER, BONUS } MapMetadata;

class Pacman : public IGamesModule
{
    public:
        Pacman(void);
        ~Pacman(void);

        virtual std::string getName(void) const;
        enum Status getStatus(void) const;

        void init(void);
        bool keyInput(Keys key);

        char **getMap(char *filename);
        char **getUpdatedMap(void);

    private:
        std::string _name;  
        int* _mapSize; // TODO replace int* by struct
        char **_map;
        int* _s_player; // TODO replace int* by struct

        bool checkMapFileValidity(char *filename, FILE *file);
        int *getMapSize(FILE *file);
        MapMetadata getMetaOf(char c);
        int *getPlayerPos(void);
};

#endif