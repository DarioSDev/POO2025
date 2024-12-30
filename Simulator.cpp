//
// Created by Correia, Jose Bastos on 03/12/2024.
//


#include "Simulator.h"
#include "GameConfigurator.h"
#include "Mountain.h" // TODO REMOVER
#include <algorithm>
#include <fstream>
#include <cmath>
#include <utility>
#include <ctime>
#include <vector>

#include "BarbarianCaravan.h"
#include "Desert.h"


Simulator::Simulator()
    : lines(0), columns(0), screen(lines, columns), manager(GameManager()), model(GameModel()), configurator(model) {
    initialPhase = true;
    turn = 1;
    setupManager();
}

void Simulator::makeMap() {
    map.clear();
    for (int i = 0; i < lines; i++) {
        string linha(columns, '.');
        map.push_back(linha);
    }
}

void Simulator::show() {
    // TODO need to iterate through something besides configurator.model.map && overrides when caravans and cities
    for (MapContentItem *item: model.map) {
        if (item->getType() == 'D' || item->getType() == 'M')
            map[item->getY()][item->getX()] = item->getIdentifier();
    }

    for (MapContentItem *item: model.map) {
        if (item->getType() == 'C')
            map[item->getY()][item->getX()] = item->getIdentifier();
    }

    for (MapContentItem *item: model.map) {
        if (item->getType() == 'U')
            map[item->getY()][item->getX()] = item->getIdentifier();
    }

    screen.clear();
    for (int i = 0; i < lines; i++) {
        screen.moveCursor(i, 0);
        screen << map[i].c_str();
    }
    screen.render();
    cout << "Turn: " << turn << " | Coins: " << model.coins << endl;
}

void Simulator::execute() {
    srand(static_cast<unsigned int>(time(nullptr)));
    string input;

    while (initialPhase == true) {
        cout << "\nEnter command: ";
        getline(cin, input);
        istringstream ss(input);
        string command;
        ss >> command;

        string filename;

        if (command == "config") {
            if (ss >> filename) {
                ifstream file(filename);
                if (!file.is_open()) {
                    cout << "Error: File '" << filename << "' does not exist or cannot be opened.\n";
                    cout << "Please enter the full 'config' command with a valid filename.";
                } else {
                    configurator.readConfigFile(filename);
                    configurator.displayConfig();
                    lines = model.lines;
                    columns = model.columns;
                    manager.setCoins(model.coins);
                    initialPhase = false;
                    screen = Buffer(lines, columns);
                    populateDesertItems();
                    makeMap();
                }
            } else {
                cout << "Error: Missing filename after 'config' command.\n";
                cout << "Please enter the full 'config' command with a filename: ";
            }
        } else if (command == "sair") {
            cout << "Exiting program.\n";
            exit(0);
        } else {
            cout << "Invalid command.\n";
        }
    }

    while (initialPhase == false) {
        show();

        vector<Caravan*> barbarianCaravans;

        for (auto *item : model.map) {
            if (auto *caravan = dynamic_cast<Caravan *>(item)) {
                if (caravan->getIdentifier() == '!') {
                    barbarianCaravans.push_back(caravan);
                }
            }
        }

        for (auto *item : model.map) {
            if (auto *caravan = dynamic_cast<Caravan *>(item)) {
                if (caravan->getIdentifier() == '!') continue;

                if (isdigit(caravan->getIdentifier())) {
                    int caravanX = caravan->getX();
                    int caravanY = caravan->getY();

                    for (auto *barbarian : barbarianCaravans) {
                        int barbarianX = barbarian->getX();
                        int barbarianY = barbarian->getY();

                        if ((abs(caravanX - barbarianX) == 1 && caravanY == barbarianY) || (abs(caravanY - barbarianY) == 1 && caravanX == barbarianX)) {
                            cout << "Caravan at (" << caravanX << ", " << caravanY
                                  << ") is adjacent to barbarian caravan at ("
                                  << barbarianX << ", " << barbarianY << ")\n";

                            int barbarianChance = rand() % barbarian->getCrew();
                            int userChance = rand() % caravan->getCrew();
                            cout << "User chance: " << userChance << " | crew: " << caravan->getCrew() << endl;
                            cout << "Barbarian chance: " << barbarianChance << " | crew: " << barbarian->getCrew() << endl;
                            if (barbarianChance > userChance) {
                                int loss = ceil(barbarian->getCrew() * 0.2);
                                barbarian->removeCrew(loss);
                                caravan->removeCrew(loss*2);

                            } else {
                                int loss = ceil(caravan->getCrew() * 0.2);
                                caravan->removeCrew(loss);
                                barbarian->removeCrew(loss*2);
                            }
                            if (caravan->getCrew() <= 0) {
                                cout << "Caravan " << caravan->getIdentifier() << " destroyed." << endl;
                            }
                            if (barbarian->getCrew() <= 0) {
                                cout << "Barbarian " << barbarian->getIdentifier() << " destroyed." << endl;
                            }
                        }
                    }
                }
            }
        }

        removeDestroyedCaravans();
        cout << "Enter command: ";
        getline(cin, input);
        istringstream ss(input);
        string command;
        ss >> command;

        if (command == "exec") {
            // TODO REMOVE LATER - JUST FOR TESTING
            cout << "To be implemented." << endl;
        } else if (command == "prox") {
            int num = 0;
            if (ss >> num) {
                if (ss.peek() != EOF) {
                    cout << "Invalid command format. Use: prox <positive integer>\n";
                    continue;
                }
                if (num <= 0) {
                    cout << "Invalid number of turns\n";
                    continue;
                }
                for (auto *item: model.map) {
                    if (auto *caravan = dynamic_cast<Caravan *>(item)) {
                        for (int i = 0; i < num; i++)
                        {
                            if (caravan->getMode() == Auto)
                            {
                                auto [dx, dy] = manager.moveToClosestCaravan(caravan, model.map);
                                caravan->move(dx, dy);
                            }
                            caravan->consumeWater();
                            caravan->resetTurn();
                        }
                    }
                }
                for (int i = 0; i < num; i++)
                {
                    turn ++;
                    checkTurns();
                    cout << "Turn " << turn << " ends!\n\n";
                }
            } else if (ss.eof()) {
                for (auto *item: model.map) {
                    if (auto *caravan = dynamic_cast<Caravan *>(item)) {
                        if (caravan->getMode() == Auto && caravan->getIdentifier() != '!')
                        {
                            auto [dx, dy] = manager.moveToClosestCaravan(caravan, model.map);
                            caravan->move(dx, dy);
                        }
                        if (caravan->getIdentifier() == '!')
                            manager.moveBarbarianCaravans(caravan, model.map, model.lines, model.columns);
                        caravan->consumeWater();
                        caravan->resetTurn();
                    }
                }
                cout << "Turn " << turn << " ends!\n\n";
                turn++;
                checkTurns();
            } else {
                cout << "Invalid command format. Use: prox <positive number>\n";
            }
        } else if (command == "comprac") {
            char city;
            char type;

            ss >> city >> type;

            if (ss.fail() || ss.peek() != EOF) {
                cout << "Invalid command format. Use: comprac <city letter> <type>\n";
                continue;
            }
            if (!isupper(city) || !isalpha(city) || city > 'Z') {
                cout << "City must be a single uppercase letter.\n";
                continue;
            }
            if (type != 'C' && type != 'M' && type != 'S') {
                cout << "Type must be one of: C, M, S (uppercase also)\n";
                continue;
            }
            manager.buyCaravan(city, type);
        } else if (command == "precos") {
            showPrices();
        } else if (command == "cidade") {
            char city;
            if (!(ss >> city) || ss.peek() != EOF) {
                cout << "Invalid command format. Use: cidade <city letter>\n";
                continue;
            }
            if (!islower(city)) {
                cout << "Invalid city identifier. Must be a lowercase letter.\n";
                continue;
            }
            auto it = ranges::find(model.cityIdentifiers.begin(), model.cityIdentifiers.end(), city);
            if (it == model.cityIdentifiers.end()) {
                cout << "City " << city << " not found.\n";
            } else {
                for (auto *item: model.map) {
                    City *cityObj = dynamic_cast<City *>(item);
                    if (cityObj && cityObj->getIdentifier() == city) {
                        cityObj->inspect();
                        break;
                    }
                }
            }
        } else if (command == "caravana") {
            char caravanId;
            if (ss >> caravanId) {
                if (ss.peek() != EOF) {
                    cout << "Error: Extra input after caravan ID. Use: caravana <caravan no.>" << endl;
                } else {
                    auto it = ranges::find(model.caravanIdentifiers.begin(), model.caravanIdentifiers.end(), caravanId);
                    if (it == model.caravanIdentifiers.end()) {
                        cout << "Caravan " << caravanId << " not found.\n";
                    } else {
                        bool caravanFound = false;
                        for (auto *item: model.map) {
                            if (auto *caravan = dynamic_cast<Caravan *>(item)) {
                                if (caravan->getIdentifier() == caravanId) {
                                    caravan->displayInfo();
                                    caravanFound = true;
                                    break;
                                }
                            }
                        }
                        if (!caravanFound) {
                            cout << "Caravan " << caravanId << " not found in the map.\n";
                        }
                    }
                }
            } else {
                cout << "Error: Invalid caravan ID. Use: caravana <caravan no.>\n";
            }
        }
        else if (command == "compra") {
            char caravanId;
            int tons;

            if (!(ss >> caravanId >> tons)) {
                cout << "Invalid command format. Use: compra <caravan no.> <merch tons.>\n";
                continue;
            }
            bool caravanFound = false;
            for (auto *item : model.map) {
                auto *caravan = dynamic_cast<Caravan *>(item);
                if (caravan && caravan->getIdentifier() == caravanId) {
                    caravanFound = true;
                    bool inCity = false;
                    for (auto *cityItem : model.map) {
                        if (cityItem->getType() == 'U') {
                            City *city = dynamic_cast<City *>(cityItem);
                            if (city && city->getX() == caravan->getX() && city->getY() == caravan->getY()) {
                                if (model.coins - (tons * model.merchBuyPrice) >= 0 && (caravan->getMaxTons() - caravan->getTons()) >= tons) {
                                    caravan->addTons(tons);
                                    model.coins -= tons * model.merchBuyPrice;
                                    cout << "Success! Coins: " << model.coins << " | Merch: " << caravan->getTons() << " tons!" << endl;
                                } else {
                                    cout << "Not enough space for merch or coins" << endl;
                                }
                                inCity = true;
                                break;
                            }
                        }
                    }
                    if (!inCity) {
                        cout << "Caravan " << caravanId << " is not in any city.\n";
                    }
                    break;
                }
            }
            if (!caravanFound) {
                cout << "Caravan " << caravanId << " not found.\n";
            }
        }
        else if (command == "vende") {
            char caravanId;

            if (!(ss >> caravanId)) {
                cout << "Invalid command format. Use: vende <caravan no.>\n";
                continue;
            }
            bool caravanFound = false;
            for (auto *item : model.map) {
                auto *caravan = dynamic_cast<Caravan *>(item);
                if (caravan && caravan->getIdentifier() == caravanId) {
                    caravanFound = true;
                    bool inCity = false;
                    for (auto *cityItem : model.map) {
                        if (cityItem->getType() == 'U') {
                            City *city = dynamic_cast<City *>(cityItem);
                            if (city && city->getX() == caravan->getX() && city->getY() == caravan->getY()) {
                                model.coins += caravan->getTons() * model.merchSellPrice;
                                caravan->removeTons(caravan->getTons());
                                cout << "Success! Coins: " << model.coins << " | Merch: " << caravan->getTons() << " tons!" << endl;
                                inCity = true;
                                break;
                            }
                        }
                    }
                    if (!inCity) {
                        cout << "Caravan " << caravanId << " is not in any city.\n";
                    }
                    break;
                }
            }

            if (!caravanFound) {
                cout << "Caravan " << caravanId << " not found.\n";
            }
        } else if (command == "move") {
            char caravanId;
            string direction;

            if (!(ss >> caravanId)) {
                cout << "Invalid move command format. Use: move <caravan no.> <direction>\n";
                continue;
            }

            if (ss.peek() != ' ' && ss.peek() != EOF) {
                cout << "Invalid move command format. Use: move <caravan no.> <direction>\n";
                continue;
            }

            ss >> direction;

            if (direction.empty()) {
                cout << "Direction missing. Use: move <caravan no.> <direction>\n";
                continue;
            }

            if (direction != "D" && direction != "E" && direction != "C" && direction != "B" &&
                direction != "CE" && direction != "CD" && direction != "BE" && direction != "BD") {
                cout << "Invalid direction: " << direction << ". Use: D, E, C, B, CE, CD, BE, BD\n";
                continue;
            }

            int dx = 0, dy = 0;
            if (direction == "D") { dx = 1; } else if (direction == "E") { dx = -1; } else if (
                direction == "C") { dy = -1; } else if (direction == "B") { dy = 1; } else if (direction == "CE") {
                dx = -1;
                dy = -1;
            } else if (direction == "CD") {
                dx = 1;
                dy = -1;
            } else if (direction == "BE") {
                dx = -1;
                dy = 1;
            } else if (direction == "BD") {
                dx = 1;
                dy = 1;
            }

            auto it = ranges::find(model.caravanIdentifiers.begin(), model.caravanIdentifiers.end(), caravanId);
            if (it == model.caravanIdentifiers.end()) {
                cout << "Caravan " << caravanId << " not found.\n";
                continue;
            }

            bool caravanFound = false;
            for (auto *item: model.map) {
                auto *caravan = dynamic_cast<Caravan *>(item);
                if (caravan && caravan->getIdentifier() == caravanId) {
                    if (caravan->getY() == lines - 1 && (direction == "B" || direction == "BE" || direction == "BD")) {
                        dy = -(lines - 1);
                    } else if (caravan->getY() == 0 && (direction == "C" || direction == "CE" || direction == "CD")) {
                        dy = lines - 1;
                    }

                    if (caravan->getX() == columns - 1 && (
                            direction == "D" || direction == "CD" || direction == "BD")) {
                        dx = -(columns - 1);
                    } else if (caravan->getX() == 0 && (direction == "E" || direction == "CE" || direction == "BE")) {
                        dx = columns - 1;
                    }

                    bool canMove = true;
                    int nextX = caravan->getX(), nextY = caravan->getY();
                    if (direction == "B") nextY++;
                    else if (direction == "C") nextY--;
                    else if (direction == "D") nextX++;
                    else if (direction == "E") nextX--;
                    else if (direction == "BE") {
                        nextX--;
                        nextY++;
                    } else if (direction == "BD") {
                        nextX++;
                        nextY++;
                    } else if (direction == "CE") {
                        nextX--;
                        nextY--;
                    } else if (direction == "CD") {
                        nextX++;
                        nextY--;
                    }

                    if (item->getItemTypeAt(nextX, nextY, model.map) == 'M' ||
                        item->getItemTypeAt(nextX, nextY, model.map) == 'C') {
                        cout << "Can't go in that direction: " << direction << "\n";
                        canMove = false;
                    }
                    if (canMove) {
                        manager.moveCaravan(caravan, dx, dy);
                    }
                    caravanFound = true;
                    break;
                }
            }

            if (!caravanFound) {
                cout << "Caravan " << caravanId << " not found in the map.\n";
            }
        } else if (command == "auto") {
            char caravanId;

            if (!(ss >> caravanId)) {
                cout << "Invalid command format. Use: auto <caravan no.>\n";
                continue;
            }
            auto it = ranges::find(model.caravanIdentifiers.begin(), model.caravanIdentifiers.end(), caravanId);
            if (it == model.caravanIdentifiers.end()) {
                cout << "Caravan " << caravanId << " not found.\n";
                continue;
            }

            for (auto *item: model.map) {
                auto *caravan = dynamic_cast<Caravan *>(item);
                if (caravan && caravan->getIdentifier() == caravanId) {
                    if(caravan->setMode(Auto)) {
                        cout << "Caravan " << caravanId << " set to Auto.\n";
                    } else {
                        cout << "Caravan " << caravanId << " could not set to Auto.\n";
                    }
                }
            }
        } else if (command == "stop") {
            char caravanId;

            if (!(ss >> caravanId)) {
                cout << "Invalid command format. Use: stop <caravan no.>\n";
                continue;
            }
            auto it = ranges::find(model.caravanIdentifiers.begin(), model.caravanIdentifiers.end(), caravanId);
            if (it == model.caravanIdentifiers.end()) {
                cout << "Caravan " << caravanId << " not found.\n";
                continue;
            }

            for (auto *item: model.map) {
                auto *caravan = dynamic_cast<Caravan *>(item);
                if (caravan && caravan->getIdentifier() == caravanId) {
                    if(caravan->setMode(Manual)) {
                        cout << "Caravan " << caravanId << " set to Manual.\n";
                    } else {
                        cout << "Caravan " << caravanId << " could not set to Manual.\n";
                    }
                }
            }
        } else if (command == "barbaro") {
            cout << "To be implemented....." << endl;
        } else if (command == "areia") {
            cout << "To be implemented......" << endl;
        } else if (command == "moedas") {
            int amount = 0;
            if (ss >> amount) {
                if (ss.peek() != EOF) {
                    cout << "Invalid command format. Use: moedas <integer amount>\n";
                    continue;
                }
                cout << "Current Coins: " << manager.getCoins() << endl;
                manager.addCoins(amount);
                cout << (amount > 0 ? "Adding " : "Removing ") << amount << " coins.\n";
                cout << "Updated Coins: " << manager.getCoins() << endl;
            } else if (ss.eof()) {
                cout << "Current Coins: " << manager.getCoins() << endl;
            } else {
                cout << "Invalid command format. Use: moedas <integer amount>\n";
            }
        } else if (command == "tripul") {
            char caravanId;
            int crew;

            if (!(ss >> caravanId >> crew)) {
                cout << "Invalid command format. Use: tripul <caravan no.> <crew>\n";
                continue;
            }
            bool caravanFound = false;
            for (auto *item : model.map) {
                auto *caravan = dynamic_cast<Caravan *>(item);
                if (caravan && caravan->getIdentifier() == caravanId) {
                    caravanFound = true;
                    bool inCity = false;
                    for (auto *cityItem : model.map) {
                        if (cityItem->getType() == 'U') {
                            City *city = dynamic_cast<City *>(cityItem);
                            if (city && city->getX() == caravan->getX() && city->getY() == caravan->getY()) {
                                if (model.coins - crew >= 0 && (caravan->getMaxCrew() - caravan->getCrew()) >= crew) {
                                    caravan->addCrew(crew);
                                    model.coins -= crew;
                                    cout << "Success! Coins: " << model.coins << " | Crew: " << caravan->getCrew() << endl;
                                } else {
                                    cout << "Not enough space for crew or coins" << endl;
                                }
                                inCity = true;
                                break;
                            }
                        }
                    }
                    if (!inCity) {
                        cout << "Caravan " << caravanId << " is not in any city.\n";
                    }
                    break;
                }
            }
            if (!caravanFound) {
                cout << "Caravan " << caravanId << " not found.\n";
            }

        } else if (command == "saves") {
            string bufferName;
            if (ss >> bufferName) {
                if (ss.peek() != EOF) {
                    cout << "Invalid command format. Use: saves <bufferName>\n";
                    continue;
                }
                // FIXME DONT ERASE
                //screen.setName(bufferName.data());

                if ( manager.addMemoryBuffer(screen) )
                    cout << "Current Buffer saved with name '" << bufferName << "'." << endl;
                else
                    cout << "There's already a Buffer with the name '" << bufferName << "', try again!" << endl;

            } else {
                cout << "Invalid command format. Use: saves <bufferName>\n";
            }

        } else if (command == "loads") {
            string bufferName;
            if (ss >> bufferName) {
                if (ss.peek() != EOF) {
                    cout << "Invalid command format. Use: loads <bufferName>\n";
                    continue;
                }
                // FIXME DONT ERASE
                //screen.setName(bufferName.data());

                if ( !manager.displayBuffer(bufferName) )
                    cout << "Buffer with the name '" << bufferName << "' NOT FOUND, try again!" << endl;

            } else {
                cout << "Invalid command format. Use: loads <bufferName>\n";
            }
        } else if (command == "lists") {
            manager.listBuffers();
        } else if (command == "dels") {
            string bufferName;
            if (ss >> bufferName) {
                if (ss.peek() != EOF) {
                    cout << "Invalid command format. Use: dels <bufferName>\n";
                    continue;
                }
                // FIXME DONT ERASE
                //screen.setName(bufferName.data());

                if ( manager.removeMemoryBuffer(bufferName) )
                    cout << "Buffer with name '" << bufferName << "' successfully deleted." << endl;
                else
                    cout << "Buffer with the name '" << bufferName << "' NOT FOUND, try again!" << endl;

            } else {
                cout << "Invalid command format. Use: dels <bufferName>\n";
            }
        } else if (command == "terminar") {
            cout << "Simulation Over!" << model.coins << endl;
            cout << "Turns: " << turn << " | Coins: " << model.coins << endl;
            initialPhase = true;
        } else {
            cout << "Invalid command.\n";
        }
    }
}


void Simulator::setupManager() {
    manager.setCoins(model.coins);
    manager.setNewItemsCouldown(model.turnsBetweenNewItems);
    manager.setItemDuration(model.itemDuration);
}

void Simulator::showPrices() const {
    cout << "Prices:" << endl;
    cout << "Buy Merch: " << model.merchBuyPrice << endl;
    cout << "Sell Merch: " << model.merchSellPrice << endl;
    cout << "Buy Caravan: " << model.caravanPrice << endl;
}

void Simulator::checkTurns()
{
    vector<MapContentItem *>::iterator it = model.map.begin();
    while (it != model.map.end())
    {
        if (auto* barbarianCaravan = dynamic_cast<BarbarianCaravan *>(*it))
        {
            if (barbarianCaravan->incTurnsPlayed() % model.barbariansDuration == 0)
            {
                cout << "Barbarian Carvan deleted at [" << barbarianCaravan->getX() << "][" << barbarianCaravan->getY() << "]" << endl;

                it = model.map.erase(it);
                continue;
            }
        }
        ++it;
    }

    if (turn % model.turnsBetweenNewBarbarians == 0)
    {
        vector<Desert*> deserts;
        for (auto* item : model.map) {
            if (auto* desert = dynamic_cast<Desert*>(item)) {
                deserts.push_back(desert);
            }
        }

        if (!deserts.empty()) {
            bool seeded = false;
            if (!seeded) {
                srand(static_cast<unsigned>(time(0)));
                seeded = true;
            }

            int randomIndex = rand() % deserts.size();

            model.map.push_back(new BarbarianCaravan(   deserts[randomIndex]->getX(),
                                                        deserts[randomIndex]->getY(), '!'));

            cout << "A new Barbarian Caravan appears! t (" << deserts[randomIndex]->getX() << ", " << deserts[randomIndex]->getY() << ")\n";
        } else {
            cout << "No deserts available to spawn a Barbarian Caravan.\n";
        }
    }

    if (turn % model.turnsBetweenNewItems == 0)
    {
        populateDesertItems();
    }
}


void Simulator::populateDesertItems()
{
    vector<Desert*> deserts;

    for (auto* item : model.map)
    {
        if (auto* desert = dynamic_cast<Desert*>(item))
        {
            desert->setItem(None);
            deserts.push_back(desert);
        }
    }

    random_device rd;
    default_random_engine rng(rd());
    shuffle(deserts.begin(), deserts.end(), rng);

    int itemsToAssign = std::min(model.maxItems, static_cast<int>(deserts.size()));
    for (int i = 0; i < itemsToAssign; ++i)
    {
        Item randItem = randomItem();
        deserts[i]->setItem(randItem);

        cout << "Assigned " << itemTypeToString(randItem)
             << " to desert at (" << deserts[i]->getX() << ", " << deserts[i]->getY() << ")\n";
    }
}

void Simulator::removeDestroyedCaravans()
{
    vector<MapContentItem *>::iterator it = model.map.begin();
    while (it != model.map.end())
    {
        if (auto* caravan = dynamic_cast<Caravan *>(*it))
        {
            if (caravan->getCrew() <= 0)
            {
                it = model.map.erase(it);
                continue;
            }
        }
        ++it;
    }
}
