//
// Created by Correia, Jose Bastos on 03/12/2024.
//

#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <sstream>
#include <vector>
#include <iostream>
#include "Buffer.h"
#include "CMD.h"
#include "GameManager.h"

using namespace std;

class Simulator {
    int lines;
    int columns;
    int turn;
    vector<string> map;
    Buffer screen;
    GameManager manager;
    GameModel model;
    GameConfigurator configurator;
    bool initialPhase;
public:
    Simulator();
    void makeMap();
    void show();
    Caravan findCaravan(int caravan_number);
    bool moveCaravan(Caravan caravan, int dx, int dy);
    void showPrices() const;
    void executeCommand(string cmd);
    void execute();
    void setupManager();
};

#endif //SIMULADOR_H
