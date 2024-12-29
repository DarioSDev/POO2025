//
// Created by Correia, Jose Bastos on 18/12/2024.
//

#ifndef DESERT_H
#define DESERT_H
#include "Caravan.h"
#include "Item.h"
#include "MapContentItem.h"

class Desert final : public MapContentItem {
    Item item = None;
public:
    Desert( int x,
            int y,
            char identifier = '.');

    Item getItem();
    bool setItem(Item item);
};

#endif //DESERT_H
