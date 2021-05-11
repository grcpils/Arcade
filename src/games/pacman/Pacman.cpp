/*
** EPITECH PROJECT, 2021
** # Pacman.cpp
** File description:
** Created 26/03/2021 11:46:32
*/

#include "Pacman.hpp"

Pacman::Pacman(void)
    : _name("pacman"), _lastInput(RIGHT_KEY), _status(RUN), _score(0)
{}

Pacman::~Pacman(void)
{
    free(_mapSize);
    free(_s_player);
}

std::string Pacman::getName(void) const
{
    return (_name);
}

enum Status Pacman::getStatus(void) const
{
    return _status;
}

void Pacman::init(void)
{
    _s_player = this->getPlayerPos();
}

bool Pacman::keyInput(Keys key)
{
    Keys k = key;
    pos_t tmp;
    char playerType = '<';

    tmp.x = _s_player->x;
    tmp.y = _s_player->y;

    if (key == NIL_KEY)
        k = _lastInput;

    switch (k) {
        case RIGHT_KEY:
            tmp.y++;
            playerType = '<';
            break;
        case LEFT_KEY:
            tmp.y--;
            playerType = '>';
            break;
        case UP_KEY:
            tmp.x--;
            playerType = 'v';
            break;
        case DOWN_KEY:
            tmp.x++;
            playerType = '^';
            break;
        default:
            return false;
            break;
    }

    if (_mapMetaData.at(tmp.x).at(tmp.y) == PPATH ||
        _mapMetaData.at(tmp.x).at(tmp.y) == PATH ||
        _mapMetaData.at(tmp.x).at(tmp.y) == MONSTER ||
        _mapMetaData.at(tmp.x).at(tmp.y) == BONUS ||
        _mapMetaData.at(tmp.x).at(tmp.y) == PLAYER) {
            if (_map.at(tmp.x).at(tmp.y) == '.')
                _score += 10;
            if (_map.at(tmp.x).at(tmp.y) == '*')
                _score += 100;

            _map.at(_s_player->x).at(_s_player->y) = ' ';
            _mapMetaData.at(_s_player->x).at(_s_player->y) = PATH;
            _s_player->x = tmp.x;
            _s_player->y = tmp.y;
            _map.at(_s_player->x).at(_s_player->y) = playerType;
            _mapMetaData.at(_s_player->x).at(_s_player->y) = PLAYER;
            if (key != NIL_KEY)
                _lastInput = key;
            return true;
    }
    return false;
}

int Pacman::getScore(void) const
{
    return _score;
}

std::vector<std::vector<char>> Pacman::getMap(char *filename)
{
    std::vector<char> vline;
    FILE *map_file = fopen(filename, "r");
    char line[255];
    int i = 0;

    if (map_file == NULL) {
        fprintf(stderr, "Can't open file: %s\n", filename);
        return _map;
    }
    if (this->checkMapFileValidity(filename, map_file) == false)
        return _map;
    _mapSize = this->getMapSize(map_file);
    while (fgets(line, 255, map_file)) {
        for (int x = 0 ; line[x] != '\0' ; x++) {
            vline.push_back(line[x]);
        }
        _map.push_back(vline);
        vline.clear();
    }
    fclose(map_file);
    this->buildMetaData();
    return _map;
}

MapContainer Pacman::getUpdatedMap(void)
{
    return _map;
}

MetaContainer Pacman::getMetaMap(void)
{
    return _mapMetaData;
}

MapMetadata Pacman::getMetaOf(char c)
{
    MapMetadata ret = NIL;

    switch (c) {
        case '.':
            ret = PPATH;
            break;
        case '<':
        case '>':
        case 'v':
        case '^':
            ret = PLAYER;
            break;
        case '#':
            ret = WALL;
            break;
        case ' ':
            ret = IWALL;
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

void Pacman::buildMetaData(void)
{
    std::vector<MapMetadata> meta(_mapSize->y, NIL);
    std::vector<std::vector<MapMetadata>> metaData(_mapSize->x, meta);

    for (int x = 0 ; x < _map.size() ; x++) {
        for (int y = 0 ; y < _map.at(x).size() ; y++) {
            metaData.at(x).at(y) = this->getMetaOf(_map.at(x).at(y));
        }
    }
    _mapMetaData = metaData;
}

pos_t *Pacman::getPlayerPos(void)
{
    pos_t *pos = (pos_t*) malloc(sizeof(pos_t));

    for (int x = 0 ; x < _map.size() ; x++) {
        for (int y = 0 ; y < _map.at(x).size() ; y++) {
            if (_map.at(x).at(y) == '<') {
                pos->x = x;
                pos->y = y;
            }
        }
    }
    return pos;
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
pos_t *Pacman::getMapSize(FILE *file)
{
    pos_t *size = (pos_t*) malloc(sizeof(pos_t));
    char chr;

    size->x = 0;
    size->y = 0;
    while ((chr = fgetc(file)) != EOF) {
        if (chr == '\n')
            size->x++;
        if (chr != '\n' && size->x == 0)
            size->y++;
    }
    size->x++;
    size->y++;
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