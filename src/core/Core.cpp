/*
** EPITECH PROJECT, 2021
** # Core.cpp
** File description:
** Created 06/04/2021 10:51:35
*/

#include "Core.hpp"
#include "Logger.hpp"

namespace Arcade {

    Core::Core(int ac, char **av)
    :   _graphicLib(NULL), _gameLib(NULL), _graphicPtr(NULL), _gamePtr(NULL),
        _playerName("Player"), _score(0)
    {
        Log("New Core", 0);
        if (ac < 2) {
            this->usage();
            exit(84);
        }

        _graphicPtr = new DLLoader<IGraphicsModule>(av[1]);
        _graphicLib = _graphicPtr->getInstance();

        this->menu();
    }

    Core::~Core(void)
    {
        _graphicPtr->destroyInstance();
        if (_gamePtr != NULL)
            _gamePtr->destroyInstance();
        delete _gamePtr;
        delete _graphicPtr;
        Log("Core destroyed", 0);
    }

    int Core::menu(void)
    {
        Keys input = NIL_KEY;

        Log("load libraries from 'lib/'", 0);
        this->loadLibsFromFolder();
        Log("Start menu loop", 0);
        while (input != MENU_KEY) {
            input = _graphicLib->viewMenu(_libraries, _playerName);
            std::this_thread::sleep_for(std::chrono::milliseconds(75));
            switch (input) {
                case PCM_KEY:
                    Log("Start Pacman", 0);
                    if (startGame("lib/arcade_pacman.so", "mapping/map.pcm") != 0)
                        return (-1);
                    break;
                case NBL_KEY:
                    Log("Start Pacman", 0);
                    if (startGame("lib/arcade_nibbler.so", "mapping/map.nbl") != 0)
                        return (-1);
                    break;
                case NC_KEY:
                    Log("Change graphic for ncurses", 0);
                    changeGraphics("lib/arcade_ncurses.so");
                    break;
                case SF_KEY:
                    Log("Change graphic for sfml", 0);
                    changeGraphics("lib/arcade_sfml.so");
                    break;
                default:
                    break;
            }
        }
        return (0);
    }

    int Core::gameloop(const  char *filemap)
    {
        MapContainer map = _gameLib->getMap((char*) filemap);
        Keys input = NIL_KEY;
        if (map.empty() == 1)
            return (-1);
        _gameLib->init();
        _graphicLib->loadMap(map, _gameLib->getMetaMap());
        while (input != MENU_KEY) {
            input = _graphicLib->keyPressed();
            _gameLib->keyInput(input);
            _graphicLib->refreshMap(_gameLib->getUpdatedMap(), _gameLib->getMetaMap());
            _score = _gameLib->getScore();
            _graphicLib->updateScore(_score);
            if (this->checkGameStatus() != 0)
                return (0);
            std::this_thread::sleep_for(std::chrono::milliseconds(75));
            if (input == EXIT_KEY) {
                return (-1);
            }

            if (input == NEXTLIB_KEY) {
                changeGraphics("lib/arcade_ncurses.so");
            } else if (input == PREVLIB_KEY) {
                changeGraphics("lib/arcade_sfml.so");
            }

        }
        return (0);
    }

    int Core::checkGameStatus(void)
    {
        Keys input;

        if (_gameLib->getStatus() == WIN) {
            _graphicLib->endGame("You Win !");
            while (input != MENU_KEY) {
                input = _graphicLib->keyPressed();
            };
            return (-1);
        }
        if (_gameLib->getStatus() == LOOSE) {
            _graphicLib->endGame("Game Over :(");
            while (input != MENU_KEY) {
                input = _graphicLib->keyPressed();
            };
            return (-1);
        }
        return (0);
    }

    void Core::loadLibsFromFolder(void)
    {
        DIR *dir = opendir("lib/");
        char path[255] = "lib/";
        struct dirent *dirs;
        lib_t  newlib;
        int x;

        if (dir == NULL) {
            fprintf(stderr, "Can't open folder '%s'.", "lib/");
            return;
        }
        while ((dirs = readdir(dir)) != NULL) {
            if (dirs->d_type != DT_DIR && dirs->d_name[0] != '.') {
                newlib.name = strrchr(strdup(dirs->d_name), '_') + 1;
                for (x = 0 ; newlib.name[x] != '.' ; x++);
                newlib.name[x] = '\0';
                newlib.origin_name = strcat(path, dirs->d_name);
                if (strcmp(newlib.name, "pacman") == 0 || strcmp(newlib.name, "nibbler") == 0)
                    newlib.type = GAME;
                else
                    newlib.type = GRAPHIC;
                if (strcmp(newlib.name, "sdl2") == 0)
                    newlib.type = UNKNOWN;
                _libraries.push_back(newlib);
            }
        }
        closedir(dir);

        newlib.name = strdup("Player");
        newlib.type = PSEUDO;
        _libraries.push_back(newlib);
    }

    int Core::startGame(const char *gameLib, const char *gameMap)
    {
        if (_gamePtr != NULL)
            _gamePtr->destroyInstance();
        _gamePtr = new DLLoader<IGamesModule>(gameLib);
        _gameLib = _gamePtr->getInstance();
        return this->gameloop(gameMap);
    }

    int Core::changeGraphics(const char *graphicLib)
    {
        if (_graphicPtr != NULL)
            _graphicPtr->destroyInstance();
        _graphicPtr = new DLLoader<IGraphicsModule>(graphicLib);
        _graphicLib = _graphicPtr->getInstance();
        return (0);
    }

    void Core::usage(void)
    {
        printf("./arcade <graphic library>\n");
    }

}