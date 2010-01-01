//
// Created by venso on 2017/4/28.
//

#include "cmd.h"

int createCmd(struct CarVector carVector) {
    int code = 1;//命令代号
    return ((code << 17) | (carVector.angle << 9) | (carVector.direction << 8) | carVector.speed) << 11;
}

void parseCmd(int cmd, struct CarVector *carVector) {
    cmd = cmd >> 11;
    carVector->speed = cmd & 0xFF;
    carVector->direction = (cmd >> 8) & 1;
    carVector->angle = (cmd >> 9) & 0xFF;

}

int isCmdValid(int cmd) {
    //左移28位末尾是否为1
    int i=(cmd >>28) & 1;
    if (i== 0) {
        return 0;
    }
    cmd = cmd >> 11;
    return (((cmd >> 9) & 0xFF)<=180)&&(((cmd >> 9) & 0xFF)>=0);
}