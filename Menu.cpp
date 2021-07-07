#include "Menu.h"

void dominoName(sf::RenderWindow& window)
{

    sf::Font font;
    if (!font.loadFromFile("External/fonts/Allura.ttf"))
    {
        std::cout << "Failed to load font!\n";
    }

    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setOutlineThickness(1.f);
    text.setFillColor(sf::Color::Magenta);
    text.setLetterSpacing(2.f);
    text.setString("DOMINO");
    //text.setOrigin(text.getGlobalBounds().width / 2, text.getGlobalBounds().height / 2);
    //text.setPosition(window.getSize().x / 2, window.getSize().y / 100);
    text.setPosition(450.f, 2.f);
    window.draw(text);
}

void dominoMenu(sf::Font& font, sf::Text text[3], sf::RenderWindow& window, std::string key)
{
    //строка №1
    text[0].setFont(font);
    text[0].setCharacterSize(40);
    text[0].setOutlineThickness(2.f);
    text[0].setFillColor(sf::Color::White);
    text[0].setLetterSpacing(4.f);
    if (key == "start")
    {
        text[0].setString("Registration");
    }
    else if (key == "end")
    {
        text[0].setString("Play again");
    }

    text[0].setOrigin(text[0].getLocalBounds().width / 2, text[0].getLocalBounds().height / 2);
    text[0].setPosition(window.getSize().x / 2, window.getSize().y / 5);

    //строка №2
    text[1].setFont(font);
    text[1].setCharacterSize(40);
    text[1].setOutlineThickness(2.f);
    text[1].setFillColor(sf::Color::Blue);
    text[1].setLetterSpacing(4.f);
    if (key == "start")
    {
        text[1].setString("Authorization");
    }
    else if (key == "end")
    {
        text[1].setString("Results table");
    }

    text[1].setOrigin(text[1].getLocalBounds().width / 2, text[1].getLocalBounds().height / 2);
    text[1].setPosition(window.getSize().x / 2, window.getSize().y / 3);

    //строка №3
    text[2].setFont(font);
    text[2].setCharacterSize(40);
    text[2].setOutlineThickness(2.f);
    text[2].setFillColor(sf::Color::Blue);
    text[2].setLetterSpacing(4.f);
    text[2].setString("Exit");
    text[2].setOrigin(text[2].getLocalBounds().width / 2, text[2].getLocalBounds().height / 2);
    text[2].setPosition(window.getSize().x / 2, window.getSize().y / 2);
}

void moveUpMenu(int& selItem, sf::Text text[3])
{
    if (selItem - 1 >= 0)
    {
        text[selItem].setFillColor(sf::Color::Blue);
        selItem--;
        text[selItem].setFillColor(sf::Color::White);
    }
}

void moveDownMenu(int& selItem, sf::Text text[3])
{
    if (selItem + 1 < 3)
    {
        text[selItem].setFillColor(sf::Color::Blue);
        selItem++;
        text[selItem].setFillColor(sf::Color::White);
    }
}

void keyItemUpdate(std::string& vibor, bool& isButtonPressed, int& selItem, sf::Text text[3])
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
    {
        if (isButtonPressed == false)
        {
            isButtonPressed = true;
            moveUpMenu(selItem, text);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
    {
        if (isButtonPressed == false)
        {
            isButtonPressed = true;
            moveDownMenu(selItem, text);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter))
    {
        if (isButtonPressed == false)
        {
            isButtonPressed = true;
            switch (selItem)
            {
            case 0:
                vibor = "One";
                break;
            case 1:
                vibor = "Two";
                break;
            case 2:
                vibor = "Exit";
                break;
            }
        }
    }
    else
    {
        isButtonPressed = false;
    }
}

void mouseItemUpdate(std::string& vibor, bool& isButtonPressed, int& selItem, sf::Text text[3], sf::RenderWindow& window)
{
    //Позиция мыши
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;
    //обновляем позицию мыши
    mousePosWindow = sf::Mouse::getPosition(window);
    mousePosView = window.mapPixelToCoords(mousePosWindow);

    for (size_t i = 0; i < 3; i++)
    {
        if (selItem != i)
        {
            text[i].setFillColor(sf::Color::Blue);
        }
        if (text[i].getGlobalBounds().contains(mousePosView))
        {
            text[i].setFillColor(sf::Color::White);
            selItem = i;
        }
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (isButtonPressed == false)
        {
            isButtonPressed = true;
            switch (selItem)
            {
            case 0:
                vibor = "One";
                break;
            case 1:
                vibor = "Two";
                break;
            case 2:
                vibor = "Exit";
                break;
            }
        }

    }
    else
    {
        isButtonPressed = false;
    }
}