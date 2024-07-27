#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void analyze_frequency(const char *text, int *frequency);
void print_frequency(int *frequency);
void decrypt_message(const char *ciphertext, const char *key);

int main() {
    const char *ciphertext = "53‡‡†305))6*;4826)4‡.)4‡);806*;48†8¶60))85;;]8*;:‡*8†83 "
                             "(88)5*†;46(;88*96*?;8)*‡(;485);5*†2:*‡(;4956*2(5*—4)8¶8* "
                             ";4069285);)6†8)4‡‡;1(‡9;48081;8:8‡1;48†85;4)485†528806*81 "
                             "(‡9;48;(88;4(‡?34;48)4‡;161;:188;‡?;";

    int frequency[256] = {0};
    analyze_frequency(ciphertext, frequency);
    print_frequency(frequency);
    char key[256] = {0};
    key['5'] = 't';
    key['3'] = 'h';
    key['‡'] = 'e';
    key['†'] = 'a';
    key['0'] = 'o';
    key['6'] = 'i';
    key['*'] = 'n';
    key['4'] = 's';
    key['8'] = 'r';
    key['2'] = 'd';
    key['¶'] = 'l';
    key[')'] = 'u';
    key[';'] = 'c';
    key[']'] = 'm';
    key[':'] = 'w';
    key['('] = 'f';
    key['?'] = 'y';
    key['9'] = 'g';
    key['1'] = 'b';
    key['—'] = 'p';
    decrypt_message(ciphertext, key);

    return 0;
}

void analyze_frequency(const char *text, int *frequency) {
    for (const char *p = text; *p; p++) {
        frequency[(unsigned char)*p]++;
    }
}

void print_frequency(int *frequency) {
    printf("Character frequency analysis:\n");
    for (int i = 0; i < 256; i++) {
        if (frequency[i] > 0) {
            printf("'%c' : %d\n", i, frequency[i]);
        }
    }
}

void decrypt_message(const char *ciphertext, const char *key) {
    printf("\nDecrypted message:\n");
    for (const char *p = ciphertext; *p; p++) {
        if (key[(unsigned char)*p]) {
            putchar(key[(unsigned char)*p]);
        } else {
            putchar(*p);
        }
    }
    printf("\n");
}
