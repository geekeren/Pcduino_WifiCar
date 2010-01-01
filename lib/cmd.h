//
// Created by venso on 2017/4/28.
//
#ifdef __cplusplus
extern "C"{

#endif

#include <stdio.h>

struct CarVector{
    int angle;
    int direction;
    int speed;
};
int createCmd(struct CarVector carVector);
void parseCmd(int cmd, struct CarVector *carVector);
int isCmdValid(int cmd);
#ifdef __cplusplus
};
#endif
