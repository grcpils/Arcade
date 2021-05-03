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

        void loadMap(std::vector<std::vector<char>> map);
        void refreshMap(std::vector<std::vector<char>> map);
        enum Keys keyPressed(void);

    private:
        std::string _name;
};