//
// Created by Correia, Jose Bastos on 23/12/2024.
//

#ifndef SECRETCARAVAN_H
#define SECRETCARAVAN_H
#include "Caravan.h"


class SecretCaravan final: public Caravan{

public:
    SecretCaravan(int x, int y, char identifier);

    SecretCaravan* duplicate() const override;
};



#endif //SECRETCARAVAN_H
