//
// Created by Correia, Jose Bastos on 10/12/2024.
//

#ifndef MAPCONTENTITEM_H
#define MAPCONTENTITEM_H
#include <string>
#include <vector>
using namespace std;

class MapContentItem {
    protected:
    int x;
    int y;
    char identifier;
    char type;
public:
    virtual ~MapContentItem() = default;
    MapContentItem(int x, int y, char identifier = 'X', char type = 'X');

    enum MoveDirection
    {
        Top, Right, Bottom, Left
    };

    // TODO FIX MAPA EMISFERICO
    void move(MoveDirection direction);
    char getItemTypeAt(int x, int y, const vector<MapContentItem*>& map);
    char getIdentifier();
    char getType() const;
    int getX() const;
    int getY() const;
};

#endif //MAPCONTENTITEM_H
