//
// Created by Correia, Jose Bastos on 23/12/2024.
//

#include "SecretCaravan.h"

SecretCaravan::SecretCaravan(   int x,
                                int y,
                                char identifier,
                                int crew = 0):
                                Caravan(x,
                                        y,
                                        identifier,
                                        crew)
{
}

SecretCaravan* SecretCaravan::duplicate() const
{
    return new SecretCaravan(*this);
}
