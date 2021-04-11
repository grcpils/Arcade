/*
** EPITECH PROJECT, 2021
** # IGraphicsModule.hpp
** File description:
** Created 26/03/2021 11:28:10
*/

#ifndef IGAMES_HPP
#define IGAMES_HPP

#include <ostream>
#include <string>

typedef enum Keys { K_UP, K_DOWN, K_LEFT, K_RIGHT, K_MENU, NIL } Keys;

class IGraphicsModule
{
    public:
        virtual ~IGraphicsModule(void) = default;

        virtual std::string getName(void) const = 0;

        virtual void loadMap(char **map) = 0;
        virtual void refreshMap(char **map) = 0;
        virtual enum Keys keyPressed(void) = 0;

    private:
};

#endif