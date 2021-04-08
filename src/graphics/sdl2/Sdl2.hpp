/*
** EPITECH PROJECT, 2021
** # sdl2.hpp
** File description:
** Created 26/03/2021 11:34:43
*/

#include "IGraphicsModule.hpp"

class Sdl2 : public IGraphicsModule
{
    public:
        Sdl2(void);
        ~Sdl2(void);

        std::string getName(void) const;

    private:
        std::string _name;
};