#include <stdio.h>
// Alat detektor tipe angka pada pemrograman bahasa c
//Author : Atha Tajuddin
int main() {
    // Write C code here
    int a;
    printf("Masukkan angka yang anda inginkan (Positif/Negatif) : ");
    scanf("%d",&a);
    a > 0 ? "positif" : (a < 0 ? "negatif" : "nol");
    printf("Angka yang anda masukkan %d adalah bilangan %s",a, a > 0 ? "positif" : (a < 0 ? "negatif" : "nol"));
    return 0;
}
