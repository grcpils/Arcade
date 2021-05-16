/*
** EPITECH PROJECT, 2021
** # Scoreboard.cpp
** File description:
** Created 16/05/2021 10:01:06
*/

#include "Scoreboard.hpp"

namespace Arcade
{

    Scoreboard::Scoreboard()
    :   _scoreFilename(NULL)
    {
        Log("Init scoreboard", 0);
    }

    Scoreboard::~Scoreboard(void)
    {
        Log("Insert scores in file", 0);
        this->insertInFile();
        Log("Destroy Scoreboard", 0);
    }

    bool Scoreboard::setFile(char *filename)
    {
        _scoreFilename = filename;
        this->extractFromFile();
    }

    bool Scoreboard::extractFromFile(void)
    {
        std::ifstream scoreFile(_scoreFilename);
        std::string line;

        std::string limit = ":";
        std::string token;
        size_t next = 0;

        std::string playername;
        int score;

        if (!scoreFile.is_open()) {
            std::cerr << "Error on score file openning" << std::endl;
            return false;
        } else {
            while(getline(scoreFile, line)) {
                next = line.find(limit);
                token = line.substr(0, next);
                playername = token;
                line.erase(0, next + limit.length());
                score = stoi(line);
                _scores.push_back(std::pair<std::string, int>(playername, score));
            }
            scoreFile.close();
        }

    }

    bool Scoreboard::insertInFile(void)
    {
        std::ofstream scoreFile(_scoreFilename, std::ios::trunc);

        for (int x = 0 ; x < _scores.size() ; x++) {
            scoreFile << _scores.at(x).first << ":" << _scores.at(x).second << std::endl;
        }
    }

    bool comparator(std::pair<std::string, int> &a, std::pair<std::string, int> &b)
    {
        return a.second > b.second;
    }

    bool Scoreboard::sort(void)
    {
        std::sort(_scores.begin(), _scores.end(), comparator);
    }

    int Scoreboard::findLowest(int current)
    {
        for (int x = 0 ; x < _scores.size() ; x++) {
            if (_scores.at(x).second < current)
                return x;
            if (x >= 5)
                return 4;
        }
        return -1;
    }

    bool Scoreboard::add(std::string playerName, int playerScore)
    {
        int lowest = this->findLowest(playerScore);

        if (_scoreFilename == NULL) {
            Log("Scoreboard: File not set: Use setFile() before", 0);
        }
        this->sort();

        if (_scores.size() < 5) {
            _scores.push_back(std::pair<std::string, int>(playerName, playerScore));
            return true;
        }
        if (lowest > 0 && _scores.size() == 5)
            _scores.at(lowest) = std::pair<std::string, int>(playerName, playerScore);
        return true;
    }

    std::vector<std::pair<std::string, int>> Scoreboard::get(void)
    {
        this->sort();
        Log("Size of scores: %d", _scores.size());
        return _scores;
    }

} /* namespace Arcade */