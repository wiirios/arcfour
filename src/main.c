#include "arcfour.h"

int main(int argc, char *argv[]) {
    unsigned char *key = argv[1];
    unsigned char plaintext[] = "Plaintext"; 

    size_t key_size = strlen(key);
    size_t plaintext_size = strlen(plaintext);

    unsigned char s[MAX];
    unsigned char keystream[plaintext_size];
    unsigned char cipher[plaintext_size];
    unsigned char deciphered[plaintext_size + 1];

    struct s_arcfour* s_ = create_arc(s, key, key_size);

    /* generate keystream */
    arcfour_ksa(s_->s, s_->key, s_->key_size);
    arcfour_prga(s_->s, s_->key_size, &keystream[0], plaintext_size);
    
    for (int i = 0; i < plaintext_size; i++) {
        cipher[i] = plaintext[i] ^ keystream[i];
    }

    for (int i = 0; i < plaintext_size; i++) {
        deciphered[i] = cipher[i] ^ keystream[i];
    }
    
    free(s_);

    return 0;
}