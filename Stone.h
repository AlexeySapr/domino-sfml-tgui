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
    /*����������*/
    int id_stone = 0;
    int side_A = 0;
    int side_B = 0;
    int sum = 0;
    char direct = 'H';  //H - �������������, V - �����������
    sf::Sprite* dominoStone = nullptr;
    sf::Sprite* dominoStone_back = nullptr;
    char roteted = 'N';

    /*������*/
    void SetSide_A(int side_A);
    void SetSide_B(int side_B);

public:
    /*����������*/
    static int idCounter;

    /*�����������*/
    Stone();
    Stone(int side_A, int side_B);

    //����������
    ~Stone();

    //�������� ��������
    void SetSprite(sf::Texture& dominoTexture);

    //���������� ����������
    void SetDir(char dir);
 
    //������� ��������
    sf::Sprite* GetSprite() const;

    //������� �������� ��������
    sf::Sprite* GetBackSprite() const;

    //������� ����� �����
    int GetSum();

    //������� ID �����
    int GetID();

    //������� ���������� �����
    char GetDir();

    //������� ������������� �� ������
    char GetRotated();

    //������� �������� ������� � �����
    int GetSide_A();

    //������� �������� ������� B �����
    int GetSide_B();

    //��������� ��������
    void Move(float x, float y);

    //������ ������� ��������
    void Position(float x, float y);

    //��������� ��������
    void Rotation(float angle);

    //��������� ������
    void RotateStone();

    //�������� ������ � �������
    void ShowStone() const;

};



