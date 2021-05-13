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

        void loadMap(MapContainer map, MetaContainer meta);
        bool updateScore(int score);
        void refreshMap(MapContainer map, MetaContainer meta);
        enum Keys keyPressed(void);
        void endGame(std::string text);

        enum Keys viewMenu(LibCollection libs, std::string &playerName);

        void setCurrentGame(std::string currentGame);

    private:
        std::string _name;
};