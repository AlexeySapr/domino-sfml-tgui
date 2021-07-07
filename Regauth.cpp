#include "Regauth.h"

void WriteVectorToFile(std::vector<User>& arr_users)
{
    //адрес и имя файла
    std::string path = "test_users.txt";
    //объект класса (для чтения и записи)
    std::fstream finout;
    //открываем файловый поток, если файла нет, он создастся
    finout.open(path, std::fstream::out);

    //создаем временные переменные
    std::string temp_name = "";
    std::string temp_pass = "";
    int temp_point = 0;

    //если файл не открылся - ошибка!
    if (!finout.is_open())
    {
        std::cout << "eror!\n";
        exit(1);
    }
    //иначе записываем вектор пользователей в файл
    else
    {
        for (User user : arr_users)
        {
            temp_name = user.GetName();
            temp_pass = user.GetPass();
            temp_point = user.GetPoints();
            finout << temp_name << " " << temp_pass << " " << temp_point << "\n";
        }
    }
    finout.close();
}

void ReadVectorFromFile(std::vector<User>& arr_users)
{
    //адрес и имя файла
    std::string path = "test_users.txt";
    //объект класса (для чтения и записи)
    std::fstream finout;
    //открываем файловый поток, если файла нет, он создастся
    finout.open(path, std::fstream::in | std::fstream::app);

    //создаем временные переменные
    std::string temp_name = "";
    std::string temp_pass = "";
    int temp_point = 0;
    User user;

    //если файл не открылся - ошибка!
    if (!finout.is_open())
    {
        std::cout << "eror!\n";
        exit(1);
    }
    //иначе считываем данные из файла в вектор пользователей
    else
    {
        while (!finout.eof())
        {
            finout >> temp_name >> temp_pass >> temp_point;
            user.SetName(temp_name);
            user.SetPass(temp_pass);
            user.SetPoints(temp_point);
            arr_users.push_back(user);
        }
    }
    finout.close();
    arr_users.pop_back();
}

bool NameValid(std::string name)
{
    bool flag = true;
    for (size_t i = 0; i < name.length(); i++)
    {
        if (!(name[i] > 64 && name[i] < 91) &&
            !(name[i] > 96 && name[i] < 123) &&
            !(name[i] > 47 && name[i] < 58))
        {
            flag = false;
        }
    }
    if (flag)
    {
        return true;
    }
    return false;
}

bool Login(tgui::EditBox::Ptr username, tgui::EditBox::Ptr password, tgui::Label::Ptr label)
{
    std::string user = static_cast<std::string>(username->getText());
    std::string pass = static_cast<std::string>(password->getText());

    if (NameValid(user))
    {
        //std::cout << "Username: " << user << std::endl;
        //std::cout << "Password: " << pass << std::endl;
        return true;
    }
    else
    {
        label->setVisible(true);
        return false;
    }
}

bool IsUser(std::vector<User>& arr_users, std::string name, std::string pass)
{
    if (!arr_users.empty()) //если вектор не пустой
    {
        for (User user : arr_users)
        {
            if (user.GetName() == name || user.GetPass() == pass)
            {
                return true;
            }
        }
    }

    return false;
}

bool IsUser(std::string name, std::string pass, std::vector<User>& arr_users)
{
    for (User user : arr_users)
    {
        if (user.GetName() == name && user.GetPass() == pass)
        {
            return true;
        }
    }

    return false;
}

void updateTextSize(tgui::GuiBase& gui)
{
    // Update the text size of all widgets in the gui, based on the current window height
    const float windowHeight = gui.getView().getRect().height;
    gui.setTextSize(static_cast<unsigned int>(0.05f * windowHeight)); // 5% of height
}

void MyTgui(std::vector<User>& arr_users, User& user, std::string regauth)
{
    //Создаем окно регистрации
    sf::RenderWindow window(sf::VideoMode(400, 300), "TGUI window", sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    tgui::Gui gui(window);

    ////Позиция мыши
    //sf::Vector2i mousePosTgui;
    //sf::Vector2f mousePosViewTgui;
    //bool mouseHeldTgui = false;

    //Создаем виджет ГУИ
    updateTextSize(gui);
    //gui.onViewChange([&gui] { updateTextSize(gui); });

    // Create the background image
    auto picture = tgui::Picture::create("External/picture/background_login.png");
    picture->setSize({ "100%", "100%" });
    gui.add(picture);

    // Create the username edit box
    auto editBoxUsername = tgui::EditBox::create();
    editBoxUsername->setSize({ "66.67%", "12.5%" });
    editBoxUsername->setPosition({ "16.67%", "16.67%" });
    editBoxUsername->setDefaultText("Username");
    editBoxUsername->setInputValidator("[a-zA-Z0-9_()@{}]*");
    editBoxUsername->setMaximumCharacters(30);
    gui.add(editBoxUsername);

    // Create the password edit box
    auto editBoxPassword = tgui::EditBox::copy(editBoxUsername);
    editBoxPassword->setPosition({ "16.67%", "41.6%" });
    //editBoxPassword->setPasswordCharacter('*');
    editBoxPassword->setDefaultText("Password");
    editBoxPassword->setMaximumCharacters(15);
    gui.add(editBoxPassword);

    // Create the login button
    auto button = tgui::Button::create();
    if (regauth == "Registration")
    {
        button->setText("Registration");
    }
    else if (regauth == "Autorisation")
    {
        button->setText("Login");
    }
    button->setSize({ "50%", "16.67%" });
    button->setPosition({ "25%", "70%" });
    gui.add(button);

    //Labels
    auto label = tgui::Label::create();
    label->setText("Incorrect data!");
    label->setPosition({ "30%", "5%" });
    label->setVisible(false);
    //label->setTextSize(2);
    gui.add(label);

    auto label_2 = tgui::Label::copy(label);
    label_2->setText("User or password already exists");
    label_2->setPosition({ "18%", "5%" });
    label_2->setVisible(false);
    //label_2->setTextSize(2);
    gui.add(label_2);

    auto label_3 = tgui::Label::copy(label_2);
    label_3->setText("No registered users. You need to register!");
    label_3->setPosition({ "13%", "5%" });
    label_3->setVisible(false);
    //label_2->setTextSize(2);
    gui.add(label_3);

    while (window.isOpen())
    {
        sf::Event tev;
        while (window.pollEvent(tev))
        {
            if (tev.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (tev.type == sf::Event::KeyPressed)
            {
                if (tev.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
                //else if (tev.key.code == sf::Keyboard::Enter)
                //{
                //    if (login(editBoxUsername, editBoxPassword, label))
                //    {
                //        std::string user = static_cast<std::string>(editBoxUsername->getText());
                //        std::string pass = static_cast<std::string>(editBoxPassword->getText());

                //        temp_user.SetName(user);
                //        temp_user.SetPass(pass);
                //        temp_user.SetPoints(0);
                //        arr_users.push_back(temp_user);
                //        std::cout << "OK!" << std::endl;

                //        window.close();
                //    }
                //}
            }
            if (button->isMouseDown())
            {
                std::string user_name = static_cast<std::string>(editBoxUsername->getText());
                std::string user_pass = static_cast<std::string>(editBoxPassword->getText());

                if (regauth == "Registration")
                {
                    if (IsUser(arr_users, user_name, user_pass))
                    {
                        label_2->setVisible(true);
                    }
                    else
                    {
                        user.SetName(user_name);
                        user.SetPass(user_pass);
                        user.SetPoints(0);
                        arr_users.push_back(user);
                        std::cout << "OK!" << std::endl;

                        window.close();
                    }
                }
                else if (regauth == "Autorisation")
                {
                    if (arr_users.empty())
                    {
                        label_3->setVisible(true);
                    }
                    else if (IsUser(user_name, user_pass, arr_users))
                    {
                        user.SetName(user_name);
                        user.SetPass(user_pass);
                        std::cout << "OK!" << std::endl;

                        window.close();
                    }
                    else
                    {
                        label->setVisible(true);
                    }
                }
            }
            if (editBoxUsername->isFocused() || editBoxPassword->isFocused())
            {
                label->setVisible(false);
                label_2->setVisible(false);
                label_3->setVisible(false);
            }

            //информируем ГУИ о событии
            gui.handleEvent(tev);
        }

        window.clear();

        gui.draw();

        window.display();
    }
}