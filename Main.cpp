#include "Logik.h"

int main()
{
    //��� ������ ������� rand
    srand(static_cast<unsigned>(time(NULL)));

    //������� �������� ������������
    User current_user;

    //������� ������ �������������
    std::vector<User> arr_users;

    //��������� ������ ������������� �� ����� � ������
    ReadVectorFromFile(arr_users);

    //������� ������� ����
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML");
    window.setFramerateLimit(25);

    //������
    sf::Font font;
    if (!font.loadFromFile("External/fonts/Konstanting_cyr.ttf"))
    {
        std::cout << "Failed to load font!\n";
    }

    sf::Font font_arial;
    if (!font_arial.loadFromFile("External/fonts/arial.ttf"))
    {
        std::cout << "Failed to load font!\n";
    }

    //����� ����
    sf::Text text_menu_start[3];
    sf::Text text_menu_end[3];
    dominoMenu(font_arial, text_menu_start, window, "start");
    dominoMenu(font_arial, text_menu_end, window, "end");

    //����� ����
    int selItem = 0;
    std::string stage_vibor = "menu_start";
    std::string vibor = "";

    //������� ����
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    //������ �� ������ ����?
    bool mouseHeld = false;
    bool isButtonPressed = false;

    ///////////////////////////////////////////////////////////////////////////////////////////
    //�������� �������� ��� ���������
    sf::Texture dominoTexture;
    if (!dominoTexture.loadFromFile("External/picture/domino_pool.png"))
    {
        std::cout << "Eror!\n";
    }
    dominoTexture.setSmooth(true);

    //������� ������ ����
    std::vector<Stone*> pile;
    //������� ������ ����
    std::vector<Stone*> field_right;
    std::vector<Stone*> field_left;
    //������� ������ �����
    std::vector<Stone*> player;
    //������� ������ ���������
    std::vector<Stone*> pc;

    //��������� ������ ������� �� ���������
    SetPile(pile, dominoTexture);

    //���������� ����
    Shuffle(pile);

    //������� ����� ������ � ����������
    SetGamers(pile, player);
    SetGamers(pile, pc);

    /*����������*/
    bool first_move = true;
    std::string move = "";
    std::string side = "";
    bool what_side = false;
    int num_of_stone = -1;

    int left_side_value = 0;
    int right_side_value = 0;

    bool no_move_player = false;
    bool no_move_pc = false;

    bool need_calc = true;

    //����� ����� ������ � ����������
    int player_points = 0;
    int pc_points = 0;

    //���������� �������
    sf::Clock clock; //������ �������
    sf::Time elapsed = clock.getElapsedTime(); //��������� �����

    ///////////////////////////////////////////////////////////////////////////////////////////
    stage_vibor = "game";
    //����� �� �����
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
        }

        window.clear(sf::Color(70, 130, 85));
        /************************************************/

        //��������
        dominoName(window);

        //�����������,�����������
        if (stage_vibor == "menu_start")
        {
            //����
            for (size_t i = 0; i < 3; i++)
            {
                window.draw(text_menu_start[i]);
            }

            //����������� �� ���� ���������
            keyItemUpdate(vibor, isButtonPressed, selItem, text_menu_start);
            //����������� �� ���� ������
            mouseItemUpdate(vibor, mouseHeld, selItem, text_menu_start, window);


            if (vibor == "One")
            {
                MyTgui(arr_users, current_user, "Registration");
                if (current_user.GetName().size() > 0)
                {
                    stage_vibor = "game";
                    vibor = "";
                }
                else
                {
                    stage_vibor = "menu_start";
                    vibor = "";
                }
            }
            else if (vibor == "Two")
            {
                MyTgui(arr_users, current_user, "Autorisation");
                if (current_user.GetName().size() > 0)
                {
                    stage_vibor = "game";
                    vibor = "";
                }
                else
                {
                    stage_vibor = "menu_start";
                    vibor = "";
                }
            }
            else if (vibor == "Exit")
            {
                window.close();
            }
        }
        //����
        else if (stage_vibor == "game")
        {
            //������ ������� ���� ������, ������� ������;
            SetPozStones(pile, 600, 100);
            SetPozStones(player, 30, 100);
            SetPozStones(pc, 30, 610);
            SetPozField_right(field_right, 520, 300);
            SetPozField_left(field_left, 490, 300);

            //������ ��� ����� � ������� ����
            DrawStones(pile, player, pc, window);
            DrawField(field_right, window, 'R');
            DrawField(field_left, window, 'L');

            //������ ������ ����� �� ������� ����
            TextOnTheField(font, window, current_user.GetName());
            LeftValueText(font, window, left_side_value);
            RightValueText(font, window, right_side_value);
            PlayerPoints(font, window, current_user.GetPoints());

            //��������� ������� ����
            mousePosWindow = sf::Mouse::getPosition(window);
            mousePosView = window.mapPixelToCoords(mousePosWindow);

            //������ ���
            if (first_move) //���������� ������� � ������ ����
            {
                StartText(font, window);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) //��� ������ ������ Enter ������� ��������, ���������� ����
                {
                    first_move = false;
                    move = FirstMove(pile, field_right, player, pc);
                    left_side_value = field_right.back()->GetSide_A();
                    right_side_value = field_right.back()->GetSide_A();
                }
            }

            if (!move.empty())
            {
                WhoMoveText(font_arial, window, move);
            }


            //��� ������
            if (move == "Player")
            {
                elapsed = clock.getElapsedTime();
                //1. �������� �� ������ ���������?
                if (IsMovePossible(player, right_side_value, left_side_value))
                {
                    /******************************************************************/
                    //���� ���� ������ � ����� ������� �������.
                    bool key = false;
                    if (what_side)
                    {
                        what_side = WhatSide(font_arial, window, side, key);
                        if (key)
                        {
                            if (side == "left")
                            {
                                if (player[num_of_stone]->GetSide_A() != left_side_value)
                                {
                                    player[num_of_stone]->RotateStone();
                                }
                                field_left.emplace_back(player[num_of_stone]);
                            }
                            else if (side == "right")
                            {
                                if (player[num_of_stone]->GetSide_B() != right_side_value)
                                {
                                    player[num_of_stone]->RotateStone();
                                }
                                field_right.emplace_back(player[num_of_stone]);
                            }
                            player.erase(player.begin() + num_of_stone);
                            move = "Pc";
                            no_move_player = false;
                            clock.restart();
                            key = false;
                        }
                    }
                    /******************************************************************/

                    //�������� ������ � ������ � ������ �� ������� ����
                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        if (mouseHeld == false)
                        {
                            mouseHeld = true;
                            for (size_t i = 0; i < player.size(); i++)
                            {
                                if (player[i]->GetSprite()->getGlobalBounds().contains(mousePosView))
                                {
                                    //��������� ����� �� ������� � ���� ������?
                                    if (IsBothPutPossible(player[i], right_side_value, left_side_value))
                                    {
                                        //���� ����� - �� ������ ������ � ����� ������� ������� � ����� ���������� � ���������� side
                                        what_side = true;
                                        num_of_stone = i;
                                    }
                                    //��������� ����� �� ������� �����?
                                    else if (IsPutLeftPossible(player[i], left_side_value))
                                    {
                                        if (player[i]->GetSide_A() != left_side_value)
                                        {
                                            player[i]->RotateStone();
                                        }
                                        //��������� ������ �� ����, ������� � ������, ��������� ������������ �������� �� ����
                                        field_left.emplace_back(player[i]);
                                        player.erase(player.begin() + i);
                                        move = "Pc";
                                        no_move_player = false;
                                        clock.restart();
                                    }
                                    //��������� ����� �� ������� ������?
                                    else if (IsPutRightPossible(player[i], right_side_value))
                                    {
                                        if (player[i]->GetSide_B() != right_side_value)
                                        {
                                            player[i]->RotateStone();
                                        }
                                        //��������� ������ �� ����, ������� � ������, ��������� ������������ �������� �� ����
                                        field_right.emplace_back(player[i]);
                                        player.erase(player.begin() + i);
                                        move = "Pc";
                                        no_move_player = false;
                                        clock.restart();
                                    }

                                }
                            }
                        }
                    }
                    else
                    {
                        mouseHeld = false;
                    }
                }
                else
                {
                    //���� � ���� ���� �����
                    if (!pile.empty())
                    {
                        //������� ����� ��� ����� ����� ������ �� ����
                        TextOnCenter(font_arial, window, "The Player takes a stone from a pile!");

                        //�������� ������ �� ���� � ��������� ��� ������
                        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                        {
                            if (mouseHeld == false)
                            {
                                mouseHeld = true;
                                for (size_t i = 0; i < pile.size(); i++)
                                {
                                    if (pile[i]->GetSprite()->getGlobalBounds().contains(mousePosView))
                                    {
                                        player.emplace_back(pile[i]);
                                        pile.erase(pile.begin() + i);
                                    }
                                }
                            }
                        }
                        else
                        {
                            mouseHeld = false;
                        }
                    }
                    else
                    {
                        TextOnCenter(font_arial, window, "No move Player");    //��������!!! ����� ����������
                        if (elapsed.asSeconds() > 4)
                        {
                            no_move_player = true;
                            move = "Pc";
                            clock.restart();
                        }
                    }
                }
            }


            //��� ����������
            if (move == "Pc")
            {
                elapsed = clock.getElapsedTime();
                if (elapsed.asSeconds() > 2)
                {
                    //�������� ����� ����� ������� ����� ��������� ���������
                    num_of_stone = RequiredStone(pc, right_side_value, left_side_value);

                    //���� ��������� � �������� ��������:
                    if (num_of_stone >= 0)
                    {
                        //��������� ����� �� ������� �����?
                        if (IsPutLeftPossible(pc[num_of_stone], left_side_value))
                        {
                            if (pc[num_of_stone]->GetSide_A() != left_side_value)
                            {
                                pc[num_of_stone]->RotateStone();
                            }
                            //��������� ������ �� ����
                            field_left.emplace_back(pc[num_of_stone]);
                            pc.erase(pc.begin() + num_of_stone);
                            move = "Player";
                            clock.restart();
                        }
                        else if (IsPutRightPossible(pc[num_of_stone], right_side_value))
                        {
                            if (pc[num_of_stone]->GetSide_B() != right_side_value)
                            {
                                pc[num_of_stone]->RotateStone();
                            }
                            //��������� ������ �� ����
                            field_right.emplace_back(pc[num_of_stone]);
                            pc.erase(pc.begin() + num_of_stone);
                            move = "Player";
                            clock.restart();
                        }
                    }
                    else
                    {
                        //���� � ���� ���� �����
                        if (!pile.empty())
                        {
                            //������� ����� ��� ����� ����� ������ �� ����
                            TextOnCenter(font_arial, window, "The PC takes a stone from a pile!");
                            if (elapsed.asSeconds() > 4)
                            {
                                pc.emplace_back(pile[0]);
                                pile.erase(pile.begin());
                                clock.restart();
                            }
                        }
                        else
                        {
                            TextOnCenter(font_arial, window, "No move PC");    //��������!!! ����� ����������
                            if (elapsed.asSeconds() > 4)
                            {
                                no_move_pc = true;
                                move = "Player";
                                clock.restart();
                            }
                        }
                    }
                }
            }

            //����
            if (no_move_player && no_move_pc)
            {
                move = "";
                TextOnCenter(font_arial, window, "FISSSSSHHHHHHHH!!!!!!  Please press Enter to continue.");
                EndGameMenu(isButtonPressed, stage_vibor);
                if (need_calc)
                {
                    need_calc = false;
                    player_points = (150 - CalculatePoints(player)) + current_user.GetPoints();
                    current_user.SetPoints(player_points);
                    AddPointsUser(arr_users, current_user);
                    SortVector(arr_users);
                }
                
            }


            //����� ����������
            if (player.empty())
            {
                move = "";
                TextOnCenter(font_arial, window, "Player WIN! Please press Enter to continue.");
                EndGameMenu(isButtonPressed, stage_vibor);

                if (need_calc)
                {
                    need_calc = false;
                    player_points = 150 + current_user.GetPoints();
                    current_user.SetPoints(player_points);
                    AddPointsUser(arr_users, current_user);
                    SortVector(arr_users);
                }
            }
            else if (pc.empty())
            {
                move = "";
                TextOnCenter(font_arial, window, "Pc WIN!  Please press Enter to continue.");
                EndGameMenu(isButtonPressed, stage_vibor);
                if (need_calc)
                {
                    need_calc = false;
                    player_points = (150 - CalculatePoints(player)) + current_user.GetPoints();
                    current_user.SetPoints(player_points);
                    AddPointsUser(arr_users, current_user);
                    SortVector(arr_users);
                } 
            }


            //��������� �������� ������ � ����� ��� ����������� �� ������
            if (!field_left.empty())
            {
                left_side_value = field_left.back()->GetSide_B();
            }
            if (!field_right.empty())
            {
                right_side_value = field_right.back()->GetSide_A();
            }

        }
        else if (stage_vibor == "menu_end")
        {
            //����
            for (size_t i = 0; i < 3; i++)
            {
                window.draw(text_menu_end[i]);
            }

            //����������� �� ���� ���������
            keyItemUpdate(vibor, isButtonPressed, selItem, text_menu_end);
            //����������� �� ���� ������
            mouseItemUpdate(vibor, mouseHeld, selItem, text_menu_end, window);


            if (vibor == "One")
            {
                Stone::idCounter = 0;
                bool tmep_key = false;
                bool clear_key = false;

                if (CleanAllMemory(pile, field_right, field_left, player, pc))
                {
                    tmep_key = InitGame(pile, player, pc, dominoTexture);
                }

                if (tmep_key)
                {
                    first_move = true;
                    move = "";
                    side = "";
                    what_side = false;
                    num_of_stone = -1;
                    left_side_value = 0;
                    right_side_value = 0;

                    no_move_player = false;
                    no_move_pc = false;
                    need_calc = true;
                    stage_vibor = "game";
                    vibor = "";
                    clock.restart();
                }
            }
            else if (vibor == "Two")
            {
                TableWindow(arr_users);
                stage_vibor = "menu_end";
                vibor = "";
                std::cout << "Table!\n";
            }
            else if (vibor == "Exit")
            {
                window.close();
            }
        }






        window.display();
    }

    //������ ������� ������������� � ���� ��� ������ �� ����
    if (current_user.GetName().size() > 0)
    {
        WriteVectorToFile(arr_users);
    }

    //������������ ������
    CleanAllMemory(pile, field_right, field_left, player, pc);

    return 0;
}