#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NC 26
#define A 'A'

// rotors
const char *rs[] = {
    "BDFHJLCPRTXVZNYEIWGAKMUSQO", // fast
    "AJDKSIRUXBLHWTMCQGZNPYFVOE", // medium
    "EKMFLGDQVZNTOWYHXUSPAIBRCJ", // slow
    "IXUHFEZDAOMTKQJWNSRLCYPBVG"  // reflect
};

// apply a cipher/rotor `r` to a letter `c`
char rapply(char c, const char *r) {
    return r[c - A];
}

// invert a cipher/rotor `r`
void invert(const char *r, char *inv) {
    int i;
    for (i = 0; i < NC; i++) {
        inv[r[i] - A] = A + i;
    }
}

// encrypt letter `c` with rotors in default* positions
char rotors(char c, const char **rs) {
    int i;
    for (i = 0; i < 4; i++) {
        c = rapply(c, rs[i]);
    }
    return c;
}

// define enigma function
void enigma(const char *text, char *result, const char **rs) {
    int i;
    for (i = 0; text[i] != '\0'; i++) {
        result[i] = rotors(text[i], rs);
    }
    result[i] = '\0';
}

int main() {
    srand(time(NULL));

    // extend the rotor set to include inverted ciphers
    const char *extended_rs[7];
    char inv[NC + 1];
    int i;
    for (i = 0; i < 4; i++) {
        extended_rs[i] = rs[i];
    }
    for (i = 0; i < 3; i++) {
        invert(rs[2 - i], inv);
        extended_rs[4 + i] = strdup(inv);
    }

    // generate a random sample
    char sample[17];
    for (i = 0; i < 16; i++) {
        sample[i] = A + rand() % NC;
    }
    sample[16] = '\0';

    // encrypt the sample
    char secret[17];
    enigma(sample, secret, extended_rs);

    // print the result
    printf("Sample: %s\n", sample);
    printf("Secret: %s\n", secret);

    // free allocated memory
    for (i = 4; i < 7; i++) {
        free((void *)extended_rs[i]);
    }

    return 0;
}
