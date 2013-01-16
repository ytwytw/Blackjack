/*
 Junhua Zhang
 Ryerson University
 Computer Engineering Student
 This is assignment4
 junhua.zhang@ryerson.ca
 */

#ifndef dealer
#define dealer
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

int gamedealer(int dealer);

int dealdealer(int dealer, int clientSockFd);

int gameplayer(int player, int clientSockFd);

int dealplayer(int player, int clientSockFd);

#endif
