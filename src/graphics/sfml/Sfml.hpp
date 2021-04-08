/*
** EPITECH PROJECT, 2021
** # sfml.hpp
** File description:
** Created 26/03/2021 11:34:43
*/

#include "IGraphicsModule.hpp"

class Sfml : public IGraphicsModule
{
    public:
        Sfml(void);
        ~Sfml(void);

        std::string getName(void) const;

    private:
        std::string _name;
};