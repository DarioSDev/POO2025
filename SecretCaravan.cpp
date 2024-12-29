//
// Created by Correia, Jose Bastos on 23/12/2024.
//

#include "SecretCaravan.h"

SecretCaravan::SecretCaravan(   int x,
                                int y,
                                char identifier):
                                Caravan(    x,
                                            y,
                                            identifier,
                                            50,
                                            50,
                                            500,
                                            100,
                                            Manual){}

SecretCaravan* SecretCaravan::duplicate() const
{
    return new SecretCaravan(*this);
}
