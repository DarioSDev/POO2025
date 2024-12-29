//
// Created by Correia, Jose Bastos on 08/12/2024.
//

#include "MerchantCaravan.h"
#include <iostream>

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
                                        2,
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

void MerchantCaravan::consumeWater()
{
    if (crew > 10)
        currentWater -= 2;
    else
        currentWater -= 1;
    if (currentWater < 0) currentWater = 0;
}

bool MerchantCaravan::move(int dx, int dy)
{
    if (movesThisTurn < maxMovesPerTurn) {
        if (crew == 0 && turnsWithoutCrew < 5)
        {
            movesThisTurn++;
            turnsWithoutCrew++;
            dx = (rand() % 3) - 1;
            dy = (rand() % 3) - 1;
            return Caravan::move(dx, dy);
        }
        movesThisTurn++;
        x += dx;
        y += dy;
        cout << "Caravan moved to (" << x << ", " << y << "). Moves left: " << getMovesLeft() << ".\n";
        return true;
    }
    cout << "No moves left this turn!\n";
    return false;
}
