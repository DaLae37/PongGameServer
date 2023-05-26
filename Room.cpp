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
    this->leftPlayer = leftPlayer;
    this->rightPlayerAddr = leftPlayerAddr;
    this->rightPlayer = rightPlayer;
    this->rightPlayerAddr = rightPlayerAddr;
}

void Room::Update() {
    if (isPlayerSet) {

    }
}