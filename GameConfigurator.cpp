//
// Created by Correia, Jose Bastos on 17/12/2024.
//

#include "GameConfigurator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>

#include "BarbarianCaravan.h"
#include "City.h"
#include "Desert.h"
#include "MapContentItem.h"
#include "MerchantCaravan.h"
#include "Mountain.h"

using namespace std;

GameConfigurator::GameConfigurator(GameModel& model) : model(model) {
}

void GameConfigurator::configGame(string fileName)
{
    cout << "Fase 1 Iniciada!" << endl;
    readConfigFile(fileName);
    displayConfig(); // Add a getter in GameConfigurator if necessary
}

// Método para ler configurações do ficheiro
void GameConfigurator::readConfigFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Erro: Não foi possível abrir o ficheiro " << filename << endl;
        return;
    }

    string line;

    // Ler o número de linhas
    if (getline(file, line)) {
        stringstream ss(line);
        string temp;
        ss >> temp >> model.lines;
    }

    // Ler o número de colunas
    if (getline(file, line)) {
        stringstream ss(line);
        string temp;
        ss >> temp >> model.columns;
    }

    // Ler o grid do mapa
    //for (int i = 0; i < gameModel.linhas; ++i) {
    //    if (getline(file, line)) {
//
//
    //        // TODO Criar vector<MapContentItem *> com o devido item;
//
    //        grid.push_back(line);
    //    }
    //}

    //Ler o grid do mapa
    for (int y = 0; y < model.lines; ++y) {
        if (getline(file, line)) {
            for (int x = 0; x < line.size(); ++x) {
                char content = line[x];

                if (content == '.')
                    model.map.push_back(new Desert(x, y));
                else if(content == '+')
                    model.map.push_back(new Mountain(x, y));
                else if(islower(content)) {
                    City* city = new City(x, y, content);
                    model.map.push_back(city);
                    model.cityIdentifiers.push_back(city->getIdentifier());
                }
                else if (isdigit(content)) {
                    model.map.push_back(new Desert(x, y));
                    MapContentItem* caravan = new MerchantCaravan(x, y, content, 10);
                    model.map.push_back(caravan);
                    model.caravanIdentifiers.push_back(caravan->getIdentifier());
                }
                else if (content == '!')
                {
                    model.map.push_back(new Desert(x, y));
                    model.map.push_back(new BarbarianCaravan(x, y, content));
                }

                // TODO FIX crew and AP init above
            }
        }
    }

    // Ler os restantes parâmetros do jogo
    while (getline(file, line)) {
        stringstream ss(line);
        string key;
        int value;
        ss >> key >> value;

        if (key == "moedas") model.coins = value;
        else if (key == "instantes_entre_novos_itens") model.turnsBetweenNewItems = value;
        else if (key == "duração_item") model.itemDuration = value;
        else if (key == "max_itens") model.maxItems = value;
        else if (key == "preço_venda_mercadoria") model.merchSellPrice = value;
        else if (key == "preço_compra_mercadoria") model.merchBuyPrice = value;
        else if (key == "preço_caravana") model.caravanPrice = value;
    }

    file.close();
}

// Método para mostrar as configurações carregadas
void GameConfigurator::displayConfig() const {
    cout << "\n\n";
    cout << "Linhas: " << model.lines << ", Colunas: " << model.columns << "\n";
    for (const auto& row : model.map) {
        cout << row->getIdentifier();
        if (row->getX() == 19)
            cout << "\n";
    }

    cout << "\n" << endl;
    cout << "Moedas: " << model.coins << "\n";
    cout << "Instantes entre novos itens: " << model.turnsBetweenNewItems << "\n";
    cout << "Duracao do item: " << model.itemDuration << "\n";
    cout << "Max itens: " << model.maxItems << "\n";
    cout << "Preco de venda da mercadoria: " << model.merchSellPrice << "\n";
    cout << "Preco de compra da mercadoria: " << model.merchBuyPrice << "\n";
    cout << "Preco da caravana: " << model.caravanPrice << "\n";
    cout << "\n\n";
}
