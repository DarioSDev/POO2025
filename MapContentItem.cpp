//
// Created by Correia, Jose Bastos on 10/12/2024.
//

#include "MapContentItem.h"

MapContentItem::MapContentItem(int x, int y, char identifier, char type): x(x), y(y), identifier(identifier), type(type) {}

void MapContentItem::move(MoveDirection direction) {
    switch (direction) {
    case Top:    y--; break;
    case Right:  x++; break;
    case Bottom: y++; break;
    case Left:   x--; break;
    }
}

char MapContentItem::getIdentifier()
{
    return identifier;
}

char MapContentItem::getType()
{
    return type;
}

int MapContentItem::getX() const
{
    return x;
}

int MapContentItem::getY() const
{
    return y;
}