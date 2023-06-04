#pragma once
#include "stdafx.h"
#include "Room.h"

typedef std::pair<SOCKET, SOCKADDR_IN> CLIENT;
typedef std::pair<Room*, std::thread*> GAME;

void StartGame(Room *room, std::thread*gameThread) {
    while (!room->getIsGameEnd()) {
        room->Update();
    }
}

int main() {
    std::deque<CLIENT> clientList;
    std::deque<GAME> gameList;

    WSADATA wsaData;
    SOCKET serverSock = socket(PF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(3737);

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cout << "Ver 2.2 Erorr" << std::endl;
        return 1;
    }
    if (bind(serverSock, (SOCKADDR*)&addr, sizeof(SOCKADDR_IN)) == SOCKET_ERROR) {
        std::cout << "Bind Failed" << std::endl;
        return 1;
    }
    if (listen(serverSock, SOMAXCONN) == SOCKET_ERROR) {
        std::cout << "Listen Error" << std::endl;
        return 1;
    }

    std::cout << "Server Start" << std::endl;
    char buffer[BUFFER_SIZE];
    while (true) {
        if (gameList.size() < MAX_GAME) {
            int len = sizeof(SOCKADDR_IN);
            SOCKADDR_IN clientAddr;
            SOCKET clientSock = accept(serverSock, (SOCKADDR*)&clientAddr, &len);
            CLIENT client(clientSock, clientAddr);
            clientList.push_back(client);
            
            for (auto client = clientList.begin(); client < clientList.end(); client++) {
                if (recv(client->first, buffer, BUFFER_SIZE, 0) == SOCKET_ERROR) {
                    closesocket(client->first);
                    clientList.erase(client);
                    continue;
                }
            }

            if (clientList.size() >= 2) {
                for (int i = 0; i < clientList.size() / 2; i++) {
                    CLIENT client1 = clientList.front();
                    clientList.pop_front();
                    CLIENT client2 = clientList.front();
                    clientList.pop_front();

                    Room* room = new Room;
                    room->SetPlayer(client1.first, client1.second, client1.first, client2.second);
                    std::thread* gameThread = new std::thread(StartGame, room, gameThread);

                    GAME game(room, gameThread);
                    gameList.push_back(game);
                }
            }
            if (gameList.front().first->getIsGameEnd()) {
                GAME game = gameList.front();
                gameList.pop_front();
                delete game.first;
                game.second->join();
            }
        }
    }

    while (!gameList.empty()) {
        GAME game = gameList.front();
        gameList.pop_front();
        delete game.first;
        game.second->join();
    }

    closesocket(serverSock);
    WSACleanup();
    return 0;
}