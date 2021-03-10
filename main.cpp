/*
** EPITECH PROJECT, 2021
** # main.c
** File description:
** Created 10/03/2021 09:30:37
*/

#include "IDisplayModule.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string>

int main(void)
{
    void *handle_bar;
    IDisplayModule *instance;
    IDisplayModule *(*getInstance)(void);
    void (*deleteInstance)(IDisplayModule*);

    char *error;

    printf("[main.c] Init Bootstrap\n");

    handle_bar = dlopen("lib/libbar.so", RTLD_LAZY);
    if (!handle_bar) {
        fprintf(stderr, "%s\n", dlerror());
        exit(-1);
    }

    *(void **) (&getInstance) = dlsym(handle_bar, "getInstance");
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    *(void **) (&deleteInstance) = dlsym(handle_bar, "deleteInstance");
    if ((error = dlerror()) != NULL)  {
        fprintf(stderr, "%s\n", error);
        exit(EXIT_FAILURE);
    }

    instance = (*getInstance)();
    instance->init();
    std::cout << instance->getName() << std::endl;
    instance->stop();
    (*deleteInstance)(instance);

    dlclose(handle_bar);

    return (0);
}