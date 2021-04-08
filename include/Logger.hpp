/*
** EPITECH PROJECT, 2021
** # Logger.hpp
** File description:
** Created 26/03/2021 16:36:16
*/

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <stdarg.h>
#include <string.h>

#define Log(msg, ...) logger(__LINE__, __FILE__, msg, __VA_ARGS__)

void logger(int line, const char *filename, const char *msg, ...);

#endif