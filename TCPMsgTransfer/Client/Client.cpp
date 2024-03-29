#include "stdafx.h"

int main()
{
    //Initialize winsock library
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    // socket creation
    int socketCreation = socket(AF_INET, SOCK_STREAM, 0);

    if (socketCreation == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Set server address details
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(12345);
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    //Connect Socket
    if (connect(socketCreation, (sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR)
    {
        std::cerr << "Connection failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cout << "Connected with Server.\n";

    //Send and recieve data
    const char* msg = "Hello, server! Data is sent from client";

    std::cout << "Message sent to Server : " << msg << "\n";

    int bytesSent = send(socketCreation, msg, strlen(msg), 0);

    if (bytesSent == SOCKET_ERROR)
    {
        std::cerr << "Data was not sent" << std::endl;
        exit(EXIT_FAILURE);
    }

    char buffer[1024] = { 0 };
    recv(socketCreation, buffer, sizeof(buffer), 0);
    printf("Message recieved from Server : %s\n", buffer);

    // Shut down the socket for further sending and recieving data
    if (shutdown(socketCreation, SD_BOTH) == -1) {
        std::cerr << "Error shutting down socket" << std::endl;
        // Handle error
    }

    //close socket
    closesocket(socketCreation);

    return 0;
}

