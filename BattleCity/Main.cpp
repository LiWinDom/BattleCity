#define NETWORK_PORT 61000
#define DEBUG false

#include <iostream>
#include <algorithm>
#include <vector>
#include <SFML/Graphics.hpp>
//#include <SFML/Network.hpp>
#include <Windows.h>

#include "Tank.h"
#include "Block.h"
#include "Stages.cpp"

sf::Clock globalClock;

bool inFocus = true;

//sf::UdpSocket connection;
//std::string connectedIP = "";
//bool client = false;

std::vector<std::vector<Block*>> map(26, std::vector<Block*>(26, nullptr));
uint8_t stage = 1;

Tank tank(TANK_YELLOW, 72, 200);

void eventProcess(sf::RenderWindow& window) {
    sf::Event event;
    static float holdTime = globalClock.getElapsedTime().asSeconds();

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            /*if (client) {
                char data[1] = { '_' };
                connection.send(data, 1, connectedIP, NETWORK_PORT);
            }*/
            window.close();
            return;
        }
        else if (event.type == sf::Event::LostFocus) {
            inFocus = false;
        }
        else if (event.type == sf::Event::GainedFocus) {
            inFocus = true;
            holdTime = globalClock.getElapsedTime().asSeconds();
        }
    }
    if (inFocus) {
        while (globalClock.getElapsedTime().asSeconds() >= holdTime + 1 / tank.speed) {
            holdTime += 1 / tank.speed;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                tank.up(map);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                tank.left(map);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                tank.down(map);
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                tank.right(map);
            }
            else {
                holdTime = globalClock.getElapsedTime().asSeconds();
            }
        }
    }
    return;
}

//void networkEvent() {
//    std::size_t received;
//    sf::IpAddress sender;
//    uint16_t port;
//    char data[8];
//    while (connection.receive(data, 8, received, sender, port) != sf::Socket::NotReady) {
//        if (connectedIP == "" && data[0] == 't' && data[1] == 'a' && data[2] == 'n' && data[3] == 'k' && data[4] == 's') {
//            connectedIP = sender.toString();
//        }
//        if (sender.toString() == connectedIP) {
//            if (client) {
//                tank.set(data[0], data[1], data[2], data[3]);
//                tank2.set(data[4], data[5], data[6], data[7]);
//            }
//            else {
//                static float holdTime = globalClock.getElapsedTime().asSeconds();
//                if (data[0] == 'W') {
//                    while (globalClock.getElapsedTime().asSeconds() >= holdTime + 1 / tank.speed) {
//                        tank2.up(tank);
//                        holdTime += 1 / tank.speed;
//                    }
//                }
//                else if (data[0] == 'A') {
//                    while (globalClock.getElapsedTime().asSeconds() >= holdTime + 1 / tank.speed) {
//                        tank2.left(tank);
//                        holdTime += 1 / tank.speed;
//                    }
//                }
//                else if (data[0] == 'S') {
//                    while (globalClock.getElapsedTime().asSeconds() >= holdTime + 1 / tank.speed) {
//                        tank2.down(tank);
//                        holdTime += 1 / tank.speed;
//                    }
//                }
//                else if (data[0] == 'D') {
//                    while (globalClock.getElapsedTime().asSeconds() >= holdTime + 1 / tank.speed) {
//                        tank2.right(tank);
//                        holdTime += 1 / tank.speed;
//                    }
//                }
//                else if (data[0] == '_') {
//                    connectedIP = "";
//                }
//                else {
//                    holdTime = globalClock.getElapsedTime().asSeconds();
//                }
//            }
//        }
//    }
//
//    if (!client) {
//        char data[8] = {tank.x, tank.y, tank.rotation, tank.animation, tank2.x, tank2.y, tank2.rotation, tank2.animation};
//        if (connection.send(data, 8, connectedIP, NETWORK_PORT) != sf::Socket::Done) {
//            ShowWindow(GetConsoleWindow(), SW_SHOW);
//            system("pause");
//            throw 1;
//        }
//    }
//    return;
//}

void display(sf::RenderWindow& window) {
    window.clear(sf::Color(0));

    tank.draw(window);

    for (uint8_t i = 0; i < 26; ++i) {
        for (uint8_t j = 0; j < 26; ++j) {
            map[i][j]->draw(window);
        }
    }

    window.display();
}

int main() {
    /*if (connection.bind(NETWORK_PORT) != sf::Socket::Done) {
        std::cout << "(2 games opened?)" << std::endl;
        system("pause");
        throw 1;
    }
    connection.setBlocking(false);

    std::cout << "Enter IP to connect (none for 1 player / host): ";
    if (std::cin.peek() != '\n') {
        std::cin >> connectedIP;
        client = true;

        char data[5] = { 't', 'a', 'n', 'k', 's' };
        connection.send(data, 5, connectedIP, NETWORK_PORT);
    }*/

    #if !DEBUG
        ShowWindow(GetConsoleWindow(), SW_HIDE);
    #endif

    sf::RenderWindow window(sf::VideoMode(832, 832), "Battle City [0.11]", sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    window.setActive(true);

    for (uint8_t i = 0; i < 26; ++i) {
        for (uint8_t j = 0; j < 26; ++j) {
            if (stages[stage][i][j] == ' ') {
                map[i][j] = new Block(BLOCK_AIR, j, i);
            }
            else if (stages[stage][i][j] == 'b') {
                map[i][j] = new Block(BLOCK_BRICK, j, i);
            }
            else if (stages[stage][i][j] == 'w') {
                map[i][j] = new Block(BLOCK_WALL, j, i);
            }
            else if (stages[stage][i][j] == 'B') {
                map[i][j] = new Block(BLOCK_BUSH, j, i);
            }
            else if (stages[stage][i][j] == 'i') {
                map[i][j] = new Block(BLOCK_ICE, j, i);
            }
            else if (stages[stage][i][j] == 'W') {
                map[i][j] = new Block(BLOCK_AIR, j, i); // TODO
            }
            else if (stages[stage][i][j] == 'p') {
                map[i][j] = new Block(BLOCK_BRICK, j, i);
            }
            else if (stages[stage][i][j] == 'e') {
                map[i][j] = new Block(BLOCK_AIR, j, i); // TODO
            }
            else {
                ShowWindow(GetConsoleWindow(), SW_SHOW);
                std::cout << "Invalid map config! Exiting..." << std::endl;
                system("pause");
                return 0;
            }
        }
    }

    while (window.isOpen()) {
        sf::Clock clock;

        eventProcess(window);
        //networkEvent();
        display(window);

        window.setTitle("Battle City [0.11] - " + std::to_string((uint16_t)(1 / clock.getElapsedTime().asSeconds())) + " fps");
    }

    return 0;
}