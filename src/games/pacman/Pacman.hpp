/*
** EPITECH PROJECT, 2021
** # Pacman.hpp
** File description:
** Created 26/03/2021 11:45:07
*/

#ifndef PACMAN_HPP
#define PACMAN_HPP

#include <string.h>
#include <iostream>
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

        std::vector<std::vector<char>> getMap(char *filename);
        std::vector<std::vector<char>> getUpdatedMap(void);

    private:
        std::string _name;
        pos_t* _mapSize;
        std::vector<std::vector<char>> _map;
        std::vector<std::vector<MapMetadata>> _mapMetaData;
        pos_t* _s_player;
        Keys _lastInput;
        Status _status;

        bool checkMapFileValidity(char *filename, FILE *file);
        pos_t *getMapSize(FILE *file);
        MapMetadata getMetaOf(char c);
        void buildMetaData(void);
        pos_t *getPlayerPos(void);
};

#endif