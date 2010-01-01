//
// Created by BrainWang on 2017-04-28.
//
#include <unistd.h>
#include "ControlServer.h"
#include <stdint.h>
void *server_fun(void *controlServer) {
    int errCount = 5;
    ControlServer *mControlServer = (ControlServer *) controlServer;
    while (errCount > 0 && mControlServer->conn > 0) {
        printf("\n角度：%d，方向：%d，速度：%d\n", mControlServer->mCarVector->angle, mControlServer->mCarVector->direction, mControlServer->mCarVector->speed);
        fflush(stdout);
        int dataToSend = createCmd(*(mControlServer->mCarVector));
        if (send(mControlServer->conn, &dataToSend, sizeof(int), 0) < 0)
            errCount--;
        else
            errCount = 5;
        usleep(200000);
    }
    close(mControlServer->conn);//10次发送失败关闭连接
    printf("10次发送失败关闭连接\n");
}

ControlServer::ControlServer(CarVector *carVector) : mCarVector(carVector) {

}

void ControlServer::start() {
//定义sockfd
    int server_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    //定义sockaddr_in
    struct sockaddr_in server_sockaddr;
    server_sockaddr.sin_family = AF_INET;
    server_sockaddr.sin_port = htons(mPort);
    server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    //bind，成功返回0，出错返回-1
    if (bind(server_sockfd, (struct sockaddr *) &server_sockaddr, sizeof(server_sockaddr)) == -1) {
        perror("bind");
        exit(1);
    }

    //客户端套接字
    while (1) {
        //listen，成功返回0，出错返回-1
        if (listen(server_sockfd, QUEUE) == -1) {
            perror("listen");
            exit(1);
        }
        struct sockaddr_in client_addr;
        socklen_t length = sizeof(client_addr);
        //成功返回非负描述字，出错返回-1
        conn = accept(server_sockfd, (struct sockaddr *) &client_addr, &length);
        if (conn < 0) {
            perror("connect");
            break;
        } else {
            printf("传入连接\n");
            fflush(stdout);
            pthread_t thread_id;
            pthread_create(&thread_id, NULL, server_fun, (void *) this);//客户端传入后发送当前车辆的状态信息

            int32_t recvint;
            while (recv(conn, &recvint, sizeof(int32_t), 0) > 0) {
                if (isCmdValid(recvint)) {
                    parseCmd(recvint, mCarVector);
                }
            }
            close(conn);
            printf("断开连接");
        }


    }

    close(server_sockfd);
}


//void ControlServer::parseCmd(int cmd, struct CarVector *carVector) {
//    cmd = cmd >> 11;
//    carVector->speed = cmd & 0b11111111;
//    carVector->direction = (cmd >> 8) & 1;
//    carVector->angle = (cmd >> 9) & 0b11111111;
//
//}

//int ControlServer::createCmd(struct CarVector carVector) {
//    int code = 1;//命令代号
//    return ((code << 17) | (carVector.angle << 9) | (carVector.direction << 8) | carVector.speed) << 11;
//}