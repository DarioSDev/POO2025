//
// Created by Correia, Jose Bastos on 18/12/2024.
//

#include "Desert.h"


Desert::Desert( int x,
                int y,
                char identifier) :
    MapContentItem(x, y, identifier, 'D')
{
}

Item Desert::getItem()
{
    return item;
}

bool Desert::setItem(Item item)
{
    if (this->item != None)
        return false;
    this->item = item;
}

