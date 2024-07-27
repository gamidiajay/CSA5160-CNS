#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MOD 26
void encrypt(const char *plaintext, const int *key, char *ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = (plaintext[i] - base + key[i]) % MOD + base;
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[len] = '\0';
}
void decrypt(const char *ciphertext, const int *key, char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = (ciphertext[i] - base - key[i] + MOD) % MOD + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[len] = '\0';
}
void findKey(const char *ciphertext, const char *desired_plaintext, int *key) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i]) && isalpha(desired_plaintext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            key[i] = (ciphertext[i] - desired_plaintext[i] + MOD) % MOD;
        } else {
            key[i] = 0;
        }
    }
}

int main() {
    char plaintext[] = "send more money";
    char ciphertext[100], decryptedText[100];
    int key[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int len = strlen(plaintext);
    encrypt(plaintext, key, ciphertext);
    printf("Encrypted Text: %s\n", ciphertext);
    char desired_plaintext[] = "cash not needed";
    int newKey[len];
    findKey(ciphertext, desired_plaintext, newKey);
    decrypt(ciphertext, newKey, decryptedText);
    printf("Decrypted Text with new key: %s\n", decryptedText);
    printf("New Key: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", newKey[i]);
    }
    printf("\n");

    return 0;
}
