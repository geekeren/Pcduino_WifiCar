//
// Created by BrainWang on 2017-04-28.
//

#ifndef SERVER_CONTROLSERVER_H
#define SERVER_CONTROLSERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "cmd.h"

#define QUEUE 1

class ControlServer {
private:
    const int mPort = 8880;


public:
    ControlServer(CarVector *);
    void start();
    struct CarVector *mCarVector;
    int conn;
};


#endif //SERVER_CONTROLSERVER_H
