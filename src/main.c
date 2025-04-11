#include "arcfour.h"

/* test only */

int main(int argc, char *argv[]) {
    unsigned char *plaintext = argv[1]; 
    unsigned char *key = argv[2];

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

    /* encrypt */
    encrypt(plaintext_size, &cipher[0], &keystream[0], &plaintext[0]);

    /* decrypt */
    decrypt(plaintext_size, &cipher[0], &keystream[0], &deciphered[0]);


    free(s_);

    return 0;
}