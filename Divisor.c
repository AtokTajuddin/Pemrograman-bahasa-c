#include <stdio.h>
#include <math.h>
#include <stdlib.h>
int main() {
    int *N = (int *)malloc(sizeof(int));
    if (N == NULL) {
        printf("Memori tidak cukup!\n");
        return 1;
    }
    int count = 0;
    double akar;
    scanf("%d", N);
    akar = pow((double)(*N), 0.5);
    for (int i = 1; i <= (int)akar; i++) {
        if (*N % i == 0) {
            if (i == *N / i) {
                count += 1;
            } else {
                count += 2;
            }
        }
    }
    printf("%d", count);
    free(N);
    return 0;
}
