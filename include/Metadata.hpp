/*
** EPITECH PROJECT, 2021
** # Metadata.hpp
** File description:
** Created 09/05/2021 16:04:41
*/

#ifndef METADATA_HPP_
#define METADATA_HPP_

#include <vector>

typedef enum MapMetadata { NIL, WALL, PATH, PLAYER, MONSTER, BONUS } MapMetadata;
typedef std::vector<std::vector<MapMetadata>> MetaContainer;

#endif