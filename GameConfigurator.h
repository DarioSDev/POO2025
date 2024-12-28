//
// Created by Correia, Jose Bastos on 17/12/2024.
//

#ifndef GAMECONFIG_H
#define GAMECONFIG_H
#include <vector>
#include <string>
#include "GameModel.h"
#include "MapContentItem.h"

using namespace std;

class GameConfigurator {
public:
    // TODO Move to some getter function later
    GameModel& model;
    GameConfigurator(GameModel& model);

    void configGame(string fileName);

    void readConfigFile(const string& filename);

    void displayConfig() const;
};



#endif //GAMECONFIG_H
