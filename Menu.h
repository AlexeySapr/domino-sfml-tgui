#pragma once
#include "Stone.h"

void dominoName(sf::RenderWindow& window);

void dominoMenu(sf::Font& font, sf::Text text[3], sf::RenderWindow& window, std::string key);

void moveUpMenu(int& selItem, sf::Text text[3]);

void moveDownMenu(int& selItem, sf::Text text[3]);

void keyItemUpdate(std::string& vibor, bool& isButtonPressed, int& selItem, sf::Text text[3]);

void mouseItemUpdate(std::string& vibor, bool& isButtonPressed, int& selItem, sf::Text text[3], sf::RenderWindow& window);