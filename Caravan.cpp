//
// Created by Correia, Jose Bastos on 08/12/2024.
//

#include "Caravan.h"
#include <iostream>

Caravan::Caravan(): MapContentItem(-1,-1), crew(0), maxTons(0), waterCapacity(200), moveType(Manual) {};

Caravan::Caravan(   int x,
                    int y,
                    char identifier,
                    int crew,
                    int maxCrew,
                    int waterCapacity,
                    int maxTons,
                    int maxMovesPerTurn,
                    MoveType moveType)
                    : MapContentItem(   x,
                                        y,
                                        identifier,
                                        'C'),
                                        crew(crew),
                                        maxCrew(maxCrew),
                                        maxTons(maxTons),
                                        tons (0),
                                        waterCapacity(waterCapacity),
                                        currentWater(waterCapacity),
                                        maxMovesPerTurn(maxMovesPerTurn),
                                        movesThisTurn(0),
                                        moveType(moveType){}

void Caravan::addTons(int quantity) {
    tons += quantity;
}

void Caravan::removeTons(int quantity) {
    if ( tons < quantity) {
        cout << "Not enough to remove!\n";
        return;
    }
    tons -= quantity;
}

int Caravan::getTons() const {
    return tons;
}

int Caravan::getMaxTons() const {
    return maxTons;
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

void Caravan::addCrew(int count) {
    crew += count;
}

void Caravan::removeCrew(int count) {
    if (count > crew) {
        crew = 0;
        return;
    }
    crew -= count;
}

int Caravan::getCrew() const {
    return crew;
}

int Caravan::getMaxCrew() const {
    return maxCrew;
}

bool Caravan::move(int dx, int dy) {
    if (movesThisTurn < maxMovesPerTurn) {
        movesThisTurn++;
        x += dx;
        y += dy;
        cout << "Caravan moved to (" << x << ", " << y << "). Moves left: " << getMovesLeft() << ".\n";
        return true;
    }
    cout << "No moves left this turn!\n";
    return false;
}

void Caravan::displayInfo()
{
}

Caravan* Caravan::duplicate() const
{
    return new Caravan(*this);
}

void Caravan::consumeWater()
{
    currentWater -= 0;
    if (currentWater < 0) currentWater = 0;
}

bool Caravan::setMode(const MoveType mode) {
    if (mode != Manual && mode != Auto) {
        return false;
    }
    moveType = mode;
    return true;
}

int Caravan::getMovesLeft() {
    return maxMovesPerTurn - movesThisTurn;
}

void Caravan::resetTurn() {
    movesThisTurn = 0;
}

