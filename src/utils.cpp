/*
** EPITECH PROJECT, 2021
** # utils.cpp
** File description:
** Created 06/04/2021 10:46:35
*/

#include "Arcade.hpp"

void logger(int line, const char *filename, const char *msg, ...)
{
    va_list args;
    char buffer[256] = { 0 };
    sprintf(buffer, "[%s:%d] ", strrchr(filename, '/') + 1, line);
    if (DEBUG == true)
        std::cout << buffer;

    va_start(args, msg);
    vsprintf(buffer, msg, args);
    if (DEBUG == true)
        std::cout << buffer << std::endl;
    va_end(args);
}