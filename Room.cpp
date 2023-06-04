#include "Room.h"

Room::Room() {
    isPlayerSet = false;
    isGameEnd = false;
    isLeftReady = false;
    isLeftReady = false;
}

Room::~Room() {
    closesocket(leftPlayer);
    closesocket(rightPlayer);
}

bool Room::getIsPlayerSet() {
    return isPlayerSet;
}

bool Room::getIsGameEnd() {
    return isGameEnd;
}

void Room::SetPlayer(SOCKET leftPlayer, SOCKADDR_IN leftPlayerAddr, SOCKET rightPlayer, SOCKADDR_IN rightPlayerAddr) {
    char sendData[BUFFER_SIZE] = { '0','0','0','0','0','1', ';'};
    this->leftPlayer = leftPlayer;
    this->leftPlayerAddr = leftPlayerAddr;
    send(leftPlayer, sendData, BUFFER_SIZE, 0);

    this->rightPlayer = rightPlayer;
    this->rightPlayerAddr = rightPlayerAddr;
    sendData[5] = '0';
    send(rightPlayer, sendData, BUFFER_SIZE, 0);

    isPlayerSet = true;
}

void Room::Update() {
    if (recv(leftPlayer, leftBuffer, BUFFER_SIZE, 0) == SOCKET_ERROR) {
        Release();
        return;
    }
    if (recv(rightPlayer, rightBuffer, BUFFER_SIZE, 0) == SOCKET_ERROR) {
        Release();
        return;
    }

    if (isLeftReady && isRightReady) {
        send(rightPlayer, leftBuffer, BUFFER_SIZE, 0);
        send(leftPlayer, rightBuffer, BUFFER_SIZE, 0);
    }
    else {
        if (leftBuffer[4] == '1') {
            isLeftReady = true;
            char data[BUFFER_SIZE] = { '0','0','0','0','1','0',';' };
            send(rightPlayer, data, BUFFER_SIZE, 0);
        }
        else {
            char data[BUFFER_SIZE] = { '0','0','0','0','0','0',';' };
            send(rightPlayer, data, BUFFER_SIZE, 0);
        }
        if (rightBuffer[4] == '1') {
            isRightReady = true;
            char data[BUFFER_SIZE] = { '0','0','0','0','1','1',';' };
            send(leftPlayer, data, BUFFER_SIZE, 0);
        }
        else {
            char data[BUFFER_SIZE] = { '0','0','0','0','0','1',';' };
            send(leftPlayer, data, BUFFER_SIZE, 0);
        }
    }
}

void Room::Release() {
    isGameEnd = true;
    closesocket(leftPlayer);
    closesocket(rightPlayer);
}