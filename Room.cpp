#include "Room.h"

Room::Room() {
    isPlayerSet = false;
    isGameEnd = false;
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
    char sendData[BUFFER_SIZE] = { '0','0','0','0','1','1', ';' ,';'};
    this->leftPlayer = leftPlayer;
    this->leftPlayerAddr = leftPlayerAddr;
    send(leftPlayer, sendData, BUFFER_SIZE, 0);

    this->rightPlayer = rightPlayer;
    this->rightPlayerAddr = rightPlayerAddr;
    sendData[6] = '0';
    send(rightPlayer, sendData, BUFFER_SIZE, 0);
}

void Room::Update() {
    if (isPlayerSet) {
        if (recv(leftPlayer, leftBuffer, BUFFER_SIZE, 0) == SOCKET_ERROR) {
            Release();
            return;
        }
        else {
            send(rightPlayer, leftBuffer, BUFFER_SIZE, 0);
        }
        if(recv(rightPlayer, leftBuffer, BUFFER_SIZE, 0) == SOCKET_ERROR){
            Release();
            return;
        }
        else {
            send(leftPlayer, rightBuffer, BUFFER_SIZE, 0);
        }
    }
}

void Room::Release() {
    isGameEnd = true;
    closesocket(leftPlayer);
    closesocket(rightPlayer);
}