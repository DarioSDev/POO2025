//
// Created by Correia, Jose Bastos on 08/12/2024.
//

#ifndef BARBARIANCARAVAN_H
#define BARBARIANCARAVAN_H
#include "Caravan.h"

class BarbarianCaravan final : public Caravan {

public:
    // Constructor
    BarbarianCaravan(int x, int y, char identifier);

    // TODO Override displayInfo to show specific details
    void displayInfo() override;

    BarbarianCaravan* duplicate() const override;
};




#endif //BARBARIANCARAVAN_H
