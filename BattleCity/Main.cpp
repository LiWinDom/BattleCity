#define NETWORK_PORT 61000
#define DEBUG false

#include <iostream>
#include <algorithm>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include <SFML/Network.hpp>
#include <Windows.h>

#include "Config.h"
#include "Block.h"
#include "Tank.h"
#include "Bullet.h"
#include "Stages.cpp"

sf::Clock globalClock;

bool inFocus = true;

//sf::UdpSocket connection;
//std::string connectedIP = "";
//bool client = false;

std::vector<std::vector<Block*>> map(26, std::vector<Block*>(26, nullptr));
uint8_t stage = 0;

Tank tank(TANK_YELLOW, 72, 200, 0, TANK_MEDIUM);
std::vector<Bullet*> bullets(0, nullptr);

sf::Music music;

void loadStage(const uint8_t& stage) {
    tank = Tank(TANK_YELLOW, 72, 200, 0, TANK_MEDIUM);
    for (uint8_t i = 0; i < 26; ++i) {
        for (uint8_t j = 0; j < 26; ++j) {
            // Deleting unused blocks
            if (map[i][j] != nullptr) {
                delete map[i][j];
            }

            // Loading blocks from "Stages.cpp"
            if (stages[stage][i][j] == ' ') {
                map[i][j] = new Block(BLOCK_AIR, j, i);
            }
            else {
                map[i][j] = new Block(stages[stage][i][j], j, i);
            }
        }
    }
    music.play();

    return;
}

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
        else if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::RShift || event.key.code == sf::Keyboard::LShift/* || event.key.code == sf::Keyboard::Space*/) {
                if (tank.getRotation() == TANK_UP) {
                    bullets.push_back(new Bullet(tank.getX(), tank.getY() - 8, BULLET_UP));
                }
                else if (tank.getRotation() == TANK_LEFT) {
                    bullets.push_back(new Bullet(tank.getX() - 8, tank.getY(), BULLET_LEFT));
                }
                else if (tank.getRotation() == TANK_DOWN) {
                    bullets.push_back(new Bullet(tank.getX(), tank.getY() + 8, BULLET_DOWN));
                }
                else if (tank.getRotation() == TANK_RIGHT) {
                    bullets.push_back(new Bullet(tank.getX() + 8, tank.getY(), BULLET_RIGHT));
                }
            }
            else if (event.key.code == sf::Keyboard::Space) {
                if (tank.getRotation() == TANK_UP) {
                    bullets.push_back(new Bullet(tank.getX(), tank.getY() - 8, BULLET_UP, BULLET_FAST, true));
                }
                else if (tank.getRotation() == TANK_LEFT) {
                    bullets.push_back(new Bullet(tank.getX() - 8, tank.getY(), BULLET_LEFT, BULLET_FAST, true));
                }
                else if (tank.getRotation() == TANK_DOWN) {
                    bullets.push_back(new Bullet(tank.getX(), tank.getY() + 8, BULLET_DOWN, BULLET_FAST, true));
                }
                else if (tank.getRotation() == TANK_RIGHT) {
                    bullets.push_back(new Bullet(tank.getX() + 8, tank.getY(), BULLET_RIGHT, BULLET_FAST, true));
                }
            } //test
            else if (event.key.code == sf::Keyboard::Num1) {
                loadStage(0);
            }
            else if (event.key.code == sf::Keyboard::Num2) {
                loadStage(1);
            }
            else if (event.key.code == sf::Keyboard::Num3) {
                loadStage(2);
            }
        }
    }
    if (inFocus) {
        while (globalClock.getElapsedTime().asSeconds() >= holdTime + 1 / tank.getSpeed()) {
            holdTime += 1 / tank.getSpeed();
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
//                    while (globalClock.getElapsedTime().asSeconds() >= holdTime + 1 / tank.getSpeed()) {
//                        tank2.up(tank);
//                        holdTime += 1 / tank.getSpeed();
//                    }
//                }
//                else if (data[0] == 'A') {
//                    while (globalClock.getElapsedTime().asSeconds() >= holdTime + 1 / tank.getSpeed()) {
//                        tank2.left(tank);
//                        holdTime += 1 / tank.getSpeed();
//                    }
//                }
//                else if (data[0] == 'S') {
//                    while (globalClock.getElapsedTime().asSeconds() >= holdTime + 1 / tank.getSpeed()) {
//                        tank2.down(tank);
//                        holdTime += 1 / tank.getSpeed();
//                    }
//                }
//                else if (data[0] == 'D') {
//                    while (globalClock.getElapsedTime().asSeconds() >= holdTime + 1 / tank.getSpeed()) {
//                        tank2.right(tank);
//                        holdTime += 1 / tank.getSpeed();
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

void doItNow() {
    for (uint8_t i = 0; i < bullets.size(); ++i) {
        if (!bullets[i]->move(map)) {
            delete bullets[i];
            bullets.erase(bullets.begin() + i);
        }
    }
    return;
}

void display(sf::RenderWindow& window) {
    window.clear(sf::Color(0));

    tank.draw(window);
    for (uint8_t i = 0; i < bullets.size(); ++i) {
        bullets[i]->draw(window);
    }
    for (uint8_t i = 0; i < 26; ++i) {
        for (uint8_t j = 0; j < 26; ++j) {
            map[i][j]->draw(window);
        }
    }

    window.display();
}

int main() {
    try {
        if (!music.openFromFile("resources/sounds/StageBegin.ogg")) throw 1;
        music.setVolume(50);
        /*if (connection.bind(NETWORK_PORT) != sf::Socket::Done) throw "(2 games opened?)";
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

        sf::RenderWindow window(sf::VideoMode(832, 832), "Battle City [0.3]", sf::Style::Close);
        window.setVerticalSyncEnabled(true);
        window.setActive(true);

        loadStage(stage);

        while (window.isOpen()) {
            sf::Clock fpsClock;

            eventProcess(window);
            //networkEvent();
            doItNow();
            display(window);

            window.setTitle("Battle City [0.3] - " + std::to_string((uint16_t)(1 / fpsClock.getElapsedTime().asSeconds())) + " fps");
        }
    }
    catch (std::string err) {
        ShowWindow(GetConsoleWindow(), SW_SHOW);
        std::cout << err << std::endl;
        system("pause");
    }
    catch (...) {
        ShowWindow(GetConsoleWindow(), SW_SHOW);
        system("pause");
    }
    return 0;
}