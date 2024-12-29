//
// Created by Correia, Jose Bastos on 29/12/2024.
//

#ifndef MILITARYCARAVAN_H
#define MILITARYCARAVAN_H
#include "Caravan.h"


class MilitaryCaravan final : public Caravan {

public:
    // Constructor
    MilitaryCaravan(int x, int y, char identifier);

    // TODO Override displayInfo to show specific details
    void displayInfo() override;

    MilitaryCaravan* duplicate() const override;
};

#endif //MILITARYCARAVAN_H
