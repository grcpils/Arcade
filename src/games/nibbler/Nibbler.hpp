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
        Nibbler(char *filename = NULL);
        ~Nibbler(void);

        void init(void);
        enum Status getStatus(void);
        bool keyInput(void);

        char **getMap(char *filename);

    private:
        char *_filename;
        char **_map;
};