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

class IGraphicsModule
{
    public:
        virtual ~IGraphicsModule(void) = default;

        virtual std::string getName(void) const;

        virtual void drawShape();

    private:
};

#endif