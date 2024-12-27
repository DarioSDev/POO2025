//
// Created by Correia, Jose Bastos on 08/12/2024.
//

#include "Caravan.h"

Caravan::Caravan(): MapContentItem(-1,-1), crew(0), maxTons(0) {};

Caravan::Caravan(   int x,
                    int y,
                    char identifier,
                    int crew ,
                    int maxTons)
                    : MapContentItem(   x,
                                        y,
                                        identifier),
                                        crew(crew),
                                        maxTons(maxTons) {}

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

void Caravan::move() {
    // TODO MOVER
}

void Caravan::displayInfo()
{
    // TODO DISPLAY INFO
    cout << "Esta caravana está a mostrar a info\n" << endl;
}

Caravan* Caravan::duplicate() const
{
    return new Caravan(*this);
}