#include <iostream>
#include <algorithm>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
//#include <SFML/Network.hpp>
#include <Windows.h>

#include "Config.h"
#include "Stages.cpp"
#include "Block.h"
#include "Tank.h"
#include "Explosion.h"
#include "Bonus.h"

sf::Clock globalClock;

bool inFocus = true;
bool gameOver = false;
bool eagleDestroyed = false;

//sf::UdpSocket connection;
//std::string connectedIP = "";
//bool client = false;

std::vector<std::vector<Block*>> map(26, std::vector<Block*>(26, nullptr));
uint8_t stage = 0;

Tank* player1 = nullptr;
Tank* player2 = nullptr;
std::vector<Tank*> enemies(0, nullptr);
uint8_t spawned = 0;

float playersFrozenUntil = -1;
float enemiesFrozenUntil = -1;

std::vector<Bullet*> player1Bullets(0, nullptr);
std::vector<Bullet*> player2Bullets(0, nullptr);
std::pair<std::vector<Bullet*>, std::vector<Tank*>> enemyBullets(std::vector<Bullet*>(0, nullptr), std::vector<Tank*>(0, nullptr));

std::vector<Explosion*> explosions(0, nullptr);
Explosion* eagleExplosion = nullptr;

sf::Texture numbers[10];

sf::Texture statsBackgroundTexture;
sf::Sprite statsBackgroundSprite;
sf::Texture tankSmallTexture;
sf::Sprite tankSmallSprite;
sf::Sprite p1lives;
sf::Sprite p2lives;
sf::Sprite stageDozens;
sf::Sprite stageOnes;

sf::Texture GOtexture;
sf::Sprite GOsprite;

Bonus* bonus = nullptr;

void loadStage(const uint8_t& loadingStage) {
    // Reinit players
    if (player1 != nullptr) player1->playerReset();
    if (player2 != nullptr) player2->playerReset();

    // Reinit enemies
    for (uint8_t i = 0; i < enemies.size(); ++i) {
        delete enemies[i];
    }
    enemies = std::vector<Tank*>(0, nullptr);
    spawned = 0;

    playersFrozenUntil = -1;
    enemiesFrozenUntil = -1;

    // Reinit bullets
    for (uint8_t i = 0; i < player1Bullets.size(); ++i) delete player1Bullets[i];
    for (uint8_t i = 0; i < player2Bullets.size(); ++i) delete player2Bullets[i];
    for (uint8_t i = 0; i < enemyBullets.first.size(); ++i) delete enemyBullets.first[i];
    player1Bullets = std::vector<Bullet*>(0, nullptr);
    player2Bullets = std::vector<Bullet*>(0, nullptr);
    enemyBullets = std::pair<std::vector<Bullet*>, std::vector<Tank*>>(std::vector<Bullet*>(0, nullptr), std::vector<Tank*>(0, nullptr));

    for (uint8_t i = 0; i < 26; ++i) {
        for (uint8_t j = 0; j < 26; ++j) {
            // Deleting unused blocks
            if (map[i][j] != nullptr) {
                delete map[i][j];
            }

            // Loading blocks from "Stages.cpp"
            if (stages[loadingStage][i][j] == ' ') {
                map[i][j] = new Block(BLOCK_AIR, j, i);
            }
            else {
                map[i][j] = new Block(stages[loadingStage][i][j], j, i);
            }
        }
    }

    // Reinit explosions
    for (uint8_t i = 0; i < explosions.size(); ++i) {
        delete explosions[i];
    }
    explosions = std::vector<Explosion*>(0, nullptr);
    delete eagleExplosion;
    eagleExplosion = nullptr;

    // Reinit bonus
    if (bonus != nullptr) delete bonus;
    bonus = nullptr;

    stageDozens.setTexture(numbers[(stage + 1) / 10 % 10]);
    stageOnes.setTexture(numbers[(stage + 1) % 10]);

    return;
}

void newGame() {
    gameOver = false;
    eagleDestroyed = false;
    stage = 0;

    if (player1 != nullptr) delete player1;
    if (player2 != nullptr) delete player2;
    player1 = new Tank(TANK_PLAYER1, 72, 200, 0, TANK_UP);
    //player2 = new Tank(TANK_PLAYER2, 136, 200, 0, TANK_UP);

    loadStage(stage);

    return;
}

void spawnTanks() {
    if (player1 != nullptr) {
        if (!player1->isSpawned()) {
            player1->spawn(player1, player2, enemies);
        }
    }
    if (player2 != nullptr) {
        if (!player2->isSpawned()) {
            player2->spawn(player1, player2, enemies);
        }
    }
    for (uint8_t i = 0; i < enemies.size(); ++i) {
        if (!enemies[i]->isSpawned()) {
            enemies[i]->spawn(player1, player2, enemies);
        }
    }
    return;
}

void spawnEnemy() {
    static float lastSpawned = globalClock.getElapsedTime().asSeconds();
    static float allKilled = 0;

    if ((lastSpawned + ((47.5 - stage - (1 - 1) * 5) / 15) < globalClock.getElapsedTime().asSeconds() || spawned == 0)) {
        if (spawned >= 20) {
            if (enemies.size() <= 0) {
                if (allKilled == 0) {
                    allKilled = globalClock.getElapsedTime().asSeconds();
                }
                if (allKilled + 2 < globalClock.getElapsedTime().asSeconds()) {
                    loadStage(++stage % 16);
                    allKilled = 0;
                }
            }
            lastSpawned = globalClock.getElapsedTime().asSeconds();
            return;
        }

        static sf::Texture tx;
        if (!tx.loadFromFile("resources/graphics/TankWhite.png", sf::IntRect(0, 0, 16, 16))) throw 1;

        static sf::Sprite pos[3];
        for (uint8_t i = 0; i < 3; ++i) {
            pos[i].setOrigin(8, 8);
            pos[i].setScale(SCALE, SCALE);
            pos[i].setTexture(tx);
        }
        pos[0].setPosition(8 * SCALE, 8 * SCALE);
        pos[1].setPosition(104 * SCALE, 8 * SCALE);
        pos[2].setPosition(200 * SCALE, 8 * SCALE);

        const bool bonus = (spawned == 3) || (spawned == 10) || (spawned == 17) ? true : false;

        std::vector<uint8_t> poses(0, 0);
        for (uint8_t i = 0; i < 3; ++i) {
            bool collide = false;
            if (player1 != nullptr) {
                if (player1->spriteCollide(pos[i], true)) {
                    continue;
                }
            }
            if (player2 != nullptr) {
                if (player2->spriteCollide(pos[i], true)) {
                    continue;
                }
            }
            for (uint8_t j = 0; j < enemies.size() && !collide; ++j) {
                if (enemies[j]->spriteCollide(pos[i], true)) {
                    collide = true;
                    break;
                }
            }
            if (!collide) {
                poses.push_back(i * 96 + 8);
            }
        }
        if (poses.size() > 0) {
            enemies.push_back(new Tank(TANK_ENEMY, poses[std::rand() % poses.size()], 8, tanks[stage % 8][spawned], std::rand() % 3 + 1, enemiesFrozenUntil - globalClock.getElapsedTime().asSeconds(), bonus));
            ++spawned;
            lastSpawned = globalClock.getElapsedTime().asSeconds();
        }
    }
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
        else if (inFocus && event.type == sf::Event::KeyPressed) {
            if (player1 != nullptr && !gameOver) {
                if ((event.key.code == sf::Keyboard::RShift || event.key.code == sf::Keyboard::LShift || event.key.code == sf::Keyboard::Space) && !player1->isDestroyed()) {
                    Bullet* bullet = player1->shoot();
                    if (bullet != nullptr) {
                        player1Bullets.push_back(bullet);
                    }
                }
            }
            if (event.key.code == sf::Keyboard::R) {
                newGame();
            }
        }
    }
    if (inFocus && player1 != nullptr && !gameOver) {
        if (!player1->isDestroyed()) {
            if (!(sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ||
                sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))) {
                holdTime = globalClock.getElapsedTime().asSeconds();
            }
            else {
                while (globalClock.getElapsedTime().asSeconds() >= holdTime + 1 / player1->getSpeed()) {
                    holdTime += 1 / player1->getSpeed();
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                        player1->up(map, player1, player2, enemies);
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                        player1->left(map, player1, player2, enemies);
                    }
                    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                        player1->down(map, player1, player2, enemies);
                    }
                    else {
                        player1->right(map, player1, player2, enemies);
                    }
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
            if (enemies[i]->getBonus()) {
                if (bonus != nullptr) delete bonus;
                bonus = new Bonus(map, player1, player2, enemies);
            }
            delete enemies[i];
            enemies.erase(enemies.begin() + i);
            continue;
        }
        Bullet* bullet = enemies[i]->think(map, player1, player2, enemies);
        if (bullet != nullptr) {
            enemyBullets.first.push_back(bullet);
            enemyBullets.second.push_back(enemies[i]);
        }
    }
    return;
}

void deleteDestroyedBullets() {
    for (uint8_t i = 0; i < player1Bullets.size(); ++i) {
        if (player1Bullets[i]->isDestroyed()) {
            delete player1Bullets[i];
            player1->bulletDestroyed();
            player1Bullets.erase(player1Bullets.begin() + i);
            --i;
        }
    }
    for (uint8_t i = 0; i < player2Bullets.size(); ++i) {
        if (player2Bullets[i]->isDestroyed()) {
            delete player2Bullets[i];
            player2->bulletDestroyed();
            player2Bullets.erase(player2Bullets.begin() + i);
            --i;
        }
    }
    for (uint8_t i = 0; i < enemyBullets.first.size(); ++i) {
        if (enemyBullets.first[i]->isDestroyed()) {
            delete enemyBullets.first[i];
            enemyBullets.second[i]->bulletDestroyed();
            enemyBullets.first.erase(enemyBullets.first.begin() + i);
            enemyBullets.second.erase(enemyBullets.second.begin() + i);
            --i;
        }
    }
    return;
}

void bulletEvent() {
    if (player1 != nullptr) {
        Explosion* tankExplosion = nullptr, * bulletExplosion = nullptr;
        if (player1->bulletCollide(enemyBullets.first, player2Bullets, tankExplosion, bulletExplosion)) {
            deleteDestroyedBullets();
        }
        if (tankExplosion != nullptr) {
            explosions.push_back(tankExplosion);
        }
        if (bulletExplosion != nullptr) {
            explosions.push_back(bulletExplosion);
        }
    }
    if (player2 != nullptr) {
        Explosion* tankExplosion = nullptr, * bulletExplosion = nullptr;
        if (player2->bulletCollide(enemyBullets.first, player1Bullets, tankExplosion, bulletExplosion)) {
            deleteDestroyedBullets();
        }
        if (tankExplosion != nullptr) {
            explosions.push_back(tankExplosion);
        }
        if (bulletExplosion != nullptr) {
            explosions.push_back(bulletExplosion);
        }
    }
    for (uint8_t i = 0; i < enemies.size(); ++i) {
        Explosion* tankExplosion = nullptr, * bulletExplosion = nullptr;
        if (enemies[i]->bulletCollide(player1Bullets, player2Bullets, tankExplosion, bulletExplosion)) {
            deleteDestroyedBullets();
        }
        if (tankExplosion != nullptr) {
            explosions.push_back(tankExplosion);
        }
        if (bulletExplosion != nullptr) {
            explosions.push_back(bulletExplosion);
        }
    }

    for (uint8_t i = 0; i < player1Bullets.size(); ++i) {
        Explosion* exp = nullptr;
        player1Bullets[i]->move(map, enemyBullets.first, player2Bullets, eagleDestroyed, exp);
        if (exp != nullptr) {
            explosions.push_back(exp);
        }
    }
    for (uint8_t i = 0; i < player2Bullets.size(); ++i) {
        Explosion* exp = nullptr;
        player2Bullets[i]->move(map, enemyBullets.first, player1Bullets, eagleDestroyed, exp);
        if (exp != nullptr) {
            explosions.push_back(exp);
        }
    }
    for (uint8_t i = 0; i < enemyBullets.first.size(); ++i) {
        Explosion* exp = nullptr;
        enemyBullets.first[i]->move(map, player1Bullets, player2Bullets, eagleDestroyed, exp);
        if (exp != nullptr) {
            explosions.push_back(exp);
        }
    }
    deleteDestroyedBullets();

    if (eagleDestroyed) {
        gameOver = true;
    }
    return;
}

void bonusEvent() {
    if (bonus != nullptr) {
        bonus->collideCheck(player1, player2, enemies, map, globalClock, playersFrozenUntil, enemiesFrozenUntil, explosions);
        if (bonus->isTaken()) {
            delete bonus;
            bonus = nullptr;
        }
    }
    return;
}

void displayStats(sf::RenderWindow& window) {
    window.draw(statsBackgroundSprite);

    for (uint8_t i = 0; i < 20 - spawned; ++i) {
        tankSmallSprite.setPosition((216 + ((i % 2) << 3)) * SCALE, ((i / 2 + 1) * SCALE) << 3);
        window.draw(tankSmallSprite);
    }

    p1lives.setTexture(numbers[std::min(player1->getLives(), (uint8_t)9)]);
    window.draw(p1lives);

    if (player2 == nullptr) {
        static sf::RectangleShape fillP2;
        fillP2.setFillColor(sf::Color(0x636363FF));
        fillP2.setScale(SCALE, SCALE);
        fillP2.setSize(sf::Vector2f(16, 16));
        fillP2.setPosition(216 * SCALE, 144 * SCALE);
        window.draw(fillP2);
    }
    else {
        p2lives.setTexture(numbers[std::min(player2->getLives(), (uint8_t)9)]);
        window.draw(p2lives);
    }

    if (stage > 8) {
        window.draw(stageDozens);
    }
    window.draw(stageOnes);

    return;
}

void display(sf::RenderWindow& window) {
    window.clear(sf::Color(0));
    displayStats(window);

    // Drawing game field
    for (uint8_t i = 0; i < 26; ++i) {
        for (uint8_t j = 0; j < 26; ++j) {
            if (map[i][j]->getType() != BLOCK_BUSH) {
                map[i][j]->draw(window, globalClock);
            }
        }
    }

    // Drawing bonus
    if (bonus != nullptr) bonus->draw(window);

    // Drawing spawn animations
    if (player1 != nullptr) {
        if (!player1->isSpawned()) player1->draw(window);
    }
    if (player2 != nullptr) {
        if (!player2->isSpawned()) player2->draw(window);
    }
    for (uint8_t i = 0; i < enemies.size(); ++i) {
        if (!enemies[i]->isSpawned()) enemies[i]->draw(window);
    }

    // Drawing tanks
    if (player1 != nullptr) {
        if (player1->isSpawned()) player1->draw(window);
    }
    if (player2 != nullptr) {
        if (player2->isSpawned()) player2->draw(window);
    }
    for (uint8_t i = 0; i < enemies.size(); ++i) {
        if (enemies[i]->isSpawned()) enemies[i]->draw(window);
    }

    // Drawing bullets
    for (uint8_t i = 0; i < player1Bullets.size(); ++i) {
        player1Bullets[i]->draw(window);
    }
    for (uint8_t i = 0; i < player2Bullets.size(); ++i) {
        player2Bullets[i]->draw(window);
    }
    for (uint8_t i = 0; i < enemyBullets.first.size(); ++i) {
        enemyBullets.first[i]->draw(window);
    }

    // Drawing explosions
    for (uint8_t i = 0; i < explosions.size(); ++i) {
        if (explosions[i]->isEnded()) {
            delete explosions[i];
            explosions.erase(explosions.begin() + i);
            --i;
            continue;
        }
        explosions[i]->draw(window);
    }

    // Drawing bushes
    for (uint8_t i = 0; i < 26; ++i) {
        for (uint8_t j = 0; j < 26; ++j) {
            if (map[i][j]->getType() == BLOCK_BUSH) {
                map[i][j]->draw(window, globalClock);
            }
        }
    }

    // Draw Game Over (if needed)
    static float GOlastMove;
    static uint8_t coord = 216;
    if (gameOver) {
        while (GOlastMove + 0.015 < globalClock.getElapsedTime().asSeconds() && coord > 104) {
            --coord;
            GOlastMove += 0.015;
        }
        GOsprite.setPosition(104 * SCALE, coord * SCALE);
        window.draw(GOsprite);
    }
    else {
        GOlastMove = globalClock.getElapsedTime().asSeconds();
        coord = 216;
    }
    if (eagleDestroyed) {
        if (eagleExplosion == nullptr) {
            eagleExplosion = new Explosion(104, 200, true);
        }
        eagleExplosion->draw(window);
    }

    window.display();
}

int main() {
    try {
        std::srand(std::time(nullptr));

        // Preloading textures/sprites
        sf::Image icon;
        if (!icon.loadFromFile("resources/Icon.png")) throw 1;

        for (uint8_t i = 0; i < 10; ++i) {
            if (!numbers[i].loadFromFile("resources/graphics/Numbers.png", sf::IntRect(i << 3, 0, 8, 8))) throw 1;
        }
        p1lives.setScale(SCALE, SCALE);
        p1lives.setPosition(224 * SCALE, 128 * SCALE);
        p2lives.setScale(SCALE, SCALE);
        p2lives.setPosition(224 * SCALE, 152 * SCALE);

        stageDozens.setScale(SCALE, SCALE);
        stageDozens.setPosition(216 * SCALE, 184 * SCALE);
        stageOnes.setScale(SCALE, SCALE);
        stageOnes.setPosition(224 * SCALE, 184 * SCALE);

        if (!statsBackgroundTexture.loadFromFile("resources/graphics/StatsBackground.png")) throw 1;
        statsBackgroundSprite.setScale(SCALE, SCALE);
        statsBackgroundSprite.setPosition(208 * SCALE, 0);
        statsBackgroundSprite.setTexture(statsBackgroundTexture);

        if (!tankSmallTexture.loadFromFile("resources/graphics/TankSmall.png")) throw 1;
        tankSmallSprite.setScale(SCALE, SCALE);
        tankSmallSprite.setTexture(tankSmallTexture);

        if (!GOtexture.loadFromFile("resources/graphics/GameOver.png")) throw 1;
        GOsprite.setOrigin(16, 8);
        GOsprite.setScale(SCALE, SCALE);
        GOsprite.setPosition(104 * SCALE, 216 * SCALE);
        GOsprite.setTexture(GOtexture);

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

        sf::RenderWindow window(sf::VideoMode(240 * SCALE, 208 * SCALE), "Battle City [beta 1.74]", sf::Style::Close);
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
        window.setVerticalSyncEnabled(true);
        window.setActive(true);
        window.setKeyRepeatEnabled(false);

        newGame();

        while (window.isOpen()) {
            sf::Clock fpsClock;

            if (!gameOver) {
                bool over = true;
                if (player1 != nullptr) {
                    if (!player1->isDestroyed()) {
                        over = false;
                    }
                }
                if (player2 != nullptr) {
                    if (!player2->isDestroyed()) {
                        over = false;
                    }
                }
                gameOver = over;
                spawnEnemy();
            }

            spawnTanks();
            eventProcess(window);
            //networkEvent();
            enemyEvent();
            bulletEvent();
            bonusEvent();

            display(window);

            window.setTitle("Battle City [beta 1.74] - " + std::to_string((uint16_t)(1 / fpsClock.getElapsedTime().asSeconds())) + " fps");
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