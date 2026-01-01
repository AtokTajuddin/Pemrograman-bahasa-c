#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Fungsi untuk mengonversi kata angka (e.g., "three") ke nilai numerik
long word_to_num(char *word) {
    if (strcmp(word, "one") == 0) return 1;
    if (strcmp(word, "two") == 0) return 2;
    if (strcmp(word, "three") == 0) return 3;
    if (strcmp(word, "four") == 0) return 4;
    if (strcmp(word, "five") == 0) return 5;
    if (strcmp(word, "six") == 0) return 6;
    if (strcmp(word, "seven") == 0) return 7;
    if (strcmp(word, "eight") == 0) return 8;
    if (strcmp(word, "nine") == 0) return 9;
    if (strcmp(word, "ten") == 0) return 10;
    if (strcmp(word, "eleven") == 0) return 11;
    if (strcmp(word, "twelve") == 0) return 12;
    if (strcmp(word, "thirteen") == 0) return 13;
    if (strcmp(word, "fourteen") == 0) return 14;
    if (strcmp(word, "fifteen") == 0) return 15;
    if (strcmp(word, "sixteen") == 0) return 16;
    if (strcmp(word, "seventeen") == 0) return 17;
    if (strcmp(word, "eighteen") == 0) return 18;
    if (strcmp(word, "nineteen") == 0) return 19;
    if (strcmp(word, "twenty") == 0) return 20;
    if (strcmp(word, "thirty") == 0) return 30;
    if (strcmp(word, "forty") == 0) return 40;
    if (strcmp(word, "fifty") == 0) return 50;
    if (strcmp(word, "sixty") == 0) return 60;
    if (strcmp(word, "seventy") == 0) return 70;
    if (strcmp(word, "eighty") == 0) return 80;
    if (strcmp(word, "ninety") == 0) return 90;
    if (strcmp(word, "hundred") == 0) return 100;
    if (strcmp(word, "thousand") == 0) return 1000;
    if (strcmp(word, "million") == 0) return 1000000;
    if (strcmp(word, "billion") == 0) return 1000000000;
    return 0;
}

// Fungsi utama untuk mengonversi string ke angka
long convert_to_num(char *str) {
    long total = 0;
    long current = 0;
    char *token = strtok(str, " ");

    while (token != NULL) {
        long num = word_to_num(token);
        if (num == 100) {
            current *= num;
        } else if (num == 1000 || num == 1000000 || num == 1000000000) {
            current *= num;
            total += current;
            current = 0;
        } else {
            current += num;
        }
        token = strtok(NULL, " ");
    }
    total += current;
    return total;
}

int main() {
    char input[1000];
    printf("Masukkan angka dalam kata (e.g., 'three hundred million'): ");
    fgets(input, sizeof(input), stdin);

    // Menghapus newline dari input
    input[strcspn(input, "\n")] = 0;

    long result = convert_to_num(input);
    printf("Hasil konversi: %ld\n", result);

    return 0;
}