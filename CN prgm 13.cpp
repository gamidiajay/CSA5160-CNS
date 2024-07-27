#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MATRIX_SIZE 2
#define MOD 26
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
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
void multiplyMatrices(int matrix1[MATRIX_SIZE][MATRIX_SIZE], int matrix2[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
            result[i][j] = (result[i][j] % MOD + MOD) % MOD;
        }
    }
}
void recoverKeyMatrix(char *plaintext, char *ciphertext, int recoveredKeyMatrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int plainMatrix[MATRIX_SIZE][MATRIX_SIZE], cipherMatrix[MATRIX_SIZE][MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            plainMatrix[i][j] = plaintext[i * MATRIX_SIZE + j] - 'A';
            cipherMatrix[i][j] = ciphertext[i * MATRIX_SIZE + j] - 'A';
        }
    }
    int det = determinant(plainMatrix);
    int invDet = modInverse(det, MOD);
    if (invDet == -1) {
        printf("No modular inverse for determinant %d\n", det);
        exit(1);
    }
    int adjMatrix[MATRIX_SIZE][MATRIX_SIZE];
    adjugate(plainMatrix, adjMatrix);
    int invPlainMatrix[MATRIX_SIZE][MATRIX_SIZE];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            invPlainMatrix[i][j] = (adjMatrix[i][j] * invDet) % MOD;
            if (invPlainMatrix[i][j] < 0) {
                invPlainMatrix[i][j] += MOD;
            }
        }
    }
    multiplyMatrices(invPlainMatrix, cipherMatrix, recoveredKeyMatrix);
}
void decryptPair(char *pair, char *decryptedPair, int keyMatrix[MATRIX_SIZE][MATRIX_SIZE]) {
    int y1 = pair[0] - 'A';
    int y2 = pair[1] - 'A';
    decryptedPair[0] = (keyMatrix[0][0] * y1 + keyMatrix[0][1] * y2) % MOD + 'A';
    decryptedPair[1] = (keyMatrix[1][0] * y1 + keyMatrix[1][1] * y2) % MOD + 'A';
}
void prepareText(const char *input, char *output) {
    int len = strlen(input);
    int j = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(input[i])) {
            output[j++] = toupper(input[i]);
        }
    }
    if (j % 2 != 0) output[j++] = 'X';
    output[j] = '\0';
}

int main() {
    char plaintext[] = "meet";
    char ciphertext[] = "EGDD";
    char preparedText[100], decryptedText[100];
    int recoveredKeyMatrix[MATRIX_SIZE][MATRIX_SIZE];
    prepareText(plaintext, preparedText);
    prepareText(ciphertext, ciphertext);
    recoverKeyMatrix(preparedText, ciphertext, recoveredKeyMatrix);
    printf("Recovered Key Matrix:\n");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", recoveredKeyMatrix[i][j]);
        }
        printf("\n");
    }
    char message[] = "EGDD";
    char decryptedMessage[100];
    prepareText(message, message);
    int len = strlen(message);

    for (int i = 0; i < len; i += 2) {
        decryptPair(&message[i], &decryptedMessage[i], recoveredKeyMatrix);
    }
    decryptedMessage[len] = '\0';

    printf("Decrypted Message: %s\n", decryptedMessage);

    return 0;
}
