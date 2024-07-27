#include <stdio.h>
#include <string.h>
#include <ctype.h>

void create_playfair_matrix(const char *key, char matrix[5][5]);
void preprocess_text(const char *input, char *output);
void decrypt_playfair(const char *ciphertext, char matrix[5][5], char *plaintext);
void find_position(char ch, char matrix[5][5], int *row, int *col);

int main() {
    const char *key = "KEYWORD";
    char matrix[5][5];
    char ciphertext[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";
    char plaintext[200];
    create_playfair_matrix(key, matrix);
    decrypt_playfair(ciphertext, matrix, plaintext);
    printf("Decrypted message: %s\n", plaintext);

    return 0;
}

void create_playfair_matrix(const char *key, char matrix[5][5]) {
    int used[26] = {0};
    int index = 0;
    char ch;
    for (int i = 0; key[i] != '\0'; i++) {
        ch = toupper(key[i]);
        if (ch == 'J') ch = 'I';
        if (!used[ch - 'A']) {
            matrix[index / 5][index % 5] = ch;
            used[ch - 'A'] = 1;
            index++;
        }
    }
    for (ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue;
        if (!used[ch - 'A']) {
            matrix[index / 5][index % 5] = ch;
            used[ch - 'A'] = 1;
            index++;
        }
    }
}

void preprocess_text(const char *input, char *output) {
    int len = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {
            output[len++] = toupper(input[i]);
        }
    }
    output[len] = '\0';
}

void decrypt_playfair(const char *ciphertext, char matrix[5][5], char *plaintext) {
    int len = strlen(ciphertext);
    char digraph[3];
    int row1, col1, row2, col2;

    for (int i = 0; i < len; i += 2) {
        digraph[0] = toupper(ciphertext[i]);
        digraph[1] = toupper(ciphertext[i + 1]);
        digraph[2] = '\0';
        find_position(digraph[0], matrix, &row1, &col1);
        find_position(digraph[1], matrix, &row2, &col2);

        if (row1 == row2) {
            plaintext[i] = matrix[row1][(col1 + 4) % 5];
            plaintext[i + 1] = matrix[row2][(col2 + 4) % 5];
        } else if (col1 == col2) {
            plaintext[i] = matrix[(row1 + 4) % 5][col1];
            plaintext[i + 1] = matrix[(row2 + 4) % 5][col2];
        } else {
            plaintext[i] = matrix[row1][col2];
            plaintext[i + 1] = matrix[row2][col1];
        }
    }
    plaintext[len] = '\0';
}

void find_position(char ch, char matrix[5][5], int *row, int *col) {
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            if (matrix[r][c] == ch) {
                *row = r;
                *col = c;
                return;
            }
        }
    }
}

