//
// Created by Correia, Jose Bastos on 08/12/2024.
//

#ifndef BARBARIANCARAVAN_H
#define BARBARIANCARAVAN_H
#include "Caravan.h"

class BarbarianCaravan final : public Caravan {
    int turnsPlayed = 0;
public:
    // Constructor
    BarbarianCaravan(int x, int y, char identifier);

    // TODO Override displayInfo to show specific details
    void displayInfo() override;

    BarbarianCaravan* duplicate() const override;

    int incTurnsPlayed();
};

#endif //BARBARIANCARAVAN_H