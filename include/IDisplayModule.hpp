#pragma once

#include <ostream>
#include <string>

class IDisplayModule
{
    public:
        virtual ~IDisplayModule(void) = default;

        virtual void init(void) = 0;
        virtual void stop(void) = 0;
        virtual const std::string &getName(void) const = 0;
};