/*
** EPITECH PROJECT, 2021
** # Core.hpp
** File description:
** Created 06/04/2021 10:49:34
*/

#ifndef CORE_HPP
#define CORE_HPP

#include "Arcade.hpp"

namespace Arcade {

    class Core
    {
        public:
            Core(int ac, char **av);
            ~Core(void);

            void usage(void);

        private:
            IGraphicsModule *_graphicLib;
            IGamesModule *_gameLib;
    };

}

#endif