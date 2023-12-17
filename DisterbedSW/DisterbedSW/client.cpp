#include <iostream>
#include <winsock2.h>
#include <WS2tcpip.h> // Для использования функции inet_pton

int main() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Failed to initialize Winsock" << std::endl;
        return 1;
    }

    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Error creating client socket" << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr); // Преобразование IP-адреса

    serverAddr.sin_port = htons(12345);

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Error connecting to server" << std::endl;
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    char buffer[1024];
    int bytesReceived = recv(clientSocket, buffer, 1024, 0);
    if (bytesReceived == SOCKET_ERROR) {
        std::cerr << "Error receiving data from server" << std::endl;
    }
    else {
        std::cout << "Received from server: " << std::string(buffer, bytesReceived) << std::endl;
    }

    closesocket(clientSocket);
    WSACleanup();

    return 0;
}
