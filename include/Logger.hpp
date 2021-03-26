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

#define LOG(msg, ...) logger(__LINE__, __FILE__, msg, __VA_ARGS__)

void logger(int line, const char *filename, const char *msg, ...)
{
    va_list args;
    char buffer[256] = { 0 };
    sprintf(buffer, "[%s:%d] ", strrchr(filename, '/') + 1, line);
    std::cout << buffer;

    va_start(args, msg);
    vsprintf(buffer, msg, args);
    std::cout << buffer << std::endl;
    va_end(args);
}

#endif