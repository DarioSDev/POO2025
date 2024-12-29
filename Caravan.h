//
// Created by Correia, Jose Bastos on 08/12/2024.
//

#ifndef CARAVAN_H
#define CARAVAN_H

#include <string>
#include <unordered_map>
#include <iostream>
#include "MapContentItem.h"
#include "MoveType.h"

using namespace std;

class Caravan : public MapContentItem {
protected:
    int crew;    // Number of crew members
    const int maxTons;
    int cargo;
    MoveType moveType;

public:
    // Constructor
    Caravan();
    Caravan(int x, int y, char identifier, int crew, int maxTons = 40, MoveType moveType = Manual);

    virtual bool move(int dx, int dy);

    // Get the caravan's name
    char getName();
    int getMaxTons();
    void addCargo(int quantity);
    void removeCargo(int quantity);
    int getCargo();

    // Virtual method to display information (polymorphic behavior)
    virtual void displayInfo();

    // Add crew members
    void addCrew(int count);

    // Remove crew members
    void removeCrew(int count);

    virtual Caravan * duplicate() const;
};

#endif //CARAVAN_H
