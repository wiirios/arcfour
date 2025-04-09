#ifndef ARCFOUR_H
#define ARCFOUR_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 256

struct s_arcfour
{
    unsigned char s[MAX];
    char *key;
    size_t key_size;

};

struct s_arcfour* create_arc(unsigned char *s, char *key, size_t key_size);
void arcfour_ksa(unsigned char *s, char *key, size_t key_size);
void arcfour_prga(unsigned char *s, size_t key_size, unsigned char *keystream, size_t secret_size);

int fatal(char *msg);

#define isempty(x) (strlen(x) == 0)

#endif