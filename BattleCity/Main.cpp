#include <iostream>
#include <algorithm>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include <SFML/Network.hpp>
#include <Windows.h>

#include "Config.h"
#include "Block.h"
#include "Player.h"
#include "Enemy.h"
#include "Stages.cpp"

sf::Clock globalClock;

bool inFocus = true;
bool gameOver = false;

//sf::UdpSocket connection;
//std::string connectedIP = "";
//bool client = false;

std::vector<std::vector<Block*>> map(26, std::vector<Block*>(26, nullptr));
uint8_t stage = 0;

std::vector<Player*> players(0, nullptr);
std::vector<Enemy*> enemies(0, nullptr);

std::pair<std::vector<Bullet*>, std::vector<Player*>> playerBullets(std::vector<Bullet*>(0, nullptr), std::vector<Player*>(0, nullptr));
std::pair<std::vector<Bullet*>, std::vector<Enemy*>> enemyBullets(std::vector<Bullet*>(0, nullptr), std::vector<Enemy*>(0, nullptr));
std::vector<sf::Sprite> tankSprites;

sf::Music music;

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
        else if (inFocus && !gameOver) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::RShift || event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::Space) {
                    Bullet* bullet = players[0]->shoot();
                    if (bullet != nullptr) {
                        playerBullets.first.push_back(bullet);
                        playerBullets.second.push_back(players[0]);
                    }
                }
            }
        }
    }
    if (inFocus && !gameOver) {
        if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
            holdTime = globalClock.getElapsedTime().asSeconds();
        }
        else {
            while (globalClock.getElapsedTime().asSeconds() >= holdTime + 1 / players[0]->getSpeed()) {
                holdTime += 1 / players[0]->getSpeed();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    players[0]->up(map, players);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    players[0]->left(map, players);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    players[0]->down(map, players);
                }
                else {
                    players[0]->right(map, players);
                }
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

void enemyEvent() {
    for (uint8_t i = 0; i < enemies.size(); ++i) {
        if (enemies[i]->isDestroyed()) {
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
            continue;
        }
        Bullet* bullet = enemies[i]->think(map, players, enemies);
        if (bullet != nullptr) {
            enemyBullets.first.push_back(bullet);
            enemyBullets.second.push_back(enemies[i]);
        }
    }
    return;
}

void deleteDestroyedBullets() {
    for (uint8_t i = 0; i < playerBullets.first.size(); ++i) {
        if (playerBullets.first[i]->isDestroyed()) {
            delete playerBullets.first[i];
            playerBullets.second[i]->bulletDestroyed();
            playerBullets.first.erase(playerBullets.first.begin() + i);
            playerBullets.second.erase(playerBullets.second.begin() + i);
        }
    }
    for (uint8_t i = 0; i < enemyBullets.first.size(); ++i) {
        if (enemyBullets.first[i]->isDestroyed()) {
            delete enemyBullets.first[i];
            enemyBullets.second[i]->bulletDestroyed();
            enemyBullets.first.erase(enemyBullets.first.begin() + i);
            enemyBullets.second.erase(enemyBullets.second.begin() + i);
        }
    }
    return;
}

void bulletEvent() {
    for (uint8_t i = 0; i < playerBullets.first.size(); ++i) {
        playerBullets.first[i]->bulletCollide(enemyBullets.first);
    }
    deleteDestroyedBullets();

    for (uint8_t i = 0; i < players.size(); ++i) {
        if (players[i]->bulletCollide(enemyBullets.first)) {
            if (players[i]->isDestroyed()) {
                delete players[i];
                players.erase(players.begin() + i);
            }
            deleteDestroyedBullets();
        }
    }
    for (uint8_t i = 0; i < enemies.size(); ++i) {
        enemies[i]->bulletCollide(playerBullets.first);
        deleteDestroyedBullets();
    }

    for (uint8_t i = 0; i < playerBullets.first.size(); ++i) {
        playerBullets.first[i]->move(map, gameOver);
    }
    for (uint8_t i = 0; i < enemyBullets.first.size(); ++i) {
        enemyBullets.first[i]->move(map, gameOver);
    }
    return;
}

void loadStage(const uint8_t& stage) {
    // Reinit players
    for (uint8_t i = 0; i < players.size(); ++i) {
        delete players[i];
    }
    players = std::vector<Player*>(0, nullptr);
    players.push_back(new Player(TANK_YELLOW, 72, 200, 0, TANK_UP));

    // Reinit enemies
    for (uint8_t i = 0; i < enemies.size(); ++i) {
        delete enemies[i];
    }
    enemies = std::vector<Enemy*>(0, nullptr);

    // Reinit bullets
    for (uint8_t i = 0; i < playerBullets.first.size(); ++i) delete playerBullets.first[i];
    for (uint8_t i = 0; i < enemyBullets.first.size(); ++i) delete enemyBullets.first[i];
    playerBullets = std::pair<std::vector<Bullet*>, std::vector<Player*>>(std::vector<Bullet*>(0, nullptr), std::vector<Player*>(0, nullptr));
    enemyBullets = std::pair<std::vector<Bullet*>, std::vector<Enemy*>>(std::vector<Bullet*>(0, nullptr), std::vector<Enemy*>(0, nullptr));

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

void spawnEnemy() {
    static float lastSpawned = globalClock.getElapsedTime().asSeconds();
    static uint8_t spawned = 0;

    if (lastSpawned + ((47.5 - stage - (1 - 1) * 5) / 15) < globalClock.getElapsedTime().asSeconds() || spawned == 0) {
        if (spawned >= 20) {
            if (enemies.size() <= 0) {
                spawned = 0;
                loadStage(++stage);
            }
            return;
        }

        const uint8_t spawnPos = std::rand() % 3;
        const bool bonus = (spawned == 3) || (spawned == 10) || (spawned == 17) ? true : false;
        if (spawnPos == 0) {
            enemies.push_back(new Enemy(8, 8, tanks[stage][spawned], std::rand() % 3 + 1, bonus));
        }
        else if (spawnPos == 1) {
            enemies.push_back(new Enemy(104, 8, tanks[stage][spawned], std::rand() % 3 + 1, bonus));
        }
        else {
            enemies.push_back(new Enemy(200, 8, tanks[stage][spawned], std::rand() % 3 + 1, bonus));
        }
        ++spawned;
        lastSpawned = globalClock.getElapsedTime().asSeconds();
    }
    return;
}

void display(sf::RenderWindow& window) {
    window.clear(sf::Color(0));

    for (uint8_t i = 0; i < players.size(); ++i) {
        players[i]->draw(window);
    }
    for (uint8_t i = 0; i < enemies.size(); ++i) {
        enemies[i]->draw(window);
    }

    for (uint8_t i = 0; i < playerBullets.first.size(); ++i) {
        playerBullets.first[i]->draw(window);
    }
    for (uint8_t i = 0; i < enemyBullets.first.size(); ++i) {
        enemyBullets.first[i]->draw(window);
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

        sf::RenderWindow window(sf::VideoMode(208 * SCALE, 208 * SCALE), "Battle City [0.31]", sf::Style::Close);
        window.setVerticalSyncEnabled(true);
        window.setActive(true);
        window.setKeyRepeatEnabled(false);

        loadStage(stage);

        while (window.isOpen()) {
            sf::Clock fpsClock;

            if (players.size() <= 0) gameOver = true;
            spawnEnemy();
            eventProcess(window);
            //networkEvent();
            enemyEvent();
            bulletEvent();
            display(window);

            window.setTitle("Battle City [0.31] - " + std::to_string((uint16_t)(1 / fpsClock.getElapsedTime().asSeconds())) + " fps");
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