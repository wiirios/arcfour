#include "arcfour.h"

int fatal(char *msg) {
    printf("Error: %s", msg);
    exit(EXIT_FAILURE);
}

struct s_arcfour* create_arc(unsigned char *s, char *key, size_t key_size) {
    struct s_arcfour* s_ = (struct s_arcfour*) malloc(sizeof(struct s_arcfour));

    if (s_ != NULL) {
        memcpy(s_->s, s, MAX);
        s_->key = key;
        s_->key_size = key_size;
    }

    return s_;
}

void arcfour_ksa(unsigned char *s, char *key, size_t key_size) {
    unsigned char temp;
    int i = 0;
    int j = 0;

    for (; i < MAX; i++) s[i] = i;

    /* Scrambling */
    for (i = 0; i < MAX; i++) {
        j = (j + s[i] + key[i % key_size]) % 256;

        temp = s[i];
        s[i] = s[j];
        s[j] = temp;
    }

}

void arcfour_prga(unsigned char *s, size_t key_size, unsigned char *keystream, size_t secret_size) {
    unsigned char temp;
    int i = 0;
    int j = 0;
    int n = 0;
    
    for (; n < secret_size; n++) {
        j = (j + 1) % 256;
        j = (j + s[i]) % 256;

        temp = s[i];
        s[i] = s[j];
        s[j] = temp;

       int pseudbyte = (s[i] + s[j]) % 256;
       keystream[i] = s[pseudbyte];
    }
}