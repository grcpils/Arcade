/*
** EPITECH PROJECT, 2021
** # foo.c
** File description:
** Created 10/03/2021 09:53:32
*/

void __attribute__((constructor)) init_foo(void);
void __attribute__((destructor)) close_foo(void);

#include <stdio.h>

void init_foo(void)
{
    printf("[libfoo.so] Load FOO\n");
}

void foo(void)
{
    printf("[libfoo.so] EntryPoint FOO\n");
}

void close_foo(void)
{
    printf("[libfoo.so] Unload FOO\n");
}