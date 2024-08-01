#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TEXT_SIZE 1000
#define ALPHABET_SIZE 26
const char english_freq[] = "etaoinshrdlcumwfgypbvkjxqz";
void analyze_frequency(const char *ciphertext, int freq[]);
void generate_plaintexts(const char *ciphertext, const int freq[], char plaintexts[][MAX_TEXT_SIZE], int topN);

int main() {
    char ciphertext[MAX_TEXT_SIZE];
    int freq[ALPHABET_SIZE] = {0};
    int topN;
    printf("Enter the ciphertext: ");
    fgets(ciphertext, MAX_TEXT_SIZE, stdin);
    ciphertext[strcspn(ciphertext, "\n")] = 0;
    printf("Enter the number of top possible plaintexts to generate: ");
    scanf("%d", &topN);
    analyze_frequency(ciphertext, freq);
    char plaintexts[topN][MAX_TEXT_SIZE];
    generate_plaintexts(ciphertext, freq, plaintexts, topN);
    for (int i = 0; i < topN; i++) {
        printf("Possible plaintext #%d: %s\n", i + 1, plaintexts[i]);
    }

    return 0;
}
void analyze_frequency(const char *ciphertext, int freq[]) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            freq[ciphertext[i] - 'a']++;
        } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            freq[ciphertext[i] - 'A']++;
        }
    }
}
int compare_freq(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}
void generate_plaintexts(const char *ciphertext, const int freq[], char plaintexts[][MAX_TEXT_SIZE], int topN) {
    int sorted_freq[ALPHABET_SIZE];
    memcpy(sorted_freq, freq, ALPHABET_SIZE * sizeof(int));
    qsort(sorted_freq, ALPHABET_SIZE, sizeof(int), compare_freq);

    for (int i = 0; i < topN; i++) {
        for (int j = 0; j < MAX_TEXT_SIZE; j++) {
            plaintexts[i][j] = '\0';
        }
    }
    for (int n = 0; n < topN; n++) {
        int mapping[ALPHABET_SIZE] = {0};
        int assigned[ALPHABET_SIZE] = {0};

        for (int i = 0; i < ALPHABET_SIZE; i++) {
            for (int j = 0; j < ALPHABET_SIZE; j++) {
                if (freq[j] == sorted_freq[i] && !assigned[j]) {
                    mapping[j] = english_freq[(i + n) % ALPHABET_SIZE];
                    assigned[j] = 1;
                    break;
                }
            }
        }
        for (int i = 0; ciphertext[i] != '\0'; i++) {
            if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
                plaintexts[n][i] = mapping[ciphertext[i] - 'a'];
            } else if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
                plaintexts[n][i] = mapping[ciphertext[i] - 'A'];
            } else {
                plaintexts[n][i] = ciphertext[i];
            }
        }
    }
}
