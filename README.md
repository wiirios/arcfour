# Arcfour
This repository contains my own implementation of the [ARCFOUR](https://en.wikipedia.org/wiki/RC4) (RC4) stream cipher, developed entirely in C. The project aims to provide a clear and concise representation of the algorithm's internal mechanics, including its Key Scheduling Algorithm (KSA) and Pseudo-Random Generation Algorithm (PRGA). This implementation is intended for study, experimentation, and a deeper understanding of symmetric key encryption techniques.

## Getting Started

1. clone this repository
``` sh
git clone https://github.com/wiirios/arcfour.git
```

2. compile using cmake
``` sh
mkdir build
cd build
cmake ..
cmake --build .
```

or
``` sh
cmake .. -G "MinGW Makefiles"
cmake --build .
```

## Hot to use it?

### Command-Line Arguments
Run the compiled binary from the terminal:

```sh
arcfour.exe "your secret message OR file path" "your encryption key" "boolean value to indicate whether there will be a file read"
```
- argv[1]: The message you want to encrypt.
- argv[2]: The key used for encryption/decryption.
- argv[3]: True OR False if `argv[1]` is a file path

## Using It in Your Project
To use the algorithm in your own C project:

1. Copy the files arcfour.c and arcfour.h into your project directory.
2. Include the header in your source code:

``` c
#include "arcfour.h"
```

here is an example

``` c

// The message to be encrypted
unsigned char *plaintext = (unsigned char *)argv[1];
   
// The key used for encryption and decryption
unsigned char *key = (unsigned char *)argv[2];

// Length of the key
size_t key_size = strlen((char *)key);
    
// Length of the plaintext
size_t plaintext_size = strlen((char *)plaintext);

// State vector for the RC4 algorithm (256 bytes)
unsigned char s[MAX];
    
// Buffer to store the generated keystream
unsigned char keystream[plaintext_size];
    
// Buffer to store the encrypted text
unsigned char cipher[plaintext_size];
    
// Buffer to store the decrypted text (+1 for null terminator)
unsigned char deciphered[plaintext_size + 1];

// Create and initialize the RC4 state structure
struct s_arcfour* s_ = create_arc(s, key, key_size);

// Step 1: Initialize the state vector using the key
arcfour_ksa(s_->s, s_->key, s_->key_size);
    
// Step 2: Generate the keystream
arcfour_prga(s_->s, s_->key_size, keystream, plaintext_size);

// Step 3: Encrypt the plaintext using the keystream
encrypt(plaintext_size, cipher, keystream, plaintext);

// Step 4: Decrypt the ciphertext using the same keystream
decrypt(plaintext_size, cipher, keystream, deciphered);
deciphered[plaintext_size] = '\0'; // Add null terminator

// Free allocated memory
free(s_);
```
## Reading Plaintext from a File

In addition to passing a plaintext message directly via the command line, you can also instruct the program to read the plaintext from a text file. This is useful when working with larger messages or secret files.

``` c
arcfour.exe "path/to/message.txt" "your encryption key" true
```
> [!WARNING]
> The third argument must be the string "true", or the file input will not be used.

``` c
arcfour.exe "texts/secret.txt" "MySecretKey123" true
```

### Step-by-step Implementation

1. Update `main` to accept a third argument
Modify your main function to read a third argument that indicates whether the input is a file:

``` c
int main(int argc, char *argv[]) {
    unsigned char *plaintext; // do not initialize the variable yet!
    unsigned char *key = argv[2];
    char *isFile = argv[3]; // "true" if reading from file

    size_t key_size = strlen(key);
    size_t plaintext_size = 0;
    ...
}
```
2. Read from the file

``` c
if (strcmp(isFile, "true") == 0) {
        FILE *file = fopen(argv[1], "r");
        
        if (file == NULL) fatal("failed to open file");

        /* obtain file size */
        fseek(file, 0, SEEK_END);
        plaintext_size = ftell(file);
        rewind(file);

        plaintext = malloc(plaintext_size + 1);
        if (plaintext == NULL) fatal("allocating memory");

        fread(plaintext, 1, plaintext_size, file);
        fclose(file); // close the file
    } else {
        plaintext = argv[1];
        plaintext_size = strlen(plaintext);
    }
```

and don't forget to free up memory at the end

``` c
if (strcmp(isFile, "true") == 0) free(plaintext);
```

### struct s_arcfour Explained
The s_arcfour structure is used to store the internal state of the RC4 algorithm and the key data. Here's the definition:
``` c
struct s_arcfour {
    unsigned char s[MAX]; // The internal state array (usually 256 bytes)
    char *key;            // Pointer to the key used for encryption/decryption
    size_t key_size;      // Length of the key
};
```

Fields:
- `s[MAX]`:
This is the state array used by the RC4 algorithm. It contains a permutation of all 256 possible byte values (0–255). The algorithm constantly modifies this array during the Key Scheduling Algorithm (KSA) and the Pseudo-Random Generation Algorithm (PRGA).

- `key`:
A pointer to the character array (string) that represents the encryption key. The same key must be used for both encryption and decryption since RC4 is a symmetric cipher.

- `key_size`:
The length of the key. It's important to know this so the algorithm can loop over the correct number of bytes when initializing the state.

## MIT License
This project is licensed under MIT license, read more at <span><a href="https://docs.github.com/pt/repositories/managing-your-repositorys-settings-and-features/customizing-your-repository/licensing-a-repository">docs.github</span>