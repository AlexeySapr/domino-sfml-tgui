#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <ctime>

#include <TGUI/TGUI.hpp>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <vector>


class Stone
{
private:
    /*переменные*/
    int id_stone = 0;
    int side_A = 0;
    int side_B = 0;
    int sum = 0;
    char direct = 'H';  //H - горизонтально, V - вертикально
    sf::Sprite* dominoStone = nullptr;
    sf::Sprite* dominoStone_back = nullptr;
    char roteted = 'N';

    /*методы*/
    void SetSide_A(int side_A);
    void SetSide_B(int side_B);

public:
    /*переменные*/
    static int idCounter;

    /*конструктор*/
    Stone();
    Stone(int side_A, int side_B);

    //деструктор
    ~Stone();

    //добавить текстуру
    void SetSprite(sf::Texture& dominoTexture);

    //установить ориентацию
    void SetDir(char dir);
 
    //вернуть текстуру
    sf::Sprite* GetSprite() const;

    //вернуть текстуру закрытой
    sf::Sprite* GetBackSprite() const;

    //вернуть сумму камня
    int GetSum();

    //вернуть ID камня
    int GetID();

    //вернуть ориентацию камня
    char GetDir();

    //вернуть разворачивать ли камень
    char GetRotated();

    //вернуть значение стороны А камня
    int GetSide_A();

    //вернуть значение стороны B камня
    int GetSide_B();

    //подвинуть текстуру
    void Move(float x, float y);

    //задать позицию текстуре
    void Position(float x, float y);

    //повернуть текстуру
    void Rotation(float angle);

    //повернуть камень
    void RotateStone();

    //показать камень в консоль
    void ShowStone() const;

};



