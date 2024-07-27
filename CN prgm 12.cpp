#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 2
#define MOD 26
int keyMatrix[MATRIX_SIZE][MATRIX_SIZE] = {
    {9, 4},
    {5, 7}
};
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) return x;
    }
    return -1;
}
int determinant(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    return (matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0]) % MOD;
}
void adjugate(int matrix[MATRIX_SIZE][MATRIX_SIZE], int adjMatrix[MATRIX_SIZE][MATRIX_SIZE]) {
    adjMatrix[0][0] = matrix[1][1];
    adjMatrix[0][1] = -matrix[0][1];
    adjMatrix[1][0] = -matrix[1][0];
    adjMatrix[1][1] = matrix[0][0];
}
void encryptPair(char *pair, char *encryptedPair) {
    int x1 = pair[0] - 'A';
    int x2 = pair[1] - 'A';
    encryptedPair[0] = (keyMatrix[0][0] * x1 + keyMatrix[0][1] * x2) % MOD + 'A';
    encryptedPair[1] = (keyMatrix[1][0] * x1 + keyMatrix[1][1] * x2) % MOD + 'A';
}
void decryptPair(char *pair, char *decryptedPair, int invKeyMatrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int y1 = pair[0] - 'A';
    int y2 = pair[1] - 'A';
    decryptedPair[0] = (invKeyMatrix[0][0] * y1 + invKeyMatrix[0][1] * y2) % MOD + 'A';
    decryptedPair[1] = (invKeyMatrix[1][0] * y1 + invKeyMatrix[1][1] * y2) % MOD + 'A';
}
void preparePlaintext(const char *plaintext, char *preparedText) {
    int len = strlen(plaintext);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            preparedText[j++] = toupper(plaintext[i]);
        }
    }
    if (j % 2 != 0) preparedText[j++] = 'X';
    preparedText[j] = '\0';
}

int main() {
    char plaintext[] = "meet me at the usual place at ten rather than eight oclock";
    char preparedText[100], ciphertext[100], decryptedText[100];
    preparePlaintext(plaintext, preparedText);
    int len = strlen(preparedText);
    for (int i = 0; i < len; i += 2) {
        encryptPair(&preparedText[i], &ciphertext[i]);
    }
    ciphertext[len] = '\0';
    int det = determinant(keyMatrix);
    int invDet = modInverse(det, MOD);
    if (invDet == -1) {
        printf("No modular inverse for determinant %d\n", det);
        return 1;
    }

    int adjMatrix[MATRIX_SIZE][MATRIX_SIZE];
    adjugate(keyMatrix, adjMatrix);

    int invKeyMatrix[MATRIX_SIZE][MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            invKeyMatrix[i][j] = (adjMatrix[i][j] * invDet) % MOD;
            if (invKeyMatrix[i][j] < 0) invKeyMatrix[i][j] += MOD;
        }
    }
    for (int i = 0; i < len; i += 2) {
        decryptPair(&ciphertext[i], &decryptedText[i], invKeyMatrix);
    }
    decryptedText[len] = '\0';

    printf("Plaintext: %s\n", plaintext);
    printf("Prepared Text: %s\n", preparedText);
    printf("Ciphertext: %s\n", ciphertext);
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}
