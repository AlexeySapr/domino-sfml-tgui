#include "Stone.h"

/*������ ������*/
void Stone::SetSide_A(int side_A)
{
    this->side_A = side_A;
}

void Stone::SetSide_B(int side_B)
{
    this->side_B = side_B;
}

/*�����������*/
Stone::Stone(){}
Stone::Stone(int side_A, int side_B)
{
    this->id_stone = idCounter++;
    this->side_A = side_A;
    this->side_B = side_B;
    if (side_A == side_B)
    {
        this->direct = 'V';
    }
    else
    {
        this->direct = 'H';
    }
    this->sum = side_A + side_B;
}

/*����������*/
Stone::~Stone()
{
    std::cout << "Destructor!!!\n";
    delete this->dominoStone;
    this->dominoStone = nullptr;
    delete this->dominoStone_back;
    this->dominoStone_back = nullptr;
}


/*������ ������*/

//�������� ��������
void Stone::SetSprite(sf::Texture& dominoTexture)
{
    int step_1 = 0;
    this->dominoStone = new sf::Sprite(dominoTexture);
    this->dominoStone_back = new sf::Sprite(dominoTexture);
    for (size_t i = 0; i < 28; i++)
    {
        if (this->id_stone == i)
        {
            step_1 = i * 40;
            this->dominoStone->setTextureRect(sf::IntRect(step_1, 0, 40, 80));
            this->dominoStone->setOrigin(20.f, 40.f);
            this->dominoStone_back->setTextureRect(sf::IntRect(1120, 0, 40, 80));
            this->dominoStone_back->setOrigin(20.f, 40.f);

            /*�������� ������*/
            this->dominoStone->setScale(0.6f, 0.6f);
            this->dominoStone_back->setScale(0.6f, 0.6f);
        }
    }
}

//���������� ����������
void Stone::SetDir(char dir)
{
    this->direct = dir;
}

//������� ��������
sf::Sprite* Stone::GetSprite() const
{
    return this->dominoStone;
}

sf::Sprite* Stone::GetBackSprite() const
{
    return this->dominoStone_back;
}

//������� ����� �����
int Stone::GetSum()
{
    return this->sum;
}

//������� ID �����
int Stone::GetID()
{
    return this->id_stone;
}

//������� ���������� �����
char Stone::GetDir()
{
    return this->direct; 
}

//������� ������������� �� ������
char Stone::GetRotated()
{
    return this->roteted;
}

//������� �������� ������� � �����
int Stone::GetSide_A()
{
    return this->side_A;
}

//������� �������� ������� B �����
int Stone::GetSide_B()
{
    return this->side_B;
}

//��������� ��������
void Stone::Move(float x, float y)
{
    this->dominoStone->move(x, y);
}

//������ ������� ��������
void Stone::Position(float x, float y)
{
    this->dominoStone->setPosition(x, y);
}

//��������� ��������
void Stone::Rotation(float angle)
{
    this->dominoStone->setRotation(angle);
}

//��������� ������
void Stone::RotateStone()
{
    int temp = this->side_A;
    this->side_A = this->side_B;
    this->side_B = temp;
    this->roteted = 'Y';
}

//�������� ������ � �������
void Stone::ShowStone() const
{
    std::cout << "****************************************************\n";
    std::cout << "id: " << id_stone << std::endl;
    std::cout << "side A: " << side_A << std::endl;
    std::cout << "side B: " << side_B << std::endl;
    std::cout << "sum: " << sum << std::endl;
    std::cout << "direct: " << direct << std::endl;
    std::cout << "rotated: " << roteted << std::endl;
    std::cout << "****************************************************\n\n";
}

int Stone::idCounter = 0;