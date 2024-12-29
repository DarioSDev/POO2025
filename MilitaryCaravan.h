//
// Created by Correia, Jose Bastos on 29/12/2024.
//

#ifndef MILITARYCARAVAN_H
#define MILITARYCARAVAN_H
#include "Caravan.h"


class MilitaryCaravan final : public Caravan {
    int turnsWithoutCrew = 0;
public:
    // Constructor
    MilitaryCaravan(int x, int y, char identifier);

    // TODO Override displayInfo to show specific details
    void displayInfo() override;

    MilitaryCaravan* duplicate() const override;

    bool consumeWater() override;

    bool move(int dx, int dy) override;
};

#endif //MILITARYCARAVAN_H
