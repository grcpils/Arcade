/*
** EPITECH PROJECT, 2021
** # Ncurses.cpp
** File description:
** Created 26/03/2021 11:34:48
*/

#include "Ncurses.hpp"

/*
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

/*
** @brief Destroy the Ncurses object
**
*/
Ncurses::~Ncurses(void)
{
    endwin();
}

/*
** @brief get name of current lib
**
** @return std::string
*/
std::string Ncurses::getName(void) const
{
    return _name;
}

/*
** @brief init all subwindow of screen
**
*/
void Ncurses::initScreen(void)
{
    _w_main = subwin(stdscr, (LINES - 1), (COLS - 1), 0, 0);
    _w_command = subwin(stdscr, 3, 50, 1, 2);
    _w_score = subwin(stdscr, 3, 20, 1, 54);

    box(_w_main, ACS_VLINE, ACS_HLINE);
    box(_w_command, ACS_VLINE, ACS_HLINE);
    box(_w_score, ACS_VLINE, ACS_HLINE);

    mvwprintw(_w_command, 1, 2, "QUIT: press enter", 0);
    mvwprintw(_w_score, 1, 2, "Score: %d", 0);
    refresh();
}

/*
** @brief load map from char**
**
** @param map
*/
void Ncurses::loadMap(char **map)
{
    int *size = this->getSizeOfArr(map);
    int h = (LINES / 2) - (size[0] / 2);
    int w = (COLS / 2) - (size[1] / 2);

    for (int x = 0 ; map[x] != NULL ; x++) {
        for (int y = 0 ; map[x][y] != '\0' ; y++) {
            wmove(_w_main, h, w);
            wrefresh(_w_main);
            wprintw(_w_main, "%c", map[x][y]);
            w++;
        }
        h++;
        w = (COLS / 2) - size[1] / 2;
        box(_w_main, ACS_VLINE, ACS_HLINE);
    }
    free(size);
}

/*
** @brief refresh map after game edit it
**
** @param map
*/
void Ncurses::refreshMap(char **map)
{
    this->loadMap(map);
}

/*
** @brief return value of pressed key
**
** @return Keys
*/
Keys Ncurses::keyPressed(void)
{
    Keys ret = NIL_KEY;
    int ch = getch();

    switch (ch) {
        case 10:
            ret = MENU_KEY;
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
        default:
            break;
    }
    return ret;
}

bool Ncurses::updateScore(int score)
{

}

/*
** @brief get size of an array
**
** @param arr
** @return int* with [0] = number of line & [1] = number of cols
*/
int *Ncurses::getSizeOfArr(char **arr) const
{
    int *size = (int*) malloc(sizeof(int) * 3);
    char chr;

    size[0] = 0;
    size[1] = 0;
    for (int x = 0 ; arr[x] != NULL ; x++)
        for (int y = 0 ; arr[x][y] != '\0' ; y++) {
            if (arr[x][y] == '\n')
                size[0]++;
            if (arr[x][y] != '\n' && size[0] == 0)
                size[1]++;
        }
    size[0]++;
    size[1]++;
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