/*
** EPITECH PROJECT, 2021
** # IGraphicsModule.hpp
** File description:
** Created 26/03/2021 11:28:10
*/

#ifndef IGAMES_HPP
#define IGAMES_HPP

#include <ostream>
#include <thread>
#include <string>
#include <iterator>
#include <vector>
#include "Keys.hpp"
#include "Position.hpp"
#include "Map.hpp"
#include "Metadata.hpp"

class IGraphicsModule
{
    public:
        virtual ~IGraphicsModule(void) = default;

        virtual std::string getName(void) const = 0;

        virtual void loadMap(MapContainer map, MetaContainer meta) = 0;
        virtual void refreshMap(MapContainer map, MetaContainer meta) = 0;
        virtual bool updateScore(int score) = 0;
        virtual enum Keys keyPressed(void) = 0;

        virtual void setCurrentGame(std::string currentGame) = 0;

    private:
};

/*!
** @fn IGraphicsModule *getInstance(void)
** @brief Get an Instance of IGraphicsModule Object
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
** @return Pointer to IGraphicsModule Object
*/

/*!
** @fn void deleteInstance(IGraphicsModule *instance)
** @brief Delete an Instance of IGraphicsModule Object
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
** @param instance
*/

#endif