//�ͻ���
#include <winsock2.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <direct.h>     
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996)

#define USER_ERROR -1

int main()
{   
    char recvData[200];
    char sendData[200];
    int ret;


    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        
            printf("Failed to load Winsock.\n");
        return USER_ERROR;
    }

    SOCKET socket_client = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_client == INVALID_SOCKET)
    {
        
            printf(" Failed socket() \n");
        return 0;
    }

    struct sockaddr_in server_in;
    server_in.sin_family = AF_INET;
    server_in.sin_port = htons(6666);
    server_in.sin_addr.S_un.S_addr = inet_addr("192.168.1.3");

    if (connect(socket_client, (struct sockaddr*)&server_in, sizeof(server_in)) == -1)
    {
        
            printf(" Failed connect() \n");
        return 0;
    }
    else
    {
        
            printf("connect %s.%d\n", inet_ntoa(server_in.sin_addr), server_in.sin_port);
        while (1)
        {
            
                printf("������Ϣ��");
            gets(sendData);
            printf("\n");
            send(socket_client, sendData, strlen(sendData), 0);
            if (strcmp(sendData, "quit") == 0)
                break;
            printf("��ȡ��Ϣ��");
            recvData[0] = '\0';
            ret = recv(socket_client, recvData, 200, 0);
            recvData[ret] = '\0';
            printf("%s\n", recvData);
        }

    }
    closesocket(socket_client);
    WSACleanup();
    return 0;
}
