#pragma once
#pragma warning(disable:4996)

#include <iostream>
#include <WinSock2.h>
#include <windows.h>

DWORD WINAPI Recieve(LPVOID lpParam);
char p2d;

using namespace std;

class GameMap {
public:
	GameMap();

	int map[12][8]={
		-1,-1,-1,-1,		-1,-1,-1,-1,
		-1,2,-1,0,		-1,-1,0,-1,
		-1,0,-1,0,		0,0,0,-1,
		-1,0,0,0,		0,-1,-1,-1,
		-1,-1,0,-1,		-1,-1,0,-1,
		-1,0,0,0,		0,-1,0,-1,
		-1,0,-1,0,		0,0,0,-1,
		-1,0,-1,-1,		-1,0,-1,-1,
		-1,-1,-1,0,		0,0,0,-1,
		-1,0,0,0,		0,-1,0,-1,
		-1,0,-1,-1,		0,-1,1,-1,
		-1,-1,-1,-1,-1,-1,-1,-1
	};
	int endFlag;

	void move(int p, char d);
	int win();


	~GameMap();


	void GameConn();

	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	SOCKET sockClient;
	SOCKADDR_IN addrSrv;
	int gm;

	void Send(char s);



};

GameMap::GameMap() {
	GameConn();
	HANDLE tt = CreateThread(NULL, 0, Recieve, NULL, 0, NULL);

}

void GameMap::move(int p, char d) {
	int i = 0, j = 0, a = 0, b = 0;
	do {
		do {
			if (map[i][j] == p){
				a = i;
				b = j;
			}
			j++;
		} while (j < 8);
		j = 0;
		i++;
	} while (i < 12);
	switch (d) {
	case 'w':
		if (a > 0 && map[a - 1][b] == 0)
		{
			map[a - 1][b] = p;
			map[a][b] = 0;
		}
		if (p==1)
			Send('s');
		break;
	case 's':
		if (a <11 && map[a + 1][b] == 0)
		{
			map[a + 1][b] = p;
			map[a][b] = 0;
		}
		if(p==1)
			Send('w');
		break;
	case 'a':
		if (b > 0 && map[a][b - 1] == 0)
		{
			map[a][b - 1] = p;
			map[a][b] = 0;
		}
		if(p==1)
			Send('d');
		break;
	case 'd':
		if (b < 8 && map[a][b + 1] == 0)
		{
			map[a][b + 1] = p;
			map[a][b] = 0;
		}
		if (p == 1)
			Send('a');
		break;
	}
	endFlag = win();
}

int GameMap::win() {
	int i = 0, j = 0, a = 0, b = 0, c = 0, d = 0;
	do {
		do {
			if (map[i][j] == 1) {
				a = i;
				b = j;
			}
			if (map[i][j] == 2) {
				c = i;
				d = j;
			}
			j++;
		} while (j < 8);
		j = 0;
		i++;
	} while (i < 12);
	if ((a == c && abs(b - d) == 1) || (b == d) && abs(a - c) == 1)
		return 1;
	return 0;
}


void GameMap::GameConn() {
	wVersionRequested = MAKEWORD(1, 1);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (0 != err)
		return;
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
		return;

	sockClient = socket(AF_INET, SOCK_DGRAM, 0);
	addrSrv.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6601);
}

void GameMap::Send(char s) {
	char ss[3];
	ss[0] = s;
	ss[1] = 'y';
	ss[2] = '\0';
	sendto(sockClient, ss, sizeof(ss) + 1, 0, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
}

DWORD WINAPI Recieve(LPVOID lpParam) {
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSADATA wsaData;
	int err;
	err = WSAStartup(wVersionRequested, &wsaData);
	if (0 != err)
		return 0;
	if (LOBYTE(wsaData.wVersion) != 1 || HIBYTE(wsaData.wVersion) != 1)
		return 0;

	SOCKET sockSrv = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6600);


	bind(sockSrv, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	char recvBuf[100];
	SOCKADDR_IN addrClient;
	int lenAddr = sizeof(SOCKADDR);
	//sendto()
	do {

		recvfrom(sockSrv, recvBuf, 100, 0, (SOCKADDR*)&addrClient, &lenAddr);
		if(recvBuf[1]=='x')
			p2d = recvBuf[0];
	} while (true);
	closesocket(sockSrv);
	WSACleanup();
}

GameMap::~GameMap() {
	closesocket(sockClient);
	WSACleanup();

}