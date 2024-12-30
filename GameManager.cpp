//
// Created by Correia, Jose Bastos on 04/12/2024.
//

#include "GameManager.h"
#include <iostream>

#include "BarbarianCaravan.h"
#include "Buffer.h"
#include "MilitaryCaravan.h"
#include "Mountain.h"
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

void GameManager::addCoins(int coins)
{
    this->coins += coins;
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
        caravans.push_back(new BarbarianCaravan(0, 0, '!'));
    if (type == 'S')
        caravans.push_back(new SecretCaravan(0, 0, '9'));
    cout << "Caravan bought in city " << city << " of type " << type << ".\n";

}

Caravan * GameManager::findCaravan(char id)
{
    for (Caravan * c: caravans)
    {
        printf("-----> %c", c->getIdentifier());
        if (c->getIdentifier() == id)
        {
            return c;
        }
    }
    return nullptr;
}

bool GameManager::moveCaravan(Caravan* caravan, int dx, int dy)
{
    if(caravan->move(dx, dy)) {
        return true;
    }
    return false;
}

bool GameManager::addMemoryBuffer(Buffer buffer) {
    //if (memoryBuffers.contains(buffer.getName())) {
    //    return false;
    //}

    // FIXME DONT ERASE
    //memoryBuffers[buffer.getName()] = buffer;
    return true;
}

bool GameManager::removeMemoryBuffer(string name) {
    auto it = memoryBuffers.find(name);

    if (it != memoryBuffers.end()) {
        memoryBuffers.erase(it);
        return true;
    }

    return false;
}

bool GameManager::displayBuffer(string name)
{
    auto it = memoryBuffers.find(name);

    if (it != memoryBuffers.end()) {
        it->second.render();
        return true;
    }

    return false;
}

pair<int, int> GameManager::moveToClosestCaravan(Caravan* caravan, const vector<MapContentItem*>& map) {
    const int caravanX = caravan->getX();
    const int caravanY = caravan->getY();
    int range = 6;
    int minRange = 1;
    pair direction = {0, 0};

    for (auto* item : map) {
        Caravan* target = nullptr;
        if (auto* merchant = dynamic_cast<MerchantCaravan*>(item)) {
            target = merchant;
        } else if (auto* military = dynamic_cast<MilitaryCaravan*>(item)) {
            target = military;
        }
        if (target && target->getIdentifier() != caravan->getIdentifier()) {
            int targetX = target->getX();
            int targetY = target->getY();

            int distance = abs(caravanX - targetX) + abs(caravanY - targetY);
            if (distance < range && distance > minRange) {
                range = distance;
                if (caravanX < targetX) direction = {1, 0};
                else if (caravanX > targetX) direction = {-1, 0};
                else if (caravanY < targetY) direction = {0, 1};
                else if (caravanY > targetY) direction = {0, -1};
            }
        }
    }
    return direction;
}

void GameManager::moveBarbarianCaravans(Caravan * caravan, vector<MapContentItem*>& map, int lines, int cols)
{
    if (auto* barbarianCaravan = dynamic_cast<BarbarianCaravan*>(caravan))
    {
        int caravanX = barbarianCaravan->getX();
        int caravanY = barbarianCaravan->getY();

        Caravan* target = nullptr;
        int closestDistance = 8;

        for (auto* item : map)
        {
            if (auto* userCaravan = dynamic_cast<Caravan*>(item))
            {
                if (userCaravan->getIdentifier() == '!')
                    continue;
                int userX = userCaravan->getX();
                int userY = userCaravan->getY();

                int distance = abs(caravanX - userX) + abs(caravanY - userY);
                if (distance <= closestDistance)
                {
                    closestDistance = distance;
                    target = userCaravan;
                }
            }
        }

        // Movimento: perseguir ou aleatório
        if (target)
        {
            int targetX = target->getX();
            int targetY = target->getY();

            int dx = 0, dy = 0;

            if (caravanX < targetX) dx = 1;
            else if (caravanX > targetX) dx = -1;

            if (caravanY < targetY) dy = 1;
            else if (caravanY > targetY) dy = -1;

            barbarianCaravan->move(dx, dy);
        }
        else
        {
            int dx = 0, dy = 0;
            while (true)
            {
                dx = 0, dy = 0;
                if (rand() % 2 == 0)
                    dx = rand() % 3 - 1;
                else
                    dy = rand() % 3 - 1;

                bool validMove = true;
                for (auto* item : map)
                {
                    if (item->getX() == dx && item->getY() == dy)
                    {
                        if (dynamic_cast<Mountain*>(item) || dynamic_cast<City*>(item)|| barbarianCaravan->getX() + dx > cols || barbarianCaravan->getY() + dy > lines || dx == 0 || dy == 0)
                        {
                            validMove = false;
                            break;
                        }

                    }
                }
                if (validMove)
                {
                    break;
                }
            }
            barbarianCaravan->move(dx, dy);
        }
    }
}



