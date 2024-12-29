//
// Created by Correia, Jose Bastos on 29/12/2024.
//

#include "MilitaryCaravan.h"

MilitaryCaravan::MilitaryCaravan( int x,
                                    int y,
                                    char identifier)
                                    : Caravan(x,
                                        y,
                                        identifier,
                                        40,
                                        400,
                                        5,
                                        Auto) {}

// TODO override displayInfo to show barbarian caravan details
void MilitaryCaravan::displayInfo() {
    cout << "Barbarian Caravan\n"
         << "Name: " << getName() << "\nCrew: " << crew << "."<< endl;
}

MilitaryCaravan* MilitaryCaravan::duplicate() const
{
    return new MilitaryCaravan(*this);
}

bool MilitaryCaravan::consumeWater()
{
    if (currentWater <= 0)
        return false;
    if (crew >= 20)
        currentWater -= 3;
    else
        currentWater -= 1;
    return true;
}
