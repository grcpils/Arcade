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

namespace Ncurses
{

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

    if (!has_colors())
        fprintf(stderr, "No color support in this terminal!\n");

    start_color();
    this->initColorPair();

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

void Ncurses::initColorPair(void)
{
    init_pair(MENU_HEADER, COLOR_GREEN, COLOR_BLACK);
    init_pair(MENU_SELECT, COLOR_MAGENTA, COLOR_BLACK);

    init_pair(GAME_PLAYER, COLOR_YELLOW, COLOR_BLACK);
    init_pair(GAME_MONSTER, COLOR_CYAN, COLOR_BLACK);
    init_pair(GAME_WALL, COLOR_BLUE, COLOR_BLACK);
    init_pair(GAME_IWALL, COLOR_BLACK, COLOR_BLACK);
    init_pair(GAME_BONUS, COLOR_RED, COLOR_BLACK);
    init_pair(GAME_PATH, COLOR_BLACK, COLOR_BLACK);
    init_pair(GAME_PPATH, COLOR_YELLOW, COLOR_BLACK);
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
    _w_menu = subwin(stdscr, 15, 19, (LINES / 2) - (15 / 2), (COLS / 2) - ((19 / 2) - 26));
    box(_w_main, ACS_VLINE, ACS_HLINE);
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
    wclear(_w_menu);

    mvwprintw(_w_main, 5, 3, "n for the next graphic library");
    mvwprintw(_w_main, 6, 3, "p for the previous graphic library");

    mvwprintw(_w_main, 8, 3, "c for the next game");
    mvwprintw(_w_main, 9, 3, "v for the previous game");

    for (int x = 0 ; x < map.size() ; x++) {
        for (int y = 0 ; y < map.at(x).size() ; y++) {
            wmove(_w_main, h, w);

            switch (meta.at(x).at(y)) {
            case PLAYER:
                wattron(_w_main, COLOR_PAIR(GAME_PLAYER));
                wprintw(_w_main, "%c", map.at(x).at(y));
                break;
            case MONSTER:
                wattron(_w_main, COLOR_PAIR(GAME_MONSTER));
                wprintw(_w_main, "M");
                break;
            case KMONSTER:
                wattron(_w_main, COLOR_PAIR(GAME_BONUS));
                wprintw(_w_main, "M");
                break;
            case BONUS:
                wattron(_w_main, COLOR_PAIR(GAME_BONUS));
                wprintw(_w_main, "*");
                break;
            case PATH:
                wattron(_w_main, COLOR_PAIR(GAME_PATH));
                wprintw(_w_main, " ");
                break;
            case PPATH:
                wattron(_w_main, COLOR_PAIR(GAME_PPATH));
                wprintw(_w_main, ".");
                break;
            case IWALL:
                wattron(_w_main, COLOR_PAIR(GAME_IWALL));
                wprintw(_w_main, " ");
                break;
            case WALL:
                wattron(_w_main, COLOR_PAIR(GAME_WALL));
                wprintw(_w_main, "#");
                break;
            default:
                break;
            }
            wattroff(_w_main, COLOR_PAIR(GAME_PLAYER));
            wattroff(_w_main, COLOR_PAIR(GAME_MONSTER));
            wattroff(_w_main, COLOR_PAIR(GAME_BONUS));
            wattroff(_w_main, COLOR_PAIR(GAME_PATH));
            wattroff(_w_main, COLOR_PAIR(GAME_PPATH));
            wattroff(_w_main, COLOR_PAIR(GAME_IWALL));
            wattroff(_w_main, COLOR_PAIR(GAME_WALL));
            w++;
            wrefresh(_w_main);
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
        case 27:
            ret = MENU_KEY;
            break;
        case 10:
            ret = ENTER_KEY;
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
    box(_w_score, ACS_VLINE, ACS_HLINE);
    mvwprintw(_w_score, 1, 2, "Score: %d", score);
    wrefresh(_w_score);
    return true;
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

enum Keys Ncurses::viewMenu(LibCollection libs, std::string &playerName, std::vector<std::pair<std::string, int>> scores)
{
    static int select = 2;
    Keys input = this->keyPressed();

    wclear(_w_main);
    box(_w_menu, ACS_VLINE, ACS_HLINE);
    mvwprintw(_w_menu, 2, 6, "ARCADE");

    int scbH = 3;
    _w_scoreboard = subwin(stdscr, 11   , 26, (LINES / 2) - (15 / 2) + 2, (COLS / 2) - (19 / 2));
    box(_w_scoreboard, ACS_VLINE, ACS_HLINE);
    mvwprintw(_w_scoreboard, 2, 8, "SCOREBOARD");

    for (int x = 0 ; x < scores.size() ; x++) {
        mvwprintw(_w_scoreboard, scbH+1, 3, scores.at(x).first.c_str());
        mvwprintw(_w_scoreboard, scbH+1, 20, std::to_string(scores.at(x).second).c_str());
        scbH++;
    }

    this->buildMenu(libs, playerName);
    this->printMenu(libs, select);

    switch (input) {
        case DOWN_KEY:
            if ((select + 1) < _menu.size()) {
                select++;
                if ((select + 1) < _menu.size() && _menu.at(select).n == 0)
                    select++;
            }
            break;
        case UP_KEY:
            if (select > 0 && (select - 1 ) != 0) {
                select--;
                if ((select - 1) < _menu.size() && _menu.at(select).n == 0)
                    select--;
            }
            break;
        case ENTER_KEY:
            if (strcmp(_menu.at(select).lib.name, "ncurses") == 0)
                return NC_KEY;
            if (strcmp(_menu.at(select).lib.name, "sfml") == 0)
                return SF_KEY;
            if (strcmp(_menu.at(select).lib.name, "pacman") == 0)
                return PCM_KEY;
            if (strcmp(_menu.at(select).lib.name, "nibbler") == 0)
                return NBL_KEY;
            if (_menu.at(select).lib.type == PSEUDO) {
                _menu.at(select).text = this->getNewPlayerName(_menu.at(select).text, playerName);
                return NIL_KEY;
            }
            break;
    default:
        break;
    }
    // this->printMenu(libs, select);

    refresh();
    wrefresh(_w_main);
    return input;
}

char *Ncurses::getNewPlayerName(char *currentName, std::string &playerName)
{
    char input[255];
    wmove(_w_menu, 4, 5);
    mvwprintw(_w_menu, 4, 5, BLANK_INPUT);
    wmove(_w_menu, 4, 5);
    wgetstr(_w_menu, input);
    wrefresh(_w_menu);
    playerName = std::string(input);
    return strdup(input);
}

int Ncurses::buildMenu(LibCollection libs, std::string playerName)
{
    entry_t newEntry;
    _menu.clear();

    newEntry.text = (char*) playerName.c_str();
    newEntry.lib = libs.at(libs.size() - 1);
    newEntry.n = 3;
    _menu.push_back(newEntry);
    newEntry.text = (char*)"Games:";
    newEntry.n = 0;
    _menu.push_back(newEntry);
    for (int x = 0 ; x < libs.size() ; x++) {
        if (libs.at(x).type == GAME) {
            newEntry.text = libs.at(x).name;
            newEntry.n = 1;
            newEntry.lib = libs.at(x);
            _menu.push_back(newEntry);
        }
    }
    newEntry.text = (char*)"Graphics:";
    newEntry.n = 0;
    _menu.push_back(newEntry);
    for (int x = 0 ; x < libs.size() ; x++) {
        if (libs.at(x).type == GRAPHIC) {
            newEntry.text = libs.at(x).name;
            newEntry.n = 2;
            newEntry.lib = libs.at(x);
            _menu.push_back(newEntry);
        }
    }
    return (0);
}

int Ncurses::printMenu(LibCollection libs, int select)
{
    int p = 3;

    for (int x = 0 ; x < _menu.size() ; x++) {
        if (x == select)
            wattron(_w_menu, COLOR_PAIR(MENU_SELECT));
        if (_menu.at(x).n == 0)
            wattron(_w_menu, COLOR_PAIR(MENU_HEADER));
        mvwprintw(_w_menu, p+1, 5, _menu.at(x).text);
        wattroff(_w_menu, COLOR_PAIR(MENU_SELECT));
        wattroff(_w_menu, COLOR_PAIR(MENU_HEADER));
        p++;
    }
    return (0);
}

void Ncurses::endGame(std::string text, int score)
{
    int h = (LINES / 2) - 1;
    int w = (COLS / 2) - (text.size() / 2);
    std::string tips = "Press escape to return at menu";
    char yourScore[255];

    sprintf(yourScore, "Score: %d", score);
    wclear(_w_main);
    wattron(_w_main, A_BOLD);
    mvwprintw(_w_main, h, w, text.c_str());
    wattroff(_w_main, A_BOLD);
    w = (COLS / 2) - (tips.size() / 2);
    mvwprintw(_w_main, h+1, w, tips.c_str());
    mvwprintw(_w_main, h-1, w, yourScore);
    wrefresh(_w_main);
}

} /* end namespace */

extern "C" {

    IGraphicsModule *getInstance(void)
    {
        IGraphicsModule *instance = new Ncurses::Ncurses();
        return instance;
    }

    void deleteInstance(IGraphicsModule *instance)
    {
        delete instance;
    }

}