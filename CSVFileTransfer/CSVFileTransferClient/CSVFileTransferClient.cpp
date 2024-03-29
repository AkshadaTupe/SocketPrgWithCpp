// CSVFileTransferClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <sstream>
#include <fstream>

void sendMsg(int client_SocketDescriptor)
{
    // Read CSV file
    std::ifstream file("C://Users//320159441//Documents//GitHub//CSVFileTransfer//CSVFileTransferClient//studentProfile.csv");
    std::stringstream fileContent;
    fileContent << file.rdbuf();
    std::string csvData = fileContent.str();

    std::cout << "Message sent to Server : " << csvData << "\n";

    int bytesSent = send(client_SocketDescriptor, csvData.c_str(), csvData.size(), 0);

    if (bytesSent == SOCKET_ERROR)
    {
        std::cerr << "Data was not sent" << std::endl;
        exit(EXIT_FAILURE);
    }

}
int main()
{
    Logger* obj = new Logger();

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        std::cerr << "WSAStartup failed.";
    else
        obj->Debug("Initialization of Winsock Library is Successfully");

    int client_SocketDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    if (client_SocketDescriptor == INVALID_SOCKET)
        std::cerr << "Failed to create socket.";
    else
        obj->Debug("Socket Created Successfully");

    sockaddr_in clientAddr;
    clientAddr.sin_family = AF_INET;
    clientAddr.sin_port = htons(12345);       // Listen on port 12345
    clientAddr.sin_addr.s_addr = INADDR_ANY; // Listen on any available interface

    inet_pton(AF_INET, "127.0.0.1", &clientAddr.sin_addr);

    if (connect(client_SocketDescriptor, (sockaddr*)&clientAddr, sizeof(clientAddr)) == SOCKET_ERROR)
        std::cerr << "Failed to connect.";
    else
        obj->Debug("Connection Successfull");

    sendMsg(client_SocketDescriptor);
    
    closesocket(client_SocketDescriptor);
    return 0;
}

