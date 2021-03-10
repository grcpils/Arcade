/*
** EPITECH PROJECT, 2021
** # bar.c
** File description:
** Created 10/03/2021 09:53:19
*/

// void __attribute__((constructor)) init_bar(void);
// void __attribute__((destructor)) close_bar(void);

#include "IDisplayModule.hpp"
#include <iostream>
#include <stdio.h>

class BarDisplayModule : public IDisplayModule
{
    public:
        BarDisplayModule(void);
        ~BarDisplayModule(void);

        void init(void);
        void stop(void);
        const std::string &getName(void) const;
    private:
        std::string _name;
        void log(std::string msg);
};

BarDisplayModule::BarDisplayModule(void)
    : _name("libbar.so")
{
    this->log("library created");
}

BarDisplayModule::~BarDisplayModule(void)
{
    this->log("library destroyed");
}

void BarDisplayModule::init(void)
{
    this->log("library loaded");
}

void BarDisplayModule::stop(void)
{
    this->log("library closed");
}

const std::string &BarDisplayModule::getName(void) const
{
    return (_name);
}

void BarDisplayModule::log(std::string msg)
{
    std::cout << "[" << _name << "] " << msg << std::endl;
}

extern "C"
{
    IDisplayModule *getInstance(void)
    {
        IDisplayModule *instance = new BarDisplayModule();
        return instance;
    }

    void deleteInstance(IDisplayModule *instance)
    {
        delete instance;
    }
}