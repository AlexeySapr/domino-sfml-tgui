#pragma once
#include <iostream>
#include <string>

class User
{
public:
	//�������� ������������
	const void Show();

	//������
	void SetName(std::string name);
	void SetPass(std::string pass);
	void SetPoints(int points);

	//�������
	std::string GetName();
	std::string GetPass();
	int GetPoints();

	//���������� ���������� > <
	bool operator > (const User& right);
	bool operator < (const User& right);

private:
	std::string name = "";
	std::string pass = "";
	int points = 0;
};

