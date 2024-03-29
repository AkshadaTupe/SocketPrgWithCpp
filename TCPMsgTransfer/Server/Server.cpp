#include "stdafx.h"

int main()
{
    //Initialize winsock library
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed." << std::endl;
    }

    // socket creation
    int socketCreation = socket(AF_INET, SOCK_STREAM, 0);

    if (socketCreation == INVALID_SOCKET) {
        std::cerr << "Failed to create socket." << std::endl;
    }

    // Set server address details
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Listen on any available interface
    server_addr.sin_port = htons(12345);       // Listen on port 12345

                                               // Bind socket to address and port
    if (bind(socketCreation, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Failed to bind socket." << std::endl;
    }

    // Listen for incoming connections
    if (listen(socketCreation, 3) < 0) {
        std::cerr << "Listening failed";
        exit(EXIT_FAILURE);
    }

    std::cout << "Server started. Listening on Port 12345...\n";

    // Accept incoming connections
    int  client_fd;
    sockaddr_in client_addr;
    int  client_len = sizeof(client_addr);

    if ((client_fd = accept(socketCreation, (struct sockaddr *)&client_addr, &client_len)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Connection accepted from client.\n";

    // Recieve and Send Message
    char buffer[1024] = { 0 };

    recv(client_fd, buffer, sizeof(buffer), 0);
    printf("Message recieved from client : %s\n", buffer);

    const char* msg = "Hello, client! Data is sent from Server";

    printf("Message sent to client : %s\n", msg);

    int bytesSent = send(client_fd, msg, strlen(msg), 0);

    if (bytesSent == SOCKET_ERROR)
    {
        std::cerr << "Data was not sent" << std::endl;
        exit(EXIT_FAILURE);
    }

    //close socket
    closesocket(socketCreation);
    return 0;
}

