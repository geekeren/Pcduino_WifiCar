//
// Created by BrainWang on 2017-04-28.
//
#include "ControlServer.h"
struct CarVector* carVectorPointer = new CarVector;

int main() {
//    struct CarVector carVector{0,0,0};
    carVectorPointer->speed = 100;
    carVectorPointer->angle = 100;
    carVectorPointer->direction = 1;
    ControlServer server(carVectorPointer);
    server.start();
    while(true);
}

