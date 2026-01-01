// #include <stdio.h>
// #include <stdlib.h>
// #include <direct.h> // Untuk _getcwd di Windows

// int main() {
//     char currentDir[FILENAME_MAX]; // Buffer untuk menyimpan path

//     // Mendapatkan direktori kerja saat ini
//     if (_getcwd(currentDir, sizeof(currentDir)) != NULL) {
//         printf("Current working directory: %s\n", currentDir);
//     } else {
//         perror("Error getting current working directory");
//         return EXIT_FAILURE;
//     }

//     return EXIT_SUCCESS;
// }

#include <stdio.h>
#include <stdlib.h>
#include <direct.h> // Untuk _getcwd di Windows

#define FILENAME "index.html"

int main() {
    char currentDir[FILENAME_MAX]; // Buffer untuk menyimpan path
    char filePath[FILENAME_MAX];  // Buffer untuk path lengkap ke file

    // Mendapatkan direktori kerja saat ini
    if (_getcwd(currentDir, sizeof(currentDir)) != NULL) {
        printf("Current working directory: %s\n", currentDir);
    } else {
        perror("Error getting current working directory");
        return EXIT_FAILURE;
    }

    // Gabungkan path direktori dan nama file
    snprintf(filePath, sizeof(filePath), "%s\\%s", currentDir, FILENAME);

    // Cek apakah file ada
    FILE *file = fopen(filePath, "r");
    if (file) {
        printf("File '%s' found at path: %s\n", FILENAME, filePath);
        fclose(file);
    } else {
        perror("Error opening file");
        printf("File '%s' not found in directory: %s\n", FILENAME, currentDir);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
