/*
** EPITECH PROJECT, 2021
** # Metadata.hpp
** File description:
** Created 09/05/2021 16:04:41
*/

#ifndef METADATA_HPP_
#define METADATA_HPP_

#include <vector>

/*!
** @brief Metadata possible value
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
*/
typedef enum MapMetadata { NIL, WALL, IWALL, PATH, PPATH, PLAYER, KMONSTER, MONSTER, BONUS } MapMetadata;

/*!
** @brief Map Metadata container
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
*/
typedef std::vector<std::vector<MapMetadata>> MetaContainer;

#endif