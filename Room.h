#pragma once
#include "stdafx.h"
class Room
{
private :
	SOCKET leftPlayer;
	SOCKET rightPlayer;

	SOCKADDR_IN leftPlayerAddr;
	SOCKADDR_IN rightPlayerAddr;

	bool isPlayerSet;
	bool isGameEnd;
	bool isLeftReady;
	bool isRightReady;

	char leftBuffer[BUFFER_SIZE];
	char rightBuffer[BUFFER_SIZE];
public :
	Room();
	~Room();

	bool getIsPlayerSet();
	bool getIsGameEnd();
	void Update();
	void Release();
	void SetPlayer(SOCKET leftPlayer, SOCKADDR_IN leftPlayerAddr, SOCKET rightPlayer, SOCKADDR_IN rightPlayerAddr);
};