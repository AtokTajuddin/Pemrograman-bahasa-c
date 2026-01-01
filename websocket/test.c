#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

#pragma comment(lib, "Ws2_32.lib")  // Pastikan link library Ws2_32

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    char buffer[BUFFER_SIZE] = {0};
    const char *response = "Hello from server";
    int addrlen = sizeof(clientAddr);

    // Inisialisasi Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed: %d\n", WSAGetLastError());
        return 1;
    }

    // Membuat socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        printf("Socket creation failed: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

    // Konfigurasi alamat server
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // Bind socket ke alamat dan port
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Bind failed: %ld\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Listen untuk koneksi masuk
    if (listen(serverSocket, 3) == SOCKET_ERROR) {
        printf("Listen failed: %ld\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    printf("Waiting for a connection...\n");

    // Terima koneksi dari client
    clientSocket = accept(serverSocket, (struct sockaddr *)&clientAddr, &addrlen);
    if (clientSocket == INVALID_SOCKET) {
        printf("Accept failed: %ld\n", WSAGetLastError());
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Membaca pesan dari client
    recv(clientSocket, buffer, BUFFER_SIZE, 0);
    printf("Message received: %s\n", buffer);

    // Mengirim respons ke client
    send(clientSocket, response, strlen(response), 0);
    printf("Response sent\n");

    // Menutup socket
    closesocket(clientSocket);
    closesocket(serverSocket);

    // Membersihkan Winsock
    WSACleanup();

    return 0;
}
