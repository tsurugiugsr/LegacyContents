#pragma once
#pragma warning(disable:4996)

#include <iostream>
#include <WinSock2.h>


using namespace std;

class GameConn {
public:
	GameConn();
    //GameMap* gm;
	void Send(char s);
	void Recieve();

    WORD wVersionRequested;
    WSADATA wsaData;
    int err;
    SOCKET sockClient;
    SOCKADDR_IN addrSrv;
};

GameConn::GameConn() {
    wVersionRequested = MAKEWORD(1, 1);
    err = WSAStartup(wVersionRequested, &wsaData);
    if (0 != err)
        //return 0;
    if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
        //return 0;

    sockClient = socket(AF_INET, SOCK_DGRAM, 0);
    addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(6600);
}

void GameConn::Send(char s) {

}

void GameConn::Recieve() {

}