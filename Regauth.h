#pragma once
#include "User.h"
#include "Menu.h"

void WriteVectorToFile(std::vector<User>& arr_users);

void ReadVectorFromFile(std::vector<User>& arr_users);

bool NameValid(std::string name);

bool Login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password, tgui::Label::Ptr label);

bool IsUser(std::vector<User>& arr_users, std::string name, std::string pass);

bool IsUser(std::string name, std::string pass, std::vector<User>& arr_users);

void updateTextSize(tgui::GuiBase& gui);

void MyTgui(std::vector<User>& arr_users, User& user, std::string regauth);