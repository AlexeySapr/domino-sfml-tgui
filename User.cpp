#include "User.h"

const void User::Show()
{
	{
		std::cout << "Name: " << this->name << std::endl;
		std::cout << "Pass: " << this->pass << std::endl;
		std::cout << "Points: " << this->points << std::endl;
	}
}

void User::SetName(std::string name)
{
	this->name = name;
}

void User::SetPass(std::string pass)
{
	this->pass = pass;
}

void User::SetPoints(int points)
{
	this->points = points;
}

std::string User::GetName()
{
	return name;
}

std::string User::GetPass()
{
	return pass;
}

int User::GetPoints()
{
	return points;
}

bool User::operator>(const User& right)
{
	return this->points > right.points;
}

bool User::operator<(const User& right)
{
	return this->points < right.points;
}
