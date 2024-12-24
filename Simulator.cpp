//
// Created by Correia, Jose Bastos on 03/12/2024.
//


#include "Simulator.h"
#include "CMD.h"
#include "GameConfigurator.h"
#include "Mountain.h" // TODO REMOVER

Simulator::Simulator()
    : lines(0), columns(0), screen(lines, columns), manager(GameManager()), model(GameModel()), configurator(model) {

    const string filename = "config.txt";
    configurator.readConfigFile(filename);
    configurator.displayConfig();
    lines = model.lines;
    columns = model.columns;
    turn = 0;
    // setup GameManager;
    setupManager();
    screen = Buffer(lines, columns);
    //makeMap();
}

void Simulator::makeMap()
{
    map.clear();
    for(int i = 0; i < lines; i++)
    {
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

void Simulator::show()
{
    screen.clear();
    for(int i = 0; i < lines; i++)
    {
        screen.moveCursor(i, 0);
        screen << map[i].c_str();
    }
    screen.render();
}

// FIXME NOT IN USE
void Simulator::executeCommand(string cmd)
{
    if (cmd == "show")
    {
        show();
    }
    else if (cmd.rfind("move", 0) == 0) {
        istringstream iss(cmd);
        string moveCmd, direction;
        int caravanNumber;

        // Parse the command
        if (!(iss >> moveCmd >> caravanNumber >> direction)) {
            cout << "Invalid move command format. Use: move <N> <X>\n";
            return;
        }

        // Find the caravan by number
        Caravan* caravan = findCaravan(caravanNumber);
        if (!caravan) {
            cout << "Caravan " << caravanNumber << " not found!\n";
            return;
        }

        // Move the caravan based on the direction
        int dx = 0, dy = 0;
        if (direction == "D")      { dx = 1;  }
        else if (direction == "E") { dx = -1; }
        else if (direction == "C") { dy = -1; }
        else if (direction == "B") { dy = 1;  }
        else if (direction == "CE"){ dx = -1; dy = -1; }
        else if (direction == "CD"){ dx = 1;  dy = -1; }
        else if (direction == "BE"){ dx = -1; dy = 1;  }
        else if (direction == "BD"){ dx = 1;  dy = 1;  }
        else {
            cout << "Invalid direction: " << direction << ". Use: D, E, C, B, CE, CD, BE, BD\n";
            return;
        }

        // Try to move the caravan
        if (moveCaravan(caravan, dx, dy)) {
            cout << "Caravan " << caravanNumber << " moved to " << direction << ".\n";
        } else {
            cout << "Caravan " << caravanNumber << " could not move to " << direction << ". Maybe the destination is not valid?\n";
        }
    }
    else if (cmd == "sair") {
        cout << "Exiting simulation.\n";
        exit(0);
    } else {
        cout << "Unknown command: " << cmd << '\n';
    }
}


void Simulator::executeCommand(CMD command) {
    switch (command) {
    case Play:
        show();
        break;
    case Move:
        // TODO: Lógica para mover caravana
            cout << "Executing move command.\n";
        break;
    case Quit:
        cout << "Exiting SIM.\n";
        exit(0);
        break;
    default:
        cout << "Unknown CMD.\n";
        break;
    }
}

void Simulator::execute() {
    string input;

    // TODO set das configs

    while (true) {
        cout << "Enter command: ";

        getline(cin, input);

        istringstream ss(input);
        string command;
        ss >> command;

        if (command == "comprac") {
            int city;
            char type;
            ss >> city >> type;
            manager.buyCaravan(city, type);
        }




        //cout << "CMD " << cmd << " PARAMS " << params << endl;

        //executCommand("");






        //CMD command = stringToCMD(input);
        //executeCommand(command);
    }
}

void Simulator::setupManager()
{
    manager.setCoins(model.coins);
    manager.setNewItemsCouldown(model.turnsBetweenNewItems);
    manager.setItemDuration(model.itemDuration);
}
