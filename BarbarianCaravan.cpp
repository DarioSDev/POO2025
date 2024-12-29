//
// Created by Correia, Jose Bastos on 08/12/2024.
//

#include "BarbarianCaravan.h"
#include <iostream>

BarbarianCaravan::BarbarianCaravan( int x,
                                    int y,
                                    char identifier)
                                    : Caravan(  x,
                                                y,
                                                identifier,
                                                40,
                                                40,
                                                0,
                                                0,
                                                1,
                                                Manual) {}

// TODO override displayInfo to show barbarian caravan details
void BarbarianCaravan::displayInfo() {
    cout << "Barbarian Caravan\n"
         << "Name: " << getName() << "\nCrew: " << crew << "."<< endl;
}

BarbarianCaravan* BarbarianCaravan::duplicate() const
{
    return new BarbarianCaravan(*this);
}

int BarbarianCaravan::incTurnsPlayed()
{
    cout << "turnsPlayed " << turnsPlayed << endl;
    return ++turnsPlayed;
}
