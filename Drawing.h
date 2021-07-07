#pragma once
#include "Regauth.h"

void SetPile(std::vector<Stone*>& pile, sf::Texture& dominoTexture);

void Shuffle(std::vector<Stone*>& pile);

const void SetPozStones(std::vector<Stone*>& vect, float x, float y);

const void SetPozField_right(std::vector<Stone*>& vect, float x, float y);

const void SetPozField_left(std::vector<Stone*>& vect, float x, float y);

void SetGamers(std::vector<Stone*>& pile, std::vector<Stone*>& gamer);

const void DrawStones(std::vector<Stone*>& pile, std::vector<Stone*>& player,
    std::vector<Stone*>& pc, sf::RenderTarget& target);

void DrawField(std::vector<Stone*>& field, sf::RenderTarget& target, char side);

const void TextOnTheField(sf::Font& font, sf::RenderWindow& window, std::string current_user);

const void StartText(sf::Font& font, sf::RenderWindow& window);

const void TextOnCenter(sf::Font& font, sf::RenderWindow& window, std::string message);

const void WhoMoveText(sf::Font& font, sf::RenderWindow& window, std::string message);

const void LeftValueText(sf::Font& font, sf::RenderWindow& window, int number);

const void RightValueText(sf::Font& font, sf::RenderWindow& window, int number);

const void PlayerPoints(sf::Font& font, sf::RenderWindow& window, int number);