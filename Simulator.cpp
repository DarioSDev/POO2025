//
// Created by Correia, Jose Bastos on 03/12/2024.
//

#include "Simulator.h"
#include "CMD.h"
#include "GameConfigurator.h"
#include "Mountain.h" // TODO REMOVER

Simulator::Simulator()
    : lines(0), columns(0), screen(lines, columns), model(GameModel()), configurator(model) {

    const string filename = "config.txt";
    configurator.readConfigFile(filename);
    configurator.displayConfig();
    lines = model.lines;
    columns = model.columns;
    screen = Buffer(lines, columns);
    makeMap();
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
void Simulator::executeCommand(string & cmd)
{
    if (cmd == "show")
    {
        show();
    }
    else if (cmd.rfind("move", 0) == 0) {
        // Lógica para mover a caravana
    }
    else if (cmd == "quit") {
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



/*
void Simulador::executa()
{
    string cmd;
    while (true) {
        cout << "Enter command: ";
        getline(cin, cmd);
        processaComando(cmd);
    }
}
*/

void Simulator::execute() {
    string input;

    // TODO set das configs

    while (true) {
        cout << "Enter command: ";

        getline(cin, input);

        CMD command = stringToCMD(input);
        executeCommand(command);
    }
}
