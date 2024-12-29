//
// Created by Correia, Jose Bastos on 08/12/2024.
//

#ifndef MERCHANTCARAVAN_H
#define MERCHANTCARAVAN_H
#include "Caravan.h"
#include <map>

class MerchantCaravan final : public Caravan {
    // FIXME create custom type


public:
    MerchantCaravan(int x, int y, char identifier, int crew);


    // TODO OVERRIDE
    void displayInfo() override;

    MerchantCaravan* duplicate() const override;
};



#endif //MERCHANTCARAVAN_H
