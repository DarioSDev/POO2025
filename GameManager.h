//
// Created by Correia, Jose Bastos on 04/12/2024.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
#include <vector>

#include "Caravan.h"
#include "City.h"
#include "GameConfigurator.h"
#include "MerchantCaravan.h"

using namespace std;

class GameManager {
    int coins;
    int turns;
    int combatsWon;
    int newItemsCouldown;
    int itemDuration;
    //GameConfigurator gameConfig;
    enum GameStatus
    {
        Running, Over
    };

    // TODO: vector the mapItemsClass
    vector<Caravan *> caravans;

    int isValidCoins(int coins) const;
public:
    GameManager(int coins = 0);
    ~GameManager();
    void combat();
    void checkGameStatus();
    int getCoins() const;
    void setCoins(int coins);
    void setNewItemsCouldown(int cd);
    void setItemDuration(int cd);
    void configGame(string fileName = "config.txt");
    void buyCaravan(int city, char type);
    Caravan * findCaravan(char id);
    bool moveCaravan(Caravan* caravan, int dx, int dy);
};



#endif //GAMEMANAGER_H
