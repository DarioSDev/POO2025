//
// Created by Correia, Jose Bastos on 03/12/2024.
//

#ifndef SIMULADOR_H
#define SIMULADOR_H
#include <vector>
#include <iostream>
#include "Buffer.h"
#include "CMD.h"
#include "GameManager.h"

using namespace std;

class Simulator {
    int lines;
    int columns;
    vector<string> map;
    Buffer screen;
    GameManager manager;
    GameModel model;
    GameConfigurator configurator;

public:
    Simulator();

    void makeMap();
    void show();
    void executeCommand(string & cmd);
    void executeCommand(CMD command);
    void execute();
};

#endif //SIMULADOR_H
