//
// Created by Correia, Jose Bastos on 08/12/2024.
//

#include "MerchantCaravan.h"

MerchantCaravan::MerchantCaravan(   int x,
                                    int y,
                                    char identifier,
                                    int crew)
                                    : Caravan(x, y, identifier, crew) {}

// FIXME FIX THIS
// Override displayInfo to show details about the merchant caravan
void MerchantCaravan::displayInfo() {
    cout << "Merchant Caravan\n"
         << "Name: " << getName() << "\nCrew: " << crew
         << "\nGoods: " << cargo << "\n";

}

MerchantCaravan* MerchantCaravan::duplicate() const
{
    return new MerchantCaravan(*this);
}
