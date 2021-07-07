#include "Drawing.h"

void SetPile(std::vector<Stone*>& pile, sf::Texture& dominoTexture)
{
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
}

void Shuffle(std::vector<Stone*>& pile)
{
    int r1, r2;
    for (int i = 0; i < 100; ++i) {
        r1 = rand() % pile.size();
        r2 = rand() % pile.size();
        if (r1 != r2)
        {
            std::swap(pile[r1], pile[r2]);
        }
    }
}

const void SetPozStones(std::vector<Stone*>& vect, float x, float y)
{
    for (size_t i = 0; i < vect.size(); i++)
    {
        vect[i]->GetSprite()->setPosition(x, y);
        vect[i]->GetBackSprite()->setPosition(x, y);
        x += 30.f;
    }
}

const void SetPozField_right(std::vector<Stone*>& vect, float x, float y)
{
    for (size_t i = 0; i < vect.size(); i++)
    {
        if (i < 9)
        {
            if (vect[i]->GetDir() == 'V')
            {
                vect[i]->GetSprite()->setPosition(x, y);
            }
            else if (vect[i]->GetDir() == 'H')
            {
                if (i > 0)
                {
                    if (vect[i - 1]->GetDir() == 'H')
                    {
                        x += 12.f;
                    }
                    else
                    {
                        x += 6.f;
                    }
                    vect[i]->GetSprite()->setPosition(x, y);
                }
                else
                {
                    x += 6.f;
                    vect[i]->GetSprite()->setPosition(x, y);
                }
                x += 6.f;
            }
            x += 30.f;
        }
        else if (i >= 9 && i < 12)
        {
            if (vect[i]->GetDir() == 'V')
            {
                if (i == 9)
                {
                    vect[i]->GetSprite()->setPosition(x, y);
                }
                else
                {
                    y += 48.f;
                    vect[i]->GetSprite()->setPosition(x, y);
                }
            }
            else if (vect[i]->GetDir() == 'H')
            {
                if (i == 9)
                {
                    if (vect[i - 1]->GetDir() == 'V')
                    {
                        y += 48.f;
                        x -= 30.f;
                    }
                    else
                    {
                        y += 12.f;
                    }
                    vect[i]->GetSprite()->setPosition(x, y);
                }
                else
                {
                    y += 48.f;
                    vect[i]->GetSprite()->setPosition(x, y);
                }
            }
        }
        else if (i >= 12)
        {
            if (vect[i]->GetDir() == 'V')
            {
                if (i == 12)
                {
                    y += 36.f;
                }
                else
                {
                    x -= 36.f;
                }
            }
            else if (vect[i]->GetDir() == 'H')
            {
                if (i == 12)
                {
                    y += 12.f;
                    x -= 36.f;
                }
                else if (i == 8 && vect[i - 1]->GetDir() == 'V')
                {
                    x -= 48.f;
                }
                else
                {
                    if (vect[i - 1]->GetDir() == 'V')
                    {
                        x -= 36.f;
                    }
                    else
                    {
                        x -= 48.f;
                    }
                }
            }
            vect[i]->GetSprite()->setPosition(x, y);
        }
    }
}

const void SetPozField_left(std::vector<Stone*>& vect, float x, float y)
{
    for (size_t i = 0; i < vect.size(); i++)
    {
        if (i < 9)
        {
            if (vect[i]->GetDir() == 'V')
            {
                vect[i]->GetSprite()->setPosition(x, y);
            }
            else if (vect[i]->GetDir() == 'H')
            {
                if (i > 0)
                {
                    if (vect[i - 1]->GetDir() == 'H')
                    {
                        x -= 12.f;
                    }
                    else
                    {
                        x -= 6.f;
                    }
                    vect[i]->GetSprite()->setPosition(x, y);
                }
                else
                {
                    x -= 6.f;
                    vect[i]->GetSprite()->setPosition(x, y);
                }
                x -= 6.f;
            }
            x -= 30.f;
        }
        else if (i >= 9 && i < 12)
        {
            if (vect[i]->GetDir() == 'V')
            {
                if (i == 9)
                {
                    vect[i]->GetSprite()->setPosition(x, y);
                }
                else
                {
                    y += 48.f;
                    vect[i]->GetSprite()->setPosition(x, y);
                }
            }
            else if (vect[i]->GetDir() == 'H')
            {
                if (i == 9)
                {
                    if (vect[i - 1]->GetDir() == 'V')
                    {
                        y += 48.f;
                        x += 30.f;
                    }
                    else
                    {
                        y += 12.f;
                    }
                    vect[i]->GetSprite()->setPosition(x, y);
                }
                else
                {
                    y += 48.f;
                    vect[i]->GetSprite()->setPosition(x, y);
                }
            }
        }
        else if (i >= 12)
        {
            if (vect[i]->GetDir() == 'V')
            {
                if (i == 12)
                {
                    y += 36.f;
                }
                else
                {
                    x += 36.f;
                }
            }
            else if (vect[i]->GetDir() == 'H')
            {
                if (i == 12)
                {
                    y += 12.f;
                    x += 36.f;
                }
                else if (i == 8 && vect[i - 1]->GetDir() == 'V')
                {
                    x += 48.f;
                }
                else
                {
                    if (vect[i - 1]->GetDir() == 'V')
                    {
                        x += 36.f;
                    }
                    else
                    {
                        x += 48.f;
                    }
                }
            }
            vect[i]->GetSprite()->setPosition(x, y);
        }
    }
}

void SetGamers(std::vector<Stone*>& pile, std::vector<Stone*>& gamer)
{
    for (size_t i = 0; i < 7; i++)
    {
        gamer.emplace_back(pile[i]);
        pile.erase(pile.begin() + i);
    }
}

const void DrawStones(std::vector<Stone*>& pile,
    std::vector<Stone*>& player,
    std::vector<Stone*>& pc,
    sf::RenderTarget& target)
{
    for (auto& stone : pile)
    {
        target.draw(*stone->GetBackSprite());
    }

    for (auto& stone : player)
    {
        target.draw(*stone->GetSprite());
    }

    for (auto& stone : pc)
    {
        target.draw(*stone->GetBackSprite());
    }
}

void DrawField(std::vector<Stone*>& field, sf::RenderTarget& target, char side)
{
    for (size_t i = 0; i < field.size(); i++)
    {
        if (i < 9)
        {
            if (field[i]->GetDir() == 'H')
            {
                if (field[i]->GetRotated() == 'N')
                {
                    field[i]->GetSprite()->setRotation(90.f);
                }
                else if (field[i]->GetRotated() == 'Y')
                {
                    field[i]->GetSprite()->setRotation(270.f);
                }
            }
        }
        else if (i >= 9 && i < 12)
        {
            if (side == 'R' && field[i]->GetRotated() == 'N')
            {
                field[i]->GetSprite()->setRotation(180.f);
            }
            else if (side == 'L' && field[i]->GetRotated() == 'Y')
            {
                field[i]->GetSprite()->setRotation(180.f);
            }
        }
        else if (i >= 12)
        {
            if (i == 12 && field[i]->GetDir() == 'V')
            {
                field[i]->GetSprite()->setRotation(90.f);
            }
            else if (field[i]->GetDir() == 'H')
            {
                if (field[i]->GetRotated() == 'N')
                {
                    field[i]->GetSprite()->setRotation(270.f);
                }
                else if (field[i]->GetRotated() == 'Y')
                {
                    field[i]->GetSprite()->setRotation(90.f);
                }
            }
        }
        target.draw(*field[i]->GetSprite());
    }
}

const void TextOnTheField(sf::Font& font, sf::RenderWindow& window, std::string current_user)
{
    float y_coord = 30;
    sf::Text player_text;
    player_text.setFont(font);
    player_text.setCharacterSize(30);
    player_text.setOutlineThickness(1.f);
    player_text.setFillColor(sf::Color::Blue);
    player_text.setLetterSpacing(2.f);
    player_text.setString("Players stones: " + current_user);
    player_text.setPosition(20.f, 10.f + y_coord);
    window.draw(player_text);

    sf::Text pc_text;
    pc_text.setFont(font);
    pc_text.setCharacterSize(30);
    pc_text.setOutlineThickness(1.f);
    pc_text.setFillColor(sf::Color::Blue);
    pc_text.setLetterSpacing(2.f);
    pc_text.setString("Pc's stones:");
    pc_text.setPosition(20.f, 520.f + y_coord);
    window.draw(pc_text);

    sf::Text field_text;
    field_text.setFont(font);
    field_text.setCharacterSize(30);
    field_text.setOutlineThickness(1.f);
    field_text.setFillColor(sf::Color::Blue);
    field_text.setLetterSpacing(2.f);
    field_text.setString("Game field:");
    field_text.setPosition(480.f, 200.f + y_coord);
    window.draw(field_text);

    sf::Text pile_text;
    pile_text.setFont(font);
    pile_text.setCharacterSize(30);
    pile_text.setOutlineThickness(1.f);
    pile_text.setFillColor(sf::Color::Blue);
    pile_text.setLetterSpacing(2.f);
    pile_text.setString("Pile:");
    pile_text.setPosition(590.f, 10.f + y_coord);
    window.draw(pile_text);
}

const void StartText(sf::Font& font, sf::RenderWindow& window)
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setOutlineThickness(1.f);
    text.setFillColor(sf::Color::Blue);
    text.setLetterSpacing(2.f);
    text.setString("Press Enter to start!");
    text.setPosition(425.f, 180.f);
    window.draw(text);
}

const void TextOnCenter(sf::Font& font, sf::RenderWindow& window, std::string message)
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setOutlineThickness(1.f);
    text.setFillColor(sf::Color::Magenta);
    text.setLetterSpacing(1.f);
    text.setString(message);
    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
    text.setPosition(525.f, 180.f);
    window.draw(text);
}

const void WhoMoveText(sf::Font& font, sf::RenderWindow& window, std::string message)
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setOutlineThickness(1.f);
    text.setFillColor(sf::Color::Magenta);
    text.setLetterSpacing(1.f);
    text.setString("Now move: " + message);
    text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
    text.setPosition(500.f, 700.f);
    window.draw(text);
}

const void LeftValueText(sf::Font& font, sf::RenderWindow& window, int number)
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(15);
    text.setOutlineThickness(0.1f);
    text.setFillColor(sf::Color::Blue);
    text.setLetterSpacing(2.f);
    text.setString("Left value: " + std::to_string(number));
    text.setPosition(800.f, 160.f);
    window.draw(text);
}

const void RightValueText(sf::Font& font, sf::RenderWindow& window, int number)
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(15);
    text.setOutlineThickness(0.1f);
    text.setFillColor(sf::Color::Blue);
    text.setLetterSpacing(2.f);
    text.setString("Right value: " + std::to_string(number));
    text.setPosition(800.f, 180.f);
    window.draw(text);
}

const void PlayerPoints(sf::Font& font, sf::RenderWindow& window, int number)
{
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(15);
    text.setOutlineThickness(0.1f);
    text.setFillColor(sf::Color::Blue);
    text.setLetterSpacing(2.f);
    text.setString("Player points: " + std::to_string(number));
    text.setPosition(800.f, 220.f);
    window.draw(text);
}
