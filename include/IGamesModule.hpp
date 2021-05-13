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
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "Keys.hpp"
#include "Position.hpp"
#include "Map.hpp"
#include "Metadata.hpp"

typedef enum Status { RUN, WIN, LOOSE } Status;

class IGamesModule
{
    public:
        virtual ~IGamesModule(void) = default;

        virtual std::string getName(void) const = 0;
        virtual enum Status getStatus(void) const = 0;
        virtual int getScore(void) const = 0;

        virtual void init(void) = 0;
        virtual bool keyInput(Keys key) = 0;

        virtual MapContainer getMap(char *filename) = 0;
        virtual MapContainer getUpdatedMap(void) = 0;
        virtual MetaContainer getMetaMap(void) = 0;

    private:
};

/*!
** @fn IGamesModule *getInstance(void)
** @brief Get an Instance of IGamesModule Object
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
** @return Pointer to IGamesModule Object
*/

/*!
** @fn void deleteInstance(IGamesModule *instance)
** @brief Delete an Instance of IGamesModule Object
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
** @param instance
*/

#endif