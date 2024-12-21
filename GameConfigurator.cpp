//
// Created by Correia, Jose Bastos on 17/12/2024.
//

#include "GameConfigurator.h"
#include <iostream>
#include <fstream>
#include <sstream>

#include "MapContentItem.h"
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
        ss >> temp >> model.linhas; // Ler "linhas" e o valor correspondente
    }

    // Ler o número de colunas
    if (getline(file, line)) {
        stringstream ss(line);
        string temp;
        ss >> temp >> model.colunas; // Ler "colunas" e o valor correspondente
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
    for (int y = 0; y < model.linhas; ++y) {
        if (getline(file, line)) {
            for (int x = 0; x < line.size(); ++x) {
                char conteudo = line[x];

                if(conteudo == '+')
                    model.mapa.push_back(new Mountain(x, y, conteudo));
                // TODO IF conteudo == '.' -> Deserto() e para os outros characters
                // TODO Mudar este push back para uma funçao interna, tipo > void addMapContent( MapContentItem * )
                else
                    model.mapa.push_back(new MapContentItem(x, y, conteudo));
            }
        }
    }

    // Ler os restantes parâmetros do jogo
    while (getline(file, line)) {
        stringstream ss(line);
        string key;
        int value;
        ss >> key >> value;

        if (key == "moedas") model.moedas = value;
        else if (key == "instantes_entre_novos_itens") model.instantesEntreNovosItems = value;
        else if (key == "duração_item") model.duracaoItem = value;
        else if (key == "max_itens") model.maxItens = value;
        else if (key == "preço_venda_mercadoria") model.precoVendaMercadoria = value;
        else if (key == "preço_compra_mercadoria") model.precoCompraMercadoria = value;
        else if (key == "preço_caravana") model.precoCaravana = value;
    }

    file.close();
    cout << "After reading: linhas = " << model.linhas << ", colunas = " << model.colunas << endl;

    printf("Configurator model address: %p\n", (void*)&model);
}

// Método para mostrar as configurações carregadas
void GameConfigurator::displayConfig() const {
    cout << "\n\n";
    cout << "Linhas: " << model.linhas << ", Colunas: " << model.colunas << "\n";
    for (const auto& row : model.mapa) {
        cout << row->getIdentifier();
        if (row->getX() == 19)
            cout << "\n";
    }

    cout << "\n" << endl;
    cout << "Moedas: " << model.moedas << "\n";
    cout << "Instantes entre novos itens: " << model.instantesEntreNovosItems << "\n";
    cout << "Duracao do item: " << model.duracaoItem << "\n";
    cout << "Max itens: " << model.maxItens << "\n";
    cout << "Preco de venda da mercadoria: " << model.precoVendaMercadoria << "\n";
    cout << "Preco de compra da mercadoria: " << model.precoCompraMercadoria << "\n";
    cout << "Preco da caravana: " << model.precoCaravana << "\n";
    cout << "\n\n";
}
