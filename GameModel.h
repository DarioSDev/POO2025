//
// Created by Correia, Jose Bastos on 18/12/2024.
//

#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include <vector>
#include "MapContentItem.h"
using namespace std;

class GameModel {
public:
    vector<MapContentItem *> map;
    vector<char> cityIdentifiers;
    vector<int> caravanIdentifiers;
    int lines;
    int columns;
    int coins;
    int turnsBetweenNewItems;
    int itemDuration;
    int maxItems;
    int merchSellPrice;
    int merchBuyPrice;
    int caravanPrice;
    int turnsBetweenNewBarbarians;
    int barbariansDuration;

    GameModel();

    void setLines(int lines)
    {
        this->lines = lines;
    }

    void setColumns(int columns)
    {
        this->columns = columns;
    }

    void setCoins(int coins)
    {
        this->coins = coins;
    }

    void setTurnsBetweenNewItems(int turns_items)
    {
        turnsBetweenNewItems = turns_items;
    }

    void setItemDuration(int duration)
    {
        itemDuration = duration;
    }

    void setMaxItens(int max_items)
    {
        maxItems = max_items;
    }

    void setMerchSellPrice(int merch_sell_price)
    {
        merchSellPrice = merch_sell_price;
    }

    void setMerchBuyPrice(int merch_buy_price)
    {
        merchBuyPrice = merch_buy_price;
    }

    void setCaravanPrice(int caravan_price)
    {
        caravanPrice = caravan_price;
    }

    void setTurnsBetweenNewBarbarians(int turns_barbarians)
    {
        turnsBetweenNewBarbarians = turns_barbarians;
    }

    void setBarbariansDuration(int barbarians_duration)
    {
        barbariansDuration = barbarians_duration;
    }
};

#endif //GAMEMODEL_H
