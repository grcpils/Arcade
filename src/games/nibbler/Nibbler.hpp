/*
** EPITECH PROJECT, 2021
** # Nibbler.hpp
** File description:
** Created 26/03/2021 11:45:07
*/

#include "IGamesModule.hpp"

class Nibbler : public IGamesModule
{
    public:
        Nibbler(void);
        ~Nibbler(void);

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
        Keys _lastInput;
        Status _status;
        int _score;
};