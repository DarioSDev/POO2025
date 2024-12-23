//
// Created by Correia, Jose Bastos on 08/12/2024.
//

#ifndef CITY_H
#define CITY_H

#include <vector>
#include <string>
#include "Caravan.h" // Assumes the Caravan class is in a separate file

using namespace std;

class City: public MapContentItem {
    vector<Caravan *> caravans; // List of caravans in the city

public:
    // Constructor
    // identifier of city is lowercase letter
    City(int x, int y, char identifier);

    // Allow a caravan to enter the city
    void addCaravan(Caravan* caravan);

    // Pop Caravan from City
    void removeCaravan(Caravan* caravan);

    // Inspect caravans currently in the city
    void inspect();

    // Get the city's name (identifier)
    char getIdentifier() const;

    // Append Caravan to City
//    void addCaravan(Caravan* caravan);
};

#endif //CITY_H
