#pragma comment(lib, "ws2_32")
#pragma warning(disable:4996)
#include <iostream>
#include <utility>
#include <deque>
#include <thread>
#include <WinSock2.h>

#define BUFFERSIZE 1024
#define MAX_GAME 4