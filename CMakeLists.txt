cmake_minimum_required(VERSION 3.29)
project(TP)

set(CMAKE_CXX_STANDARD 20)

add_executable(TP main.cpp
        Simulator.cpp
        Simulator.h
        Buffer.cpp
        Buffer.h
        CMD.cpp
        CMD.h
        GameManager.cpp
        GameManager.h
        City.cpp
        City.h
        Caravan.cpp
        Caravan.h
        BarbarianCaravan.cpp
        BarbarianCaravan.h
        MerchantCaravan.cpp
        MerchantCaravan.h
        Mountain.cpp
        Mountain.h
        MapContentItem.cpp
        MapContentItem.h
        GameConfigurator.cpp
        GameConfigurator.h
        GameModel.cpp
        GameModel.h
        Desert.cpp
        Desert.h
        SecretCaravan.cpp
        SecretCaravan.h
        MoveType.cpp
        MoveType.h
        MilitaryCaravan.cpp
        MilitaryCaravan.h
        Item.cpp
        Item.h
)
