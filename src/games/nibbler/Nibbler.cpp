/*
** EPITECH PROJECT, 2021
** # Nibbler.cpp
** File description:
** Created 26/03/2021 11:45:12
*/

#include "Nibbler.hpp"
#include "Logger.hpp"

Nibbler::Nibbler(void)
    : _name("nibbler"), _lastInput(UP_KEY), _status(RUN), _score(0)
{}

Nibbler::~Nibbler(void)
{}

std::string Nibbler::getName(void) const
{
    return _name;
}

enum Status Nibbler::getStatus(void) const
{
    return _status;
}

void Nibbler::init(void)
{
    _s_player.push_back(this->getPlayerPos());
    this->createBonus();
}

bool Nibbler::keyInput(Keys key)
{
    Keys k = key;
    pos_t tmp;
    char playerType = '<';

    tmp.x = _s_player.at(0)->x;
    tmp.y = _s_player.at(0)->y;

    if (_score == 3170)
        _status = WIN;

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

    if (_mapMetaData.at(tmp.x).at(tmp.y) == WALL ||
        _mapMetaData.at(tmp.x).at(tmp.y) == IWALL ||
        _mapMetaData.at(tmp.x).at(tmp.y) == PLAYER) {
        _status = LOOSE;
    }

    if (_mapMetaData.at(tmp.x).at(tmp.y) == PATH ||
        _mapMetaData.at(tmp.x).at(tmp.y) == BONUS) {
            if (_mapMetaData.at(tmp.x).at(tmp.y) == BONUS) {
                _score += 100;
                this->createBonus();
                this->playerAddNode(tmp);
            }

            this->movePlayer(tmp);
            if (key != NIL_KEY)
                _lastInput = key;
            return true;
    }
    return false;
}

void Nibbler::playerAddNode(pos_t next)
{
    pos_t *newPos = (pos_t*)malloc(sizeof(pos_t));
    newPos->x = next.x;
    newPos->y = next.y;
    _s_player.push_front(newPos);
}

void Nibbler::movePlayer(pos_t next)
{
    int t = 0;
    pos_t *newPos = (pos_t*)malloc(sizeof(pos_t));
    newPos->x = next.x;
    newPos->y = next.y;

    for (int x = 0 ; x < _s_player.size() ; x++)
        _mapMetaData.at(_s_player.at(x)->x).at(_s_player.at(x)->y) = PATH;
    _s_player.push_front(newPos);
    _s_player.pop_back();
    for (int x = 0 ; x < _s_player.size() ; x++) {
        _mapMetaData.at(_s_player.at(x)->x).at(_s_player.at(x)->y) = PLAYER;
         _map.at(_s_player.at(x)->x).at(_s_player.at(x)->y) = 'O';
    }
}

void Nibbler::createBonus(void)
{
    int randx = rand() % 9 + 4;
    int randy = rand() % 47 + 4;

    if (randx < _mapMetaData.size() && randy < _mapMetaData.at(randx).size() &&
        _mapMetaData.at(randx).at(randy) != PLAYER &&
        _mapMetaData.at(randx).at(randy) != WALL &&
        _mapMetaData.at(randx).at(randy) != IWALL) {
        _s_bonus.x = randx;
        _s_bonus.y = randy;
        _mapMetaData.at(_s_bonus.x).at(_s_bonus.y) = BONUS;
    } else {
        this->createBonus();
    }
}

int Nibbler::getScore(void) const
{
    return _score;
}

MapContainer Nibbler::getMap(char *filename)
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

MapMetadata Nibbler::getMetaOf(char c)
{
    MapMetadata ret = NIL;

    switch (c) {
        case ' ':
            ret = PATH;
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
        case ':':
            ret = IWALL;
            break;
        case '*':
            ret = BONUS;
            break;
        default:
            break;
    }
    return ret;
}

void Nibbler::buildMetaData(void)
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

pos_t *Nibbler::getMapSize(FILE *file)
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

MapContainer Nibbler::getUpdatedMap(void)
{
    return _map;
}

MetaContainer Nibbler::getMetaMap(void)
{
    return _mapMetaData;
}

pos_t *Nibbler::getPlayerPos(void)
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

/*!
** @brief Check validity of nibbler map extension
** @author GOUEREC Pierrick (pierrick.gouerec@epitech.eu)
**
** @param filename
** @param file
**
** @return true
** @return false
*/
bool Nibbler::checkMapFileValidity(char *filename, FILE *file)
{
    if (file == NULL) {
        std::cerr << "failed to open '" << strrchr(filename, '/') + 1 << "'" << std::endl;
        return false;
    }
    if (strcmp(strrchr(filename, '.'), ".nbl") != 0) {
        std::cerr << "file extension is incorrect '" << strrchr(filename, '/') + 1 << "'" << std::endl;
        return false;
    }
    return true;
}

extern "C" {

    IGamesModule *getInstance(void)
    {
        IGamesModule *instance = new Nibbler();
        return instance;
    }

    void deleteInstance(IGamesModule *instance)
    {
        delete instance;
    }

}