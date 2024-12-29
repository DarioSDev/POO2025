//
// Created by Correia, Jose Bastos on 29/12/2024.
//

#include "Item.h"

#include <cstdlib>
#include <ctime>

// Function to convert ItemType to a string
string itemTypeToString(Item item) {
    switch (item) {
    case PandoraBox:     return "Pandora Box";
    case TreasureChest: return "Treasure Chest";
    case Cage:          return "Cage";
    case Mine:          return "Mine";
    case Surprise:      return "Surprise";
    case None:           return "NoItem";
    default:                      return "Unknown";
    }
}

// Function to generate a random ItemType
Item randomItem() {
    // Seed the random number generator if necessary
    static bool isSeeded = false;
    if (!isSeeded) {
        srand(static_cast<unsigned>(time(0)));
        isSeeded = true;
    }

    // Generate a random number between 0 and 4 and cast it to ItemType
    int randomValue = rand() % 5;
    return static_cast<Item>(randomValue);
}
