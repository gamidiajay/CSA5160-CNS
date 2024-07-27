#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5
char keyMatrix[SIZE][SIZE] = {
    {'M', 'F', 'H', 'I', 'K'},
    {'U', 'N', 'O', 'P', 'Q'},
    {'Z', 'V', 'W', 'X', 'Y'},
    {'E', 'L', 'A', 'R', 'G'},
    {'D', 'S', 'T', 'B', 'C'}
};
void findPosition(char letter, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (keyMatrix[i][j] == letter || (letter == 'J' && keyMatrix[i][j] == 'I')) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}
void preprocess(char *plaintext, char *processedText) {
    int len = strlen(plaintext);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            processedText[j++] = toupper(plaintext[i]);
        }
    }
    processedText[j] = '\0';
}
void encrypt(char *plaintext, char *ciphertext) {
    char processedText[100];
    preprocess(plaintext, processedText);
    
    int len = strlen(processedText);
    for (int i = 0; i < len; i += 2) {
        if (i + 1 == len || processedText[i] == processedText[i + 1]) {
            memmove(&processedText[i + 2], &processedText[i + 1], len - i);
            processedText[i + 1] = 'X';
            len++;
        }
    }

    int row1, col1, row2, col2;
    for (int i = 0; i < len; i += 2) {
        findPosition(processedText[i], &row1, &col1);
        findPosition(processedText[i + 1], &row2, &col2);

        if (row1 == row2) {
            ciphertext[i] = keyMatrix[row1][(col1 + 1) % SIZE];
            ciphertext[i + 1] = keyMatrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            ciphertext[i] = keyMatrix[(row1 + 1) % SIZE][col1];
            ciphertext[i + 1] = keyMatrix[(row2 + 1) % SIZE][col2];
        } else {
            ciphertext[i] = keyMatrix[row1][col2];
            ciphertext[i + 1] = keyMatrix[row2][col1];
        }
    }
    ciphertext[len] = '\0';
}

int main() {
    char plaintext[] = "Must see you over Cadogan West. Coming at once.";
    char ciphertext[100];
    
    encrypt(plaintext, ciphertext);
    
    printf("Plaintext: %s\n", plaintext);
    printf("Ciphertext: %s\n", ciphertext);
    
    return 0;
}
