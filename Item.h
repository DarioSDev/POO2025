//
// Created by Correia, Jose Bastos on 29/12/2024.
//

#ifndef ITEM_H
#define ITEM_H
#include <string>


using namespace std;

enum Item {
    PandoraBox,       // Reduces caravan crew
    TreasureChest,    // Increases user's coins
    Cage,             // Increases caravan crew
    Mine,             // Destroys the caravan
    Surprise,          // Defined by the user
    None
};

string itemTypeToString(Item type);

// Generates a random ItemType
Item randomItem();


#endif // ITEM_H
