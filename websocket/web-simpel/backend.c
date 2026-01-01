#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void sendFile(int clientSocket, char *filename) {
  FILE *file = fopen(filename, "rb");
  if (file == NULL) {
    printf("File not found\n");
    return;
  }

  char buffer[BUFFER_SIZE];
  size_t bytesRead;

  while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
    send(clientSocket, buffer, bytesRead, 0);
  }

  fclose(file);
}

void handleRequest(int clientSocket) {
  char buffer[BUFFER_SIZE];
  int bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
  if (bytesRead < 0) {
    printf("Error reading request\n");
    return;
  }

  buffer[bytesRead] = '\0';
  printf("Request: %s\n", buffer);

  if (strncmp(buffer, "GET /", 5) == 0) {
    sendFile(clientSocket, "index.html");
  } else if (strncmp(buffer, "POST /tambah-buku", 17) == 0) {
    // Tambah buku ke database
    char judul[100], pengarang[100], tahun[10];
    sscanf(buffer, "POST /tambah-buku?judul=%s&pengarang=%s&tahun=%s", judul, pengarang, tahun);
    printf("Tambah buku: %s, %s, %s\n", judul, pengarang, tahun);
  }
}

int main() {
  int serverSocket, clientSocket;
  struct sockaddr_in serverAddr, clientAddr;
  int clientAddrSize = sizeof(clientAddr);

  // Buat socket server
  serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (serverSocket < 0) {
    printf("Error creating socket\n");
    return 1;
  }

  // Set alamat server
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  serverAddr.sin_port = htons(PORT);

  // Bind socket ke alamat server
  if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
    printf("Error binding socket\n");
    return 1;
  }

  // Listen untuk koneksi
  if (listen(serverSocket, 3) < 0) {
    printf("Error listening for connections\n");
    return 1;
  }

  printf("Server listening on port %d...\n", PORT);

  while (1) {
    // Terima koneksi dari client
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrSize);
    if (clientSocket < 0) {
      printf("Error accepting connection\n");
      continue;
    }

    printf("Client connected...\n");

    // Handle request dari client
    handleRequest(clientSocket);

    // Tutup socket client
    close(clientSocket);
  }

  return 0;
}