//
// Created by Correia, Jose Bastos on 08/12/2024.
//

#ifndef MERCHANTCARAVAN_H
#define MERCHANTCARAVAN_H
#include "Caravan.h"
#include <map>

class MerchantCaravan final : public Caravan {
    // FIXME create custom type
    int turnsWithoutCrew = 0;

public:
    MerchantCaravan(int x, int y, char identifier, int crew);


    // TODO OVERRIDE
    void displayInfo() override;

    MerchantCaravan* duplicate() const override;

    bool consumeWater() override;

    bool move(int dx, int dy) override;
};



#endif //MERCHANTCARAVAN_H
