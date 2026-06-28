#include <SFML/Graphics.hpp>
#include <iostream>
#include "System.h"
#include "Item.h"

using namespace std;

enum Mode { MENU, ADD_LOST, ADD_FOUND, SEARCH };
enum Step { NONE, NAME, DESC, LOCATION };

// ---------------- BUTTON ----------------
struct Button
{
    sf::RectangleShape box;
    sf::Text text;

    Button(sf::Font& font, string label, sf::Vector2f pos)
        : text(font, label, 20)
    {
        box.setSize(sf::Vector2f(200.f, 50.f));
        box.setPosition(pos);
        box.setFillColor(sf::Color(80, 80, 80));

        text.setFillColor(sf::Color::White);
        text.setPosition(sf::Vector2f(pos.x + 10.f, pos.y + 10.f));
    }

    bool clicked(sf::Vector2f m)
    {
        return box.getGlobalBounds().contains(m);
    }

    void draw(sf::RenderWindow& w)
    {
        w.draw(box);
        w.draw(text);
    }
};

int main()
{
    System sys;
    sys.loadLost("lost.txt");
    sys.loadFound("found.txt");

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(1000, 650)), "Lost & Found System");

    sf::Font font;
    if (!font.openFromFile("arial.ttf"))
    {
        cout << "Font load failed\n";
        return 0;
    }

    Button b1(font, "Add Lost",  {50, 80});
    Button b2(font, "Add Found", {50, 150});
    Button b3(font, "Show All",  {50, 220});
    Button b4(font, "Search",    {50, 290});

    Mode mode = MENU;
    Step step = NONE;

    string name, desc, loc, query;

    sf::Text ui(font, "Ready", 20);
    ui.setPosition(sf::Vector2f(320.f, 30.f));

    sf::Text output(font, "", 18);
    output.setPosition(sf::Vector2f(320.f, 100.f));

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            // ---------------- MOUSE ----------------
            if (event->is<sf::Event::MouseButtonPressed>())
            {
                auto mb = event->getIf<sf::Event::MouseButtonPressed>();
                if (!mb) continue;

                sf::Vector2f mousePos((float)mb->position.x, (float)mb->position.y);

                if (b1.clicked(mousePos))
                {
                    mode = ADD_LOST;
                    step = NAME;
                    name = desc = loc = "";
                    output.setString("Enter LOST NAME");
                }

                if (b2.clicked(mousePos))
                {
                    mode = ADD_FOUND;
                    step = NAME;
                    name = desc = loc = "";
                    output.setString("Enter FOUND NAME");
                }

                if (b3.clicked(mousePos))
                {
                    output.setString(sys.showAll()); // Handled by System class UI format
                }

                if (b4.clicked(mousePos))
                {
                    mode = SEARCH;
                    query = "";
                    output.setString("Type search...");
                }
            }

            // ---------------- KEYBOARD INPUT ----------------
            if (event->is<sf::Event::TextEntered>())
            {
                auto te = event->getIf<sf::Event::TextEntered>();
                if (!te) continue;

                char c = static_cast<char>(te->unicode);

                // BACKSPACE
                if (te->unicode == 8)
                {
                    if (mode == SEARCH && !query.empty())
                        query.pop_back();

                    else if (mode == ADD_LOST)
                    {
                        if (step == NAME && !name.empty()) name.pop_back();
                        else if (step == DESC && !desc.empty()) desc.pop_back();
                        else if (step == LOCATION && !loc.empty()) loc.pop_back();
                    }
                    else if (mode == ADD_FOUND)
                    {
                        if (step == NAME && !name.empty()) name.pop_back();
                        else if (step == DESC && !desc.empty()) desc.pop_back();
                        else if (step == LOCATION && !loc.empty()) loc.pop_back();
                    }
                }

                // ENTER
                else if (te->unicode == 13)
                {
                    if (mode == ADD_LOST)
                    {
                        if (step == NAME)
                        {
                            step = DESC;
                            output.setString("Enter DESCRIPTION");
                        }
                        else if (step == DESC)
                        {
                            step = LOCATION;
                            output.setString("Enter LOCATION");
                        }
                        else if (step == LOCATION)
                        {
                            sys.addLost({name, desc, loc});
                            sys.saveLost("lost.txt");
                            output.setString("LOST ITEM SAVED");
                            mode = MENU;
                            step = NONE; // Clear state
                        }
                    }

                    else if (mode == ADD_FOUND)
                    {
                        if (step == NAME)
                        {
                            step = DESC;
                            output.setString("Enter DESCRIPTION");
                        }
                        else if (step == DESC)
                        {
                            step = LOCATION;
                            output.setString("Enter LOCATION");
                        }
                        else if (step == LOCATION)
                        {
                            sys.addFound({name, desc, loc});
                            sys.saveFound("found.txt");
                            output.setString("FOUND ITEM SAVED");
                            mode = MENU;
                            step = NONE; // Clear state
                        }
                    }

                    else if (mode == SEARCH)
                    {
                        output.setString(sys.search(query)); // Handled by System class UI format
                        mode = MENU;
                    }
                }

                // NORMAL CHAR
                else if (te->unicode >= 32 && te->unicode < 127)
                {
                    if (mode == SEARCH)
                        query += c;

                    else if (mode == ADD_LOST)
                    {
                        if (step == NAME) name += c;
                        else if (step == DESC) desc += c;
                        else if (step == LOCATION) loc += c;
                    }

                    else if (mode == ADD_FOUND)
                    {
                        if (step == NAME) name += c;
                        else if (step == DESC) desc += c;
                        else if (step == LOCATION) loc += c;
                    }
                }
            }
        }

        // ---------------- LIVE UI UPDATE ----------------
        if (mode == ADD_LOST)
        {
            if (step == NAME)
                ui.setString("LOST NAME: " + name);
            else if (step == DESC)
                ui.setString("LOST DESC: " + desc);
            else if (step == LOCATION)
                ui.setString("LOST LOCATION: " + loc);
        }
        else if (mode == ADD_FOUND)
        {
            if (step == NAME)
                ui.setString("FOUND NAME: " + name);
            else if (step == DESC)
                ui.setString("FOUND DESC: " + desc);
            else if (step == LOCATION)
                ui.setString("FOUND LOCATION: " + loc);
        }
        else if (mode == SEARCH)
        {
            ui.setString("SEARCH: " + query);
        }
        else
        {
            ui.setString("MENU - Click a button");
        }

        // ---------------- DRAW ----------------
        window.clear(sf::Color(30, 30, 30));

        b1.draw(window);
        b2.draw(window);
        b3.draw(window);
        b4.draw(window);

        window.draw(ui);
        window.draw(output);

        window.display();
    }

    return 0;
}