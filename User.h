#pragma once
#include <iostream>
#include <string>

class User
{
public:
	//показать пользователя
	const void Show();

	//сетеры
	void SetName(std::string name);
	void SetPass(std::string pass);
	void SetPoints(int points);

	//геттеры
	std::string GetName();
	std::string GetPass();
	int GetPoints();

	//перегрузка операторов > <
	bool operator > (const User& right);
	bool operator < (const User& right);

private:
	std::string name = "";
	std::string pass = "";
	int points = 0;
};

