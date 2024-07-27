#include <stdio.h>
#include <string.h>
int modinv(int a, int m) {
  int x, y, q, t;
  x = 0; y = 1;
  if (m == 1) return 0;
  while ((a %= m) > 1) {
    q = a / m; t = m; m = a % m; a = t;
    t = x; x = y - q * x; y = t;
  }
  return (y + m) % m;
}
void decrypt(char *ciphertext, int a, int b) {
  int i, len = strlen(ciphertext);
  char plaintext[len + 1];
  for (i = 0; i < len; i++) {
    plaintext[i] = (((ciphertext[i] - 'A' - b) * modinv(a, 26)) % 26) + 'A';
  }
  plaintext[i] = '\0';
  printf("Plaintext: %s\n", plaintext);
}

int main() {
  char ciphertext[] = "YOUR_CYPHERTEXT_HERE";
  int a, b;
  a = 5;
  b = 1;
  decrypt(ciphertext, a, b);
  return 0;
}
