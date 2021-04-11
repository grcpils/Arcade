/*
** EPITECH PROJECT, 2021
** # DLLoader.hpp
** File description:
** Created 25/03/2021 15:00:21
*/

#ifndef DLLOADER_HPP
#define DLLOADER_HPP

#include <string>
#include <iostream>
#include <dlfcn.h>
#include <cstring>
#include "Logger.hpp"

template<typename T>
class DLLoader
{
    public:
        DLLoader<T>(std::string filename)
        : _filename(filename.c_str())
        {
            T *(*getInstance)(void);

            _handle = dlopen(_filename, RTLD_LAZY);
            if (!_handle) {
                fprintf(stderr, "%s\n", dlerror());
                exit(-1);
            }
            *(void **) (&getInstance) = dlsym(_handle, "getInstance");
            if ((_error = dlerror()) != NULL)  {
                fprintf(stderr, "%s\n", _error);
                exit(EXIT_FAILURE);
            }
            _instance = (*getInstance)();
        }

        ~DLLoader(void)
        {}

        T *getInstance(void) const
        {
            return _instance;
        }

        void destroyInstance()
        {
            void (*deleteInstance)(T*);

            *(void **) (&deleteInstance) = dlsym(_handle, "deleteInstance");
            if ((_error = dlerror()) != NULL)  {
                fprintf(stderr, "%s\n", _error);
                exit(EXIT_FAILURE);
            }
            (*deleteInstance)(_instance);
        }

    private:
        const char *_filename;
        char *_error;
        void *_handle;
        T *_instance;
};

#endif