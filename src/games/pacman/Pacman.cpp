/*
** EPITECH PROJECT, 2021
** # Pacman.cpp
** File description:
** Created 26/03/2021 11:46:32
*/

#include "Pacman.hpp"

Pacman::Pacman(void)
    : _name("pacman")
{}

Pacman::~Pacman(void)
{}

std::string Pacman::getName(void) const
{
    return (_name);
}

enum Status Pacman::getStatus(void) const
{}

void Pacman::init(void)
{}

bool Pacman::keyInput(void)
{}

char **Pacman::getMap(char *filename)
{
    FILE *map_file = fopen(filename, "r");
    int *mapSize;
    char **map;
    char line[255];
    int i = 0;

    if (this->checkMapFileValidity(filename, map_file) == false)
        return NULL;
    mapSize = this->getMapSize(map_file);
    map = (char**) malloc(sizeof(char*) * (mapSize[0] + 1));
    while (fgets(line, 255, map_file)) {
        map[i] = strdup(line);
        i++;
    }
    map[i] = NULL;
    fclose(map_file);
    return map;
}

MapMetadata Pacman::getMetaOf(char c)
{
    MapMetadata ret = NIL;

    switch (c) {
        case '.':
            ret = PATH;
            break;
        case '#':
        case ' ':
            ret = WALL;
            break;
        case '<':
        case '>':
        case '^':
        case 'v':
            ret = PLAYER;
            break;
        case 'M':
            ret = MONSTER;
            break;
        case '*':
            ret = BONUS;
            break;
        default:
            break;
    }
    return ret;
}

/*
** @brief check validity of file content and file extension
**
** @param filename
** @param file
** @return true if file is ok | false if an error occured
*/
bool Pacman::checkMapFileValidity(char *filename, FILE *file)
{
    if (file == NULL) {
        std::cerr << "failed to open '" << strrchr(filename, '/') + 1 << "'" << std::endl;
        return false;
    }
    if (strcmp(strrchr(filename, '.'), ".pcm") != 0) {
        std::cerr << "file extension is incorrect '" << strrchr(filename, '/') + 1 << "'" << std::endl;
        return false;
    }
    return true;
}

/*
** @brief get height and width of the map - file pointer is reset after return
**
** @param file
** @return int** - [0] = height | [1] = width
*/
int *Pacman::getMapSize(FILE *file)
{
    int *size = (int*) malloc(sizeof(int) * 3);
    char chr;

    size[0] = 0;
    size[1] = 0;
    while ((chr = fgetc(file)) != EOF) {
        if (chr == '\n')
            size[0]++;
        if (chr != '\n' && size[0] == 0)
            size[1]++;
    }
    size[0]++;
    size[1]++;
    rewind(file);
    return size;
}

extern "C" {

    IGamesModule *getInstance(void)
    {
        IGamesModule *instance = new Pacman();
        return instance;
    }

    void deleteInstance(IGamesModule *instance)
    {
        delete instance;
    }

}