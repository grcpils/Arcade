/*
** EPITECH PROJECT, 2021
** # Ncurses.cpp
** File description:
** Created 26/03/2021 11:34:48
*/

/*!
** @file Ncurses.cpp
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
** @version 0.1
** @date 2021-05-10
**
** @copyright Copyright (c) 2021
*/

#include "Ncurses.hpp"

/*!
** @brief Construct a new Ncurses object
**
*/
Ncurses::Ncurses(void)
:   _name("ncurses")
{
    initscr();
    keypad(stdscr, TRUE);
    curs_set(0);
    this->initScreen();
}

/*!
** @brief Destroy the Ncurses object
**
*/
Ncurses::~Ncurses(void)
{
    endwin();
}

/*!
** @brief get name of current lib
**
** @return std::string
*/
std::string Ncurses::getName(void) const
{
    return _name;
}

void Ncurses::setCurrentGame(std::string currentGame)
{
    _currentGame = currentGame;
}

/*!
** @brief init all subwindow of screen
**
*/
void Ncurses::initScreen(void)
{
    _w_main = subwin(stdscr, (LINES - 1), (COLS - 1), 0, 0);
    _w_score = subwin(stdscr, 3, 20, 1, 2);

    box(_w_main, ACS_VLINE, ACS_HLINE);
    box(_w_score, ACS_VLINE, ACS_HLINE);

    mvwprintw(_w_score, 1, 2, "Score: %d", 0);
    nodelay(_w_main, true);
    timeout(1);
    refresh();
}

/*!
** @brief Load map with MapContainer and MetaContainer
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
** @param map
** @param meta
**
*/
void Ncurses::loadMap(MapContainer map, MetaContainer meta)
{
    pos_t *size = this->getSizeOfMap(map);
    int h = (LINES / 2) - (size->x / 2);
    int w = (COLS / 2) - (size->y / 2);

    for (int x = 0 ; x < map.size() ; x++) {
        for (int y = 0 ; y < map.at(x).size() ; y++) {
            wmove(_w_main, h, w);
            wrefresh(_w_main);
            wprintw(_w_main, "%c", map.at(x).at(y));
            w++;
        }
        h++;
        w = (COLS / 2) - size->y / 2;
        box(_w_main, ACS_VLINE, ACS_HLINE);
    }

    free(size);
}

/*!
** @brief Refresh map from MapContainer and MetaContainer
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
** @param map
** @param meta
**
*/
void Ncurses::refreshMap(MapContainer map, MetaContainer meta)
{
    this->loadMap(map, meta);
}

/*!
** @brief Return actual pressed Key in Arcade Standard Keys Type
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
**
** @return Keys
*/
Keys Ncurses::keyPressed(void)
{
    Keys ret = NIL_KEY;
    int ch = getch();

    switch (ch) {
        case 10:
            ret = EXIT_KEY;
            break;
        case KEY_UP:
            ret = UP_KEY;
            break;
        case KEY_DOWN:
            ret = DOWN_KEY;
            break;
        case KEY_LEFT:
            ret = LEFT_KEY;
            break;
        case KEY_RIGHT:
            ret = RIGHT_KEY;
            break;
        case 'n':
            ret = NEXTLIB_KEY;
            break;
        case 'p':
            ret = PREVLIB_KEY;
            break;
        default:
            break;
    }
    return ret;
}

/*!
** @brief Update the score from an integer
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
** @param score
**
** @return true
** @return fals
*/
bool Ncurses::updateScore(int score)
{
    mvwprintw(_w_score, 1, 2, "Score: %d", score);
}

/*!
** @brief Get the size of Map from MapContainer
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
** @param map
**
** @return pos_t* with x equal height and y equal width of map
*/
pos_t *Ncurses::getSizeOfMap(MapContainer map) const
{
    pos_t *size = (pos_t*) malloc(sizeof(pos_t));

    size->x = map.size();
    size->y = map.at(0).size();
    return size;
}

extern "C" {

    IGraphicsModule *getInstance(void)
    {
        IGraphicsModule *instance = new Ncurses();
        return instance;
    }

    void deleteInstance(IGraphicsModule *instance)
    {
        delete instance;
    }

}