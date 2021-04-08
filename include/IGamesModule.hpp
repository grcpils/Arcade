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
#include "IGraphicsModule.hpp"

typedef enum Status { RUN, WIN, LOOSE } Status;

class IGamesModule
{
    public:
        virtual ~IGamesModule(void) = default;

        virtual std::string getName(void) const;
        virtual enum Status getStatus(void) const;

        virtual void init(void);
        virtual enum Status getStatus(void);
        virtual bool keyInput(void);

    private:
};

#endif