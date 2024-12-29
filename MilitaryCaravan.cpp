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