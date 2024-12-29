//
// Created by Correia, Jose Bastos on 08/12/2024.
//

#ifndef CARAVAN_H
#define CARAVAN_H

#include <string>
#include "MapContentItem.h"
#include "MoveType.h"

using namespace std;

class Caravan : public MapContentItem {
protected:
    int crew;
    int maxCrew{};
    const int maxTons;
    int tons{};
    const int waterCapacity;
    int currentWater{};
    MoveType moveType;

public:
    // Constructor
    Caravan();
    Caravan(int x, int y, char identifier, int crew, int maxCrew, int waterCapacity, int maxTons, MoveType moveType = Manual);

    virtual bool move(int dx, int dy);
    char getName();
    void addTons(int quantity);
    void removeTons(int quantity);
    [[nodiscard]] int getTons() const;
    [[nodiscard]] int getMaxTons() const;
    virtual void displayInfo();
    void addCrew(int count);
    void removeCrew(int count);
    [[nodiscard]] int getCrew() const;
    [[nodiscard]] int getMaxCrew() const;
    [[nodiscard]] virtual Caravan * duplicate() const;
    virtual bool consumeWater();
    bool setMode(MoveType mode);
};

#endif //CARAVAN_H
