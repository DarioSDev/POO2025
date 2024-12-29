//
// Created by Correia, Jose Bastos on 08/12/2024.
//

#include "MerchantCaravan.h"

MerchantCaravan::MerchantCaravan(   int x,
                                    int y,
                                    char identifier,
                                    int crew = 10)
                                    : Caravan(x,
                                        y,
                                        identifier,
                                        crew,
                                        20,
                                        200,
                                        40,
                                        Manual) {}

// FIXME FIX THIS
// Override displayInfo to show details about the merchant caravan
void MerchantCaravan::displayInfo() {
    cout << "Merchant Caravan\n"
         << "Name: " << getName() << "\nCrew: " << crew
         << "\nGoods: " << tons << "\n";

}

MerchantCaravan* MerchantCaravan::duplicate() const
{
    return new MerchantCaravan(*this);
}

bool MerchantCaravan::consumeWater()
{
    if (currentWater <= 0)
        return false;
    if (crew > 10)
        currentWater -= 2;
    else
        currentWater -= 1;
    return true;
}

bool MerchantCaravan::move(int dx, int dy)
{
    if (crew == 0 && turnsWithoutCrew < 5)
    {
        turnsWithoutCrew++;
        dx = (rand() % 3) - 1;
        dy = (rand() % 3) - 1;
        return Caravan::move(dx, dy);
    }
    return Caravan::move(dx, dy);
    
}
