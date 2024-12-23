//
// Created by Correia, Jose Bastos on 04/12/2024.
//

#include "GameManager.h"
#include <iostream>

#include "BarbarianCaravan.h"
#include "Buffer.h"
#include "SecretCaravan.h"

GameManager::GameManager(int coins):
coins(isValidCoins(coins)),
turns(0),
combatsWon(0)
// gameConfig(GameConfigurator())
{
}

GameManager::~GameManager()
{
    // TODO apply game over
}

int GameManager::getCoins() const
{
    return coins;
}

void GameManager::setCoins(int coins)
{
    this->coins = isValidCoins(coins);
}

void GameManager::combat()
{
    // TODO combat
}

void GameManager::checkGameStatus()
{
    // TODO checkgamestatus
}

int GameManager::isValidCoins(int coins) const
{
    return coins > 0 && coins < 99999999 ? coins : 0;
}

void GameManager::setNewItemsCouldown(int cd)
{
    this->newItemsCouldown = cd;
}

void GameManager::setItemDuration(int cd)
{
    this->itemDuration = cd;
}

void GameManager::configGame(string fileName)
{
    //cout << "Fase 1 Iniciada!" << endl;
    // gameConfig.readConfigFile(fileName);
    // gameConfig.displayConfig();
}

void GameManager::buyCaravan(int city, char type)
{
    // FIXME THIS SHOULD BE model.caravanPrice, identifier and crew
    if (coins < 100)
    {
        cout << "Not enough coins to buy that Caravan!" << endl;
        cout << "Current coins: " << coins << endl;
        return;
    }
    if (type != 'C' && type != 'M' && type != 'S')
    {
        cout << "Type " << type << " not recognizable for any Caravan." << endl;
        return;
    }
    if (type == 'C')
        caravans.push_back(new MerchantCaravan(0, 0, '9', 10));
    if (type == 'M')
        caravans.push_back(new BarbarianCaravan(0,0,'!', 5, 5));
    if (type == 'S')
        caravans.push_back(new SecretCaravan(0, 0, '9', 0));
    cout << "Caravan bought in city " << city << " of type " << type << ".\n";

}





