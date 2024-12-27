//
// Created by Correia, Jose Bastos on 03/12/2024.
//


#include "Simulator.h"
#include "CMD.h"
#include "GameConfigurator.h"
#include "Mountain.h" // TODO REMOVER
#include <algorithm>

Simulator::Simulator()
    : lines(0), columns(0), screen(lines, columns), manager(GameManager()), model(GameModel()), configurator(model) {
    initialPhase = true;
    turn = 0;
    // setup GameManager;
    setupManager();
    screen = Buffer(lines, columns);
    //makeMap();
}

void Simulator::makeMap() {
    map.clear();
    for (int i = 0; i < lines; i++) {
        string linha(lines, '.');
        map.push_back(linha);
    }
    // TODO POPULAR COM ITEMS DO GAME MANAGER

    //Mountain d = Mountain(10, 20);

    // auto it = d.getDesertPositions();


    // eg de preenchimento
    map[2][3] = '+'; // Montanha
    map[1][4] = 'C'; // Cidade TODO mudar para nums
    //for (auto it : d.getDesertPositions()) {
    //    std::cout << "Primeiro valor: " << it.first << ", Segundo valor: " << it.second << std::endl;
    //    mapa[it.first][it.second] = '+';
    //}
}

void Simulator::show() {
    screen.clear();
    for (int i = 0; i < lines; i++) {
        screen.moveCursor(i, 0);
        screen << map[i].c_str();
    }
    screen.render();
}

void Simulator::execute() {
    string input;

    while (initialPhase == true) {
        cout << "Enter command: ";
        getline(cin, input);
        istringstream ss(input);
        string command;
        ss >> command;

        string filename;

        if (command == "config") {
            if (ss >> filename) {
                configurator.readConfigFile(filename);
                configurator.displayConfig();
                lines = model.lines;
                columns = model.columns;
                initialPhase = false;
            } else {
                cout << "Error: Missing filename after 'config' command.\n";
            }
        }
        else if (command == "sair") {
            cout << "Exiting program.\n";
            exit(0);
        }
        else {
            cout << "Invalid command.\n";
        }
    }

    while (initialPhase == false) {
        cout << "Enter command: ";
        getline(cin, input);
        istringstream ss(input);
        string command;
        ss >> command;

        if (command == "show") {
            show();
        }
        else if (command == "prox") {
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
                turn += num;
            } else if (ss.eof()) {
                turn++;
            } else {
                cout << "Invalid command format. Use: prox <positive number>\n";
            }
        }
        else if (command == "comprac") {
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
        }
        else if (command == "precos") {
            showPrices();
        }
        else if (command == "cidade") {
            char city;
            if (!(ss >> city) || ss.peek() != EOF) {
                cout << "Invalid command format. Use: cidade <city letter>\n";
                continue;
            }
            if (!islower(city)) {
                cout << "Invalid city identifier. Must be a lowercase letter.\n";
                continue;
            }
            auto it = find(model.cityIdentifiers.begin(), model.cityIdentifiers.end(), city);
            if (it == model.cityIdentifiers.end()) {
                cout << "City " << city << " not found.\n";
            } else {
                for (auto* item : model.map) {
                    City* cityObj = dynamic_cast<City*>(item);
                    if (cityObj && cityObj->getIdentifier() == city) {
                        cityObj->inspect();
                        break;
                    }
                }
            }
        }
        else if (command == "caravana") {
            cout << "To be implemented..." << endl;
        }
        else if (command == "vende") {
            cout << "To be implemented..." << endl;
        }
        else if (command == "move") {
            int caravanNumber;
            string direction;

            if (!(ss >> caravanNumber)) {
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

            Caravan *caravan = manager.findCaravan(caravanNumber);
            if (!caravan) {
                cout << "Caravan " << caravanNumber << " not found!\n";
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

            if (manager.moveCaravan(caravan->getIdentifier(), dx, dy)) {
                cout << "Caravan " << caravanNumber << " moved to " << direction << ".\n";
            } else {
                cout << "Caravan " << caravanNumber << " could not move to " << direction <<
                        ". Maybe the destination is not valid?\n";
            }
        }
        else if (command == "auto") {
            cout << "To be implemented..." << endl;
        }
        else if (command == "stop") {
            cout << "To be implemented..." << endl;
        }
        else if (command == "barbaro") {
            cout << "To be implemented..." << endl;
        }
        else if (command == "areia") {
            cout << "To be implemented..." << endl;
        }
        else if (command == "moedas") {
            cout << "To be implemented..." << endl;
        }
        else if (command == "tripul") {
            cout << "To be implemented..." << endl;
        }
        else if (command == "saves") {
            cout << "To be implemented..." << endl;
        }
        else if (command == "loads") {
            cout << "To be implemented..." << endl;
        }
        else if (command == "lists") {
            cout << "To be implemented..." << endl;
        }
        else if (command == "dels") {
            cout << "To be implemented..." << endl;
        }
        else if (command == "terminar") {
            cout << "To be implemented..." << endl;
        }
        else {
            cout << "Invalid command.\n";
        }
    }
}


void Simulator::setupManager() {
    manager.setCoins(model.coins);
    manager.setNewItemsCouldown(model.turnsBetweenNewItems);
    manager.setItemDuration(model.itemDuration);
}

void Simulator::showPrices() {
    cout << "Prices:" << endl;
    cout << "Buy Merch: " << model.merchBuyPrice << endl;
    cout << "Sell Merch: " << model.merchSellPrice << endl;
    cout << "Buy Caravan: " << model.caravanPrice << endl;
}
