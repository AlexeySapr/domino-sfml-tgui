#pragma once
#include "Drawing.h"

int Duble(int num, std::vector<Stone*>& gamer);

std::string FirstMove(std::vector<Stone*>& pile, std::vector<Stone*>& field,
    std::vector<Stone*>& player, std::vector<Stone*>& pc);

bool IsMovePossible(std::vector<Stone*>& player, int right_field_value, int left_field_value);

bool IsPutPossible(std::vector<Stone*>& player, int num_of_stone, int right_field_value, int left_field_value);

bool IsPutRightPossible(Stone* stone, int right_field_value);

bool IsPutLeftPossible(Stone* stone, int left_field_value);

bool IsBothPutPossible(Stone* stone, int right_field_value, int left_field_value);

bool WhatSide(sf::Font& font, sf::RenderWindow& window, std::string& side, bool& key);

int NumberOfStone(std::vector<Stone*>& mas, sf::Vector2f& mousePos);

int RequiredStone(std::vector<Stone*>& pc, int right_field_value, int left_field_value);

int CalculatePoints(std::vector<Stone*>& gamer);

void AddPointsUser(std::vector<User>& arr_users, User& user);

void SortVector(std::vector<User>& arr_users);

void CleanMemory(std::vector<Stone*>& mass);

bool CleanAllMemory(std::vector<Stone*>& pile, std::vector<Stone*>& field_right,
    std::vector<Stone*>& field_left, std::vector<Stone*>& player, std::vector<Stone*>& pc);

bool InitGame(std::vector<Stone*>& pile, std::vector<Stone*>& player,
    std::vector<Stone*>& pc, sf::Texture& dominoTexture);

void EndGameMenu(bool& button, std::string& vibor);

void TableWindow(std::vector<User>& arr_users);