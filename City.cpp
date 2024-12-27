//
// Created by Correia, Jose Bastos on 08/12/2024.
//

#include "City.h"
#include <iostream>
#include <algorithm>

using namespace std;

City::City(int x, int y, char identifier)
    : MapContentItem(x, y, identifier), identifier(identifier) {}

// Allow a caravan to enter the city
void City::addCaravan(Caravan* caravan) {
    caravans.push_back(caravan);
    cout << "Caravan " << caravan->getIdentifier() << " has entered the city " << MapContentItem::getIdentifier() << ".\n";
}

// Pop Caravan from City
void City::removeCaravan(Caravan * caravan) {

    vector<Caravan *>::iterator it = find(  caravans.begin(),
                                            caravans.end(),
                                            caravan);

    if (it != caravans.end()) {
        caravans.erase(it);
        cout << "Caravan " << caravan->getIdentifier() << " has left removed the city " << MapContentItem::getIdentifier() << ".\n";
    } else {
        cout << "Caravan " << caravan->getIdentifier() << " is not in the city " << MapContentItem::getIdentifier() << ".\n";
    }
}

// Inspect caravans currently in the city
void City::inspect() {
    if (caravans.empty()) {
        cout << "No caravans in the city " << MapContentItem::getIdentifier() << ".\n";
    } else {
        cout << "Caravans in the city " << MapContentItem::getIdentifier() << ":\n";
        for (const auto& caravan : caravans) {
            caravan->displayInfo();
        }
    }
}

char City::getIdentifier() const {
    return identifier;
}
