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

class Pacman : public IGamesModule
{
    public:
        Pacman(void); 
        ~Pacman(void);

        virtual std::string getName(void) const;
        enum Status getStatus(void) const;
        int getScore(void) const;

        void init(void);
        bool keyInput(Keys key);

        MapContainer getMap(char *filename);
        MapContainer getUpdatedMap(void);
        MetaContainer getMetaMap(void);

    private:
        std::string _name;
        pos_t* _mapSize;
        MapContainer _map;
        MetaContainer _mapMetaData;
        pos_t* _s_player;
        std::vector<pos_t> _s_monsters;
        std::vector<MapMetadata> _monster_old;
        int _bonus;
        Keys _lastInput;
        Status _status;
        int _score;

        bool checkMapFileValidity(char *filename, FILE *file);
        pos_t *getMapSize(FILE *file);
        MapMetadata getMetaOf(char c);
        void buildMetaData(void);
        pos_t *getPlayerPos(void);
        std::vector<pos_t> getMonstersPos(void);

        void moveMonsters(void);
};

#endif