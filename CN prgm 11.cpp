#include <stdio.h>
#include <math.h>

double log2_factorial(int n) {
    const double PI = 3.141592653589793;
    const double E = 2.718281828459045;
    double log2_fact = n * log2(n) - n * log2(E) + 0.5 * log2(2 * PI * n);
    return log2_fact;
}

int main() {
    int n = 25;
    int m = 4;

    double log2_25_fact = log2_factorial(n);
    double log2_4_fact = log2_factorial(m);
    double log2_unique_keys = log2_25_fact - log2_4_fact;

    printf("Approximate log2(25!) = %.2f\n", log2_25_fact);
    printf("Approximate log2(unique keys) = %.2f\n", log2_unique_keys);
    unsigned long long possible_keys = (unsigned long long)pow(2.0, log2_25_fact);
    unsigned long long unique_keys = (unsigned long long)pow(2.0, log2_unique_keys);

    printf("Approximate possible keys (25!): 2^%.2f ˜ %llu\n", log2_25_fact, possible_keys);
    printf("Approximate unique keys (25! / 4!): 2^%.2f ˜ %llu\n", log2_unique_keys, unique_keys);

    return 0;
}
