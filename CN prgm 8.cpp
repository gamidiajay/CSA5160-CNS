#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
void generateCipherAlphabet(char keyword[], char cipherAlphabet[]) {
    int used[ALPHABET_SIZE] = {0};
    int klen = strlen(keyword);
    int index = 0;
    for (int i = 0; i < klen; i++) {
        keyword[i] = toupper(keyword[i]);
    }
    for (int i = 0; i < klen; i++) {
        if (!used[keyword[i] - 'A']) {
            cipherAlphabet[index++] = keyword[i];
            used[keyword[i] - 'A'] = 1;
        }
    }
    for (char letter = 'A'; letter <= 'Z'; letter++) {
        if (!used[letter - 'A']) {
            cipherAlphabet[index++] = letter;
        }
    }
}
void encrypt(char plaintext[], char cipherAlphabet[], char ciphertext[]) {
    int plen = strlen(plaintext);

    for (int i = 0; i < plen; i++) {
        if (isalpha(plaintext[i])) {
            char letter = toupper(plaintext[i]);
            ciphertext[i] = cipherAlphabet[letter - 'A'];
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[plen] = '\0';
}
void decrypt(char ciphertext[], char cipherAlphabet[], char plaintext[]) {
    int clen = strlen(ciphertext);
    char reverseCipher[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        reverseCipher[cipherAlphabet[i] - 'A'] = 'A' + i;
    }

    for (int i = 0; i < clen; i++) {
        if (isalpha(ciphertext[i])) {
            char letter = toupper(ciphertext[i]);
            plaintext[i] = reverseCipher[letter - 'A'];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[clen] = '\0';
}

int main() {
    char keyword[] = "CIPHER";
    char cipherAlphabet[ALPHABET_SIZE];
    char plaintext[100], ciphertext[100], decryptedText[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0';

    generateCipherAlphabet(keyword, cipherAlphabet);

    printf("Cipher Alphabet: ");
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        printf("%c ", cipherAlphabet[i]);
    }
    printf("\n");

    encrypt(plaintext, cipherAlphabet, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);

    decrypt(ciphertext, cipherAlphabet, decryptedText);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}
