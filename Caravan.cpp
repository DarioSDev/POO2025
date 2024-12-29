//
// Created by Correia, Jose Bastos on 08/12/2024.
//

#include "Caravan.h"

Caravan::Caravan(): MapContentItem(-1,-1), crew(0), maxTons(0) {};

Caravan::Caravan(   int x,
                    int y,
                    char identifier,
                    int crew,
                    int maxTons)
                    : MapContentItem(   x,
                                        y,
                                        identifier,
                                        'C'),
                                        crew(crew),
                                        maxTons(maxTons), cargo (0){}

// Add goods to the caravan
void Caravan::addCargo(int quantity) {
    cargo += quantity;
}

int Caravan::getCargo() {
    return cargo;
}

int Caravan::getMaxTons() {
    return maxTons;
}

// Remove goods from the caravan
void Caravan::removeCargo(int quantity) {
    if ( cargo < quantity) {
        cout << "Not enough to remove!\n";
        return;
    }
    cargo -= quantity;
}
// FIXME GETNADA AND NAME
// Get the caravan's name
char Caravan::getName() {
    return getIdentifier();
}

// FIXME GETNADA AND NAME
// Display basic information (can be overridden by subclasses)
//void Caravan::displayInfo() const {
//    cout << "Caravan Name: " << name << "\nCrew: " << crew << endl;
//}

// Add crew members
void Caravan::addCrew(int count) {
    crew += count;
}

// Remove crew members
void Caravan::removeCrew(int count) {
    if (count > crew) {
        cout << "Not enough crew to remove!\n";
        return;
    }
    crew -= count;
}

bool Caravan::move(int dx, int dy) {
    x += dx;
    y += dy;
    return true;
}

void Caravan::displayInfo()
{
}

Caravan* Caravan::duplicate() const
{
    return new Caravan(*this);
}