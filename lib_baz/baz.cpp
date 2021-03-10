/*
** EPITECH PROJECT, 2021
** # baz.c
** File description:
** Created 10/03/2021 09:53:28
*/

void __attribute__((constructor)) init_baz(void);
void __attribute__((destructor)) close_baz(void);

#include <stdio.h>

void init_baz(void)
{
    printf("[libbaz.so] Load BAZ\n");
}

void baz(void)
{
    printf("[libbaz.so] EntryPoint BAZ\n");
}

void close_baz(void)
{
    printf("[libbaz.so] Unload BAZ\n");
}