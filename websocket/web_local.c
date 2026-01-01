#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <stdlib.h>

#define PORT 8080
#define BUFFER_SIZE 1024  // Ukuran buffer yang akan digunakan

// Fungsi untuk mengirimkan file HTML
void sendFile(SOCKET clientSocket) {
    FILE *file = fopen("index.html", "rb");  
    if (file == NULL) {
        printf("File not found\n");
        char *httpHeader = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n";
        send(clientSocket, httpHeader, strlen(httpHeader), 0);
        return;
    }

    // Alokasikan memori untuk buffer
    char *buffer = (char *)malloc(BUFFER_SIZE);
    if (buffer == NULL) {
        printf("Memory allocation failed\n");
        fclose(file);
        return;
    }

    size_t bytesRead;

    // Kirim HTTP header
    char *httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
    send(clientSocket, httpHeader, strlen(httpHeader), 0);

    // Kirim konten file
    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        send(clientSocket, buffer, bytesRead, 0);
    }

    // Bebaskan memori yang dialokasikan
    free(buffer);
    fclose(file);
}

// Fungsi utama untuk menjalankan server
int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrSize = sizeof(clientAddr);

    // Inisialisasi WinSock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed: %d\n", WSAGetLastError());
        return 1;
    }

    // Membuat socket server
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        printf("Socket creation failed: %d\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Setup alamat server
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Menerima koneksi dari semua alamat IP
    serverAddr.sin_port = htons(PORT);

    // Mengikat socket dengan alamat server
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Bind failed: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("Server bound to port %d, listening for connections...\n", PORT);

    // Mendengarkan koneksi dari client
    if (listen(serverSocket, 3) == SOCKET_ERROR) {
        printf("Listen failed: %d\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Loop untuk menerima dan menangani koneksi client
    while (1) {
        // Menerima koneksi dari client
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
        if (clientSocket == INVALID_SOCKET) {
            printf("Accept failed: %d\n", WSAGetLastError());
            continue;  // Jika ada masalah, coba lagi
        }

        printf("Client connected, sending file...\n");

        // Kirim file HTML ke client
        sendFile(clientSocket);

        // Menutup socket client setelah file terkirim
        closesocket(clientSocket);
    }

    // Menutup socket server setelah keluar dari loop (meskipun ini tidak akan tercapai dalam kode ini)
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
