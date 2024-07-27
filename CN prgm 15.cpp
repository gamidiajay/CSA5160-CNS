#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_PLAINTEXTS 100
float englishLetterFrequencies[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966, 0.153,
    0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987, 6.327, 9.056,
    2.758, 0.978, 2.361, 0.150, 1.974, 0.074
};
float calculateScore(const char *plaintext) {
    int letterCount[ALPHABET_SIZE] = {0};
    int len = strlen(plaintext);
    int totalLetters = 0;

    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            letterCount[tolower(plaintext[i]) - 'a']++;
            totalLetters++;
        }
    }

    float score = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        float observedFrequency = (float)letterCount[i] / totalLetters * 100;
        score += observedFrequency * englishLetterFrequencies[i];
    }

    return score;
}
void decrypt(const char *ciphertext, char *plaintext, int key) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            plaintext[i] = ((ciphertext[i] - base - key + ALPHABET_SIZE) % ALPHABET_SIZE) + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[len] = '\0';
}
typedef struct {
    char plaintext[100];
    float score;
} PossiblePlaintext;
int compare(const void *a, const void *b) {
    PossiblePlaintext *plaintextA = (PossiblePlaintext *)a;
    PossiblePlaintext *plaintextB = (PossiblePlaintext *)b;
    if (plaintextA->score < plaintextB->score) return 1;
    if (plaintextA->score > plaintextB->score) return -1;
    return 0;
}

int main() {
    char ciphertext[] = "ZLWSL BJQ JGTBJ";
    int numTopPlaintexts;

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &numTopPlaintexts);

    PossiblePlaintext possiblePlaintexts[MAX_PLAINTEXTS];
    int count = 0;
    for (int key = 0; key < ALPHABET_SIZE; key++) {
        decrypt(ciphertext, possiblePlaintexts[count].plaintext, key);
        possiblePlaintexts[count].score = calculateScore(possiblePlaintexts[count].plaintext);
        count++;
    }
    qsort(possiblePlaintexts, count, sizeof(PossiblePlaintext), compare);
    printf("Top %d possible plaintexts:\n", numTopPlaintexts);
    for (int i = 0; i < numTopPlaintexts && i < count; i++) {
        printf("%d. %s (Score: %.2f)\n", i + 1, possiblePlaintexts[i].plaintext, possiblePlaintexts[i].score);
    }

    return 0;
}
