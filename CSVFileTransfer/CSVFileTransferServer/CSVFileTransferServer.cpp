// CSVFileTransferServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fstream>

void transferIntoFile(char buffer[])
{
    Logger* obj = new Logger(); 
    ofstream file("C://Users//320159441//Documents//GitHub//CSVFileTransfer//CSVFileTransferServer//studentProfile.csv", std::ios::app);
    if (!file.is_open())
        obj->Error("Error Opening File");

    file << buffer;
 
    file.close();
}
void recvMsg(int client_SocketDescriptor)
{
    // Recieve and Send Message
    char buffer[1024] = { 0 };

    recv(client_SocketDescriptor, buffer, sizeof(buffer), 0);
    printf("Message recieved from client : %s\n", buffer);

    transferIntoFile(buffer);
}
int main()
{
    Logger* obj = new Logger();

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        obj->Error("WSAStartup failed.");
    else
        obj->Debug("Initialization of Winsock Library is Successfully");

    int server_SocketDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    if (server_SocketDescriptor == INVALID_SOCKET)
        obj->Error("Failed to create socket.");
    else
        obj->Debug("Socket Created Successfully.");

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;

    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(12345);


    if (bind(server_SocketDescriptor, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
        obj->Error("Failed to bind socket.");
    else
        obj->Debug("Socket Binded Successfully.");


    if (listen(server_SocketDescriptor, 3) < 0)
        obj->Error("Listening failed");
    else
        obj->Debug("Socket in Listen State(Max Connection Queue : 3)");

    int client_SocketDescriptor;
    sockaddr_in client_addr;
    int  client_len = sizeof(client_addr);

    if ((client_SocketDescriptor = accept(server_SocketDescriptor, (struct sockaddr *)&client_addr, &client_len)) < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    obj->Debug("Connection accepted from client.\n");

    recvMsg(client_SocketDescriptor);
   

    if (shutdown(server_SocketDescriptor, SD_BOTH) == -1) {
        obj->Error("Error shutting down socket");
        // Handle error
    }

    //close socket
    closesocket(server_SocketDescriptor);
    return 0;
}

