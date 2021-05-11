/*
** EPITECH PROJECT, 2021
** # Position.hpp
** File description:
** Created 03/05/2021 16:13:55
*/

#ifndef POSITION_HPP_
#define POSITION_HPP_

/*!
** @brief Position in integer form (x, y)
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
*/
typedef struct position_s
{
    int x;  /* Position x */
    int y;  /* Position y */
} pos_t;

/*!
** @brief Position in float form (x, y)
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
*/
typedef struct float_position_s
{
    float x;  /* Position x */
    float y;  /* Position y */
} posf_t;

/*!
** @brief Position in unsigned int form (x, y)
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
*/
typedef struct uint_position_s
{
    unsigned int x;  /* Position x */
    unsigned int y;  /* Position y */
} posu_t;

#endif