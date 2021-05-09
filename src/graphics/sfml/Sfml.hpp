/*
** EPITECH PROJECT, 2021
** # sfml.hpp
** File description:
** Created 26/03/2021 11:34:43
*/

#include <SFML/Graphics.hpp>
#include "IGraphicsModule.hpp"
#include "Pixel.hpp"

namespace Sfml
{
    class Sfml : public IGraphicsModule
    {
        public:
            Sfml(void);
            ~Sfml(void);

            std::string getName(void) const;

            void loadMap(MapContainer map, MetaContainer meta);
            bool updateScore(int score);
            void refreshMap(MapContainer map, MetaContainer meta);
            enum Keys keyPressed(void);

            void setCurrentGame(std::string currentGame);

        private:
            std::string _name;
            std::string _currentGame;
            std::vector<Pixel> _PixelsMap;

            sf::RenderWindow _window;
            sf::Event _events;

    };
}
