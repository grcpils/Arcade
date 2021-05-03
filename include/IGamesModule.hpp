/*
** EPITECH PROJECT, 2021
** # IGamesModule.hpp
** File description:
** Created 26/03/2021 11:28:16
*/

#ifndef IGRAPHICS_HPP
#define IGRAPHICS_HPP

#include <ostream>
#include <string>
#include <iterator>
#include <vector>
#include "Keys.hpp"
#include "Position.hpp"

typedef enum Status { RUN, WIN, LOOSE } Status;

class IGamesModule
{
    public:
        virtual ~IGamesModule(void) = default;

        virtual std::string getName(void) const = 0;
        virtual enum Status getStatus(void) const = 0;

        virtual void init(void) = 0;
        virtual bool keyInput(Keys key) = 0;

        virtual std::vector<std::vector<char>> getMap(char *filename) = 0;
        virtual std::vector<std::vector<char>> getUpdatedMap(void) = 0;

    private:
};

#endif