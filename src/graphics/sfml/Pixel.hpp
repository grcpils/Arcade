/*
** EPITECH PROJECT, 2021
** # Pixels.hpp
** File description:
** Created 08/05/2021 18:32:03
*/

#ifndef PIXEL_HPP_
#define PIXEL_HPP_

namespace Sfml
{

    typedef struct pixel_s
    {
        sf::RectangleShape shape;
        MapMetadata meta;
    } pixel_t;

};


#endif