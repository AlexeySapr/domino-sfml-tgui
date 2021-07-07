#include "Logik.h"

int Duble(int num, std::vector<Stone*>& gamer)
{
    for (size_t i = 0; i < gamer.size(); i++)
    {
        if (gamer[i]->GetSide_A() == num && gamer[i]->GetSide_B() == num)
        {
            return i;
        }
    }
    return -1;
}

std::string FirstMove(std::vector<Stone*>& pile,
    std::vector<Stone*>& field,
    std::vector<Stone*>& player,
    std::vector<Stone*>& pc)
{
    int num = 1;
    int count = 0;
    do
    {
        if (Duble(num, player) != -1)
        {
            count = Duble(num, player);
            field.emplace_back(player[count]);
            player.erase(player.begin() + count);
            return "Pc";
        }
        else if (Duble(num, pc) != -1)
        {
            count = Duble(num, pc);
            field.emplace_back(pc[count]);
            pc.erase(pc.begin() + count);
            return "Player";
        }
        if (num < 7)
        {
            ++num;
        }
        else
        {
            player.emplace_back(pile[0]);
            pile.erase(pile.begin());
            pc.emplace_back(pile[0]);
            pile.erase(pile.begin());
            num = 1;
        }
    } while (true);
}

bool IsMovePossible(std::vector<Stone*>& player, int right_field_value, int left_field_value)
{
    for (size_t i = 0; i < player.size(); i++)
    {
        if (player[i]->GetSide_A() == left_field_value || player[i]->GetSide_A() == right_field_value
            || player[i]->GetSide_B() == left_field_value || player[i]->GetSide_B() == right_field_value)
        {
            return true;
        }
    }
    return false;
}

bool IsPutPossible(std::vector<Stone*>& player, int num_of_stone, int right_field_value, int left_field_value)
{
    if (player[num_of_stone]->GetSide_A() == left_field_value || player[num_of_stone]->GetSide_A() == right_field_value
        || player[num_of_stone]->GetSide_B() == left_field_value || player[num_of_stone]->GetSide_B() == right_field_value)
    {
        return true;
    }
    return false;
}

bool IsPutRightPossible(Stone* stone, int right_field_value)
{
    if (stone->GetSide_A() == right_field_value || stone->GetSide_B() == right_field_value)
    {
        return true;
    }
    return false;
}

bool IsPutLeftPossible(Stone* stone, int left_field_value)
{
    if (stone->GetSide_A() == left_field_value || stone->GetSide_B() == left_field_value)
    {
        return true;
    }
    return false;
}

bool IsBothPutPossible(Stone* stone, int right_field_value, int left_field_value)
{
    if (IsPutRightPossible(stone, right_field_value) && IsPutLeftPossible(stone, left_field_value))
    {
        return true;
    }
    return false;
}

bool WhatSide(sf::Font& font, sf::RenderWindow& window, std::string& side, bool& key)
{
    sf::Text text_1;
    text_1.setFont(font);
    text_1.setCharacterSize(20);
    text_1.setOutlineThickness(1.f);
    text_1.setFillColor(sf::Color::Magenta);
    text_1.setLetterSpacing(1.f);
    text_1.setString("WhatSide? ");
    text_1.setPosition(370.f, 180.f);
    window.draw(text_1);

    sf::Text text_2;
    text_2.setFont(font);
    text_2.setCharacterSize(20);
    text_2.setOutlineThickness(1.f);
    text_2.setFillColor(sf::Color::Magenta);
    text_2.setLetterSpacing(1.f);
    text_2.setString("Left");
    text_2.setPosition(500.f, 180.f);
    window.draw(text_2);

    sf::Text text_3;
    text_3.setFont(font);
    text_3.setCharacterSize(20);
    text_3.setOutlineThickness(1.f);
    text_3.setFillColor(sf::Color::Magenta);
    text_3.setLetterSpacing(1.f);
    text_3.setString("Right");
    text_3.setPosition(570.f, 180.f);
    window.draw(text_3);

    //Позиция мыши
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    //обновляем позицию мыши
    mousePosWindow = sf::Mouse::getPosition(window);
    mousePosView = window.mapPixelToCoords(mousePosWindow);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (text_2.getGlobalBounds().contains(mousePosView))
        {
            side = "left";
            key = true;
            return false;
        }
        if (text_3.getGlobalBounds().contains(mousePosView))
        {
            side = "right";
            key = true;
            return false;
        }
    }
}

int NumberOfStone(std::vector<Stone*>& mas, sf::Vector2f& mousePos)
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        for (size_t i = 0; i < mas.size(); i++)
        {
            if (mas[i]->GetSprite()->getGlobalBounds().contains(mousePos))
            {
                return i;
            }
        }
    }
}

int RequiredStone(std::vector<Stone*>& pc, int right_field_value, int left_field_value)
{
    int max_sum = -1;
    int num_of_stone = -1;
    for (size_t i = 0; i < pc.size(); i++)
    {
        if (IsPutPossible(pc, i, right_field_value, left_field_value))
        {
            if (max_sum < pc[i]->GetSum())
            {
                max_sum = pc[i]->GetSum();
                num_of_stone = i;
            }
        }
    }
    return num_of_stone;
}

int CalculatePoints(std::vector<Stone*>& gamer)
{
    int total = 0;
    for (size_t i = 0; i < gamer.size(); i++)
    {
        total += gamer.at(i)->GetSum();
    }

    return total;
}

void AddPointsUser(std::vector<User>& arr_users, User& user)
{
    for (size_t i = 0; i < arr_users.size(); i++)
    {
        if (arr_users.at(i).GetName() == user.GetName())
        {
            //int tmp_points = arr_users.at(i).GetPoints() + user.GetPoints();
            arr_users.at(i).SetPoints(user.GetPoints());
            break;
        }
    }
}

void SortVector(std::vector<User>& arr_users)
{

    for (size_t i = 0; i < arr_users.size(); i++)
    {
        for (size_t j = 0; j < arr_users.size() - 1; j++)
        {
            if (arr_users.at(j) < arr_users.at(j + 1))
            {
                std::swap(arr_users.at(j), arr_users.at(j + 1));
            }
        }
    }
}

void CleanMemory(std::vector<Stone*>& mass)
{
    for (size_t i = 0; i < mass.size(); i++)
    {
        delete mass[i];
    }
    mass.clear();
}

bool CleanAllMemory(std::vector<Stone*>& pile,
    std::vector<Stone*>& field_right,
    std::vector<Stone*>& field_left,
    std::vector<Stone*>& player,
    std::vector<Stone*>& pc)
{
    CleanMemory(pile);
    CleanMemory(field_right);
    CleanMemory(field_left);
    CleanMemory(player);
    CleanMemory(pc);

    if (pile.empty() &&
        field_right.empty() &&
        field_left.empty() &&
        player.empty() &&
        pc.empty())
    {
        return true;
    }

}

bool InitGame(std::vector<Stone*>& pile,
    std::vector<Stone*>& player,
    std::vector<Stone*>& pc, sf::Texture& dominoTexture)
{

    //заполняем КУЧУ камнями со спрайтами
    int step = 0;
    for (size_t i = 0; i < 7; ++i)
    {
        int j = 0;
        j += step;
        for (; j < 7; ++j)
        {
            pile.emplace_back(new Stone(i, j));
            pile.back()->SetSprite(dominoTexture);
        }
        ++step;
    }


    //перемешаем КУЧУ
    Shuffle(pile);
    //раздаем камни игроку и компьютеру
    SetGamers(pile, player);
    SetGamers(pile, pc);

    return true;
}


void EndGameMenu(bool& button, std::string& vibor)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
    {
        if (button == false)
        {
            button = true;
            vibor = "menu_end";
        }
    }
    else
    {
        button = false;
    }
}

void TableWindow(std::vector<User>& arr_users)
{
    //Создаем окно с таблицей
    sf::RenderWindow table_window(sf::VideoMode(800, 600), "Table");
    table_window.setFramerateLimit(25);

    sf::Font font_arial;
    if (!font_arial.loadFromFile("External/fonts/arial.ttf"))
    {
        std::cout << "Failed to load font!\n";
    }

    /*название таблицы*/
    sf::Text title_table;
    title_table.setFont(font_arial);
    title_table.setCharacterSize(40);
    title_table.setOutlineThickness(0.5f);
    title_table.setFillColor(sf::Color(0, 80, 205));
    title_table.setLetterSpacing(2.f);

    title_table.setString("Results table");
    title_table.setOrigin(title_table.getLocalBounds().width / 2, title_table.getLocalBounds().height / 2);
    title_table.setPosition(table_window.getSize().x / 2, 20.f);

    /*поля таблицы*/
    sf::Text text;
    text.setFont(font_arial);
    text.setCharacterSize(25);
    text.setOutlineThickness(0.5f);
    text.setLetterSpacing(2.f);
    text.setFillColor(sf::Color(0, 80, 205));

    std::vector<sf::Text> table_login;
    std::vector<sf::Text> table_points;

    float step = 0;
    float x = 40;
    float y = 50;

    text.setString("Users login:");
    text.setPosition(x + 30.f, y + 30.f + step);
    table_login.emplace_back(text);

    text.setString("Users points:");
    text.setPosition(x + 475.f, y + 30.f + step);
    table_points.emplace_back(text);

    step += 50.f;
    //заполняем столбец логинов текстом
    for (size_t i = 0; i < arr_users.size(); i++)
    {
        if (i < 3)
        {
            text.setFillColor(sf::Color(0, 200, 0));
        }
        else
        {
            text.setFillColor(sf::Color(0, 80, 205));
        }
        text.setString(arr_users[i].GetName());
        text.setPosition(x + 50.f, y + 30.f + step);
        table_login.emplace_back(text);

        text.setString(std::to_string(arr_users[i].GetPoints()));
        text.setPosition(x + 550.f, y + 30.f + step);
        table_points.emplace_back(text);

        step += 25.f;
    }

    while (table_window.isOpen())
    {
        sf::Event event;
        while (table_window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                table_window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    table_window.close();
                }
            }
        }

        table_window.clear(sf::Color(235, 250, 250));

        //выводим текст на экран
        table_window.draw(title_table);

        for (auto& text : table_login)
        {
            table_window.draw(text);
        }
        for (auto& text : table_points)
        {
            table_window.draw(text);
        }


        table_window.display();
    }
}