/*
** EPITECH PROJECT, 2021
** # Libraries.hpp
** File description:
** Created 11/05/2021 17:24:18
*/

#ifndef LIBRARIES_HPP_
#define LIBRARIES_HPP_

#include <vector>

typedef enum { GAME, GRAPHIC, PSEUDO, UNKNOWN } libType;

typedef struct lib_s
{
    char *name;
    char *origin_name;
    libType type;
} lib_t;

typedef std::vector<lib_t> LibCollection;

#endif