//
// Created by Correia, Jose Bastos on 29/12/2024.
//

#include "MilitaryCaravan.h"
#include <iostream>

MilitaryCaravan::MilitaryCaravan(   int x,
                                    int y,
                                    char identifier)
                                    : Caravan(x,
                                        y,
                                        identifier,
                                        20,
                                        40,
                                        400,
                                        5,
                                        Manual) {}

void MilitaryCaravan::displayInfo() {
    cout << "Barbarian Caravan\n"
         << "Name: " << getName() << "\nCrew: " << crew << "."<< endl;
}

MilitaryCaravan* MilitaryCaravan::duplicate() const
{
    return new MilitaryCaravan(*this);
}

void MilitaryCaravan::consumeWater()
{
    if (crew >= 20)
        currentWater -= 3;
    else
        currentWater -= 1;
    if (currentWater < 0) currentWater = 0;
    cout << "MilitaryCaravan consumed water. Remaining: " << currentWater << " units.\n";

}

bool MilitaryCaravan::move(int dx, int dy)
{
    if (movesThisTurn < maxMovesPerTurn) {
        if (crew == 0 && turnsWithoutCrew < 7)
        {
            Caravan::move(1, 1);
            movesThisTurn++;
            turnsWithoutCrew++;
            return true;
        }
        if (moveType == Auto)
        {
            // TODO HUNT BARBARIANS IN 6 POSITIONS DIFERENCE
            movesThisTurn++;
            consumeWater();
            return true;
        }
        if (moveType == Manual)
        {
            if (Caravan::move(dx, dy))
            {
                movesThisTurn++;
                consumeWater();
                return true;
            }
        }
    }
    cout << "No moves left this turn!\n";
    return false;
}

