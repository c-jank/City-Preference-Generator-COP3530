#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <string>
#include <SFML/graphics.hpp>
using namespace std;



string RemoveCursor(string str){
    if(str.find('|') != string::npos){
        str.erase(str.find('|'));
    }
    return str;
}

int main(int argc, char **argv) {


    //Declaring window, text entities, font
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "City Preference Generator");
    sf::Text title;
    sf::Text pop;
    sf::Text poptxt;
    sf::Text state;
    sf::Text statetxt;
    sf::Text elv;
    sf::Text elvtxt;
    sf::Text searchtext;
    sf::Text ppop;
    sf::Text pstate;
    sf::Text pelv;
    sf::Text poppr;
    sf::Text statepr;
    sf::Text elvpr;
    sf::Font font;
    font.loadFromFile("font.ttf");

    //String Containers to catch input
    string popstr = "";
    string statestr = "";
    string elvstr = "";
    string popp = "";
    string statep = "";
    string elvp = "";
    //Texture for text boxes
    sf::Texture texture;
    texture.loadFromFile("download.png");

    //Text Box Setup
    sf::Sprite popbox;
    popbox.setTextureRect(sf::IntRect(0,0,200,50));
    popbox.setTexture(texture);
    popbox.setPosition(400,190);

    sf::Sprite statebox;
    statebox.setTextureRect(sf::IntRect(0,0,200,50));
    statebox.setTexture(texture);
    statebox.setPosition(400,290);

    sf::Sprite elvbox;
    elvbox.setTextureRect(sf::IntRect(0,0,200,50));
    elvbox.setTexture(texture);
    elvbox.setPosition(400,390);

    sf::Sprite searchbox;
    searchbox.setTextureRect(sf::IntRect (0,0,200,50));
    searchbox.setTexture(texture);
    searchbox.setPosition(400,500);

    sf::Sprite ppopbox;
    ppopbox.setTextureRect(sf::IntRect(0,0,50,50));
    ppopbox.setTexture(texture);
    ppopbox.setPosition(750,190);

    sf::Sprite pstatebox;
    pstatebox.setTextureRect(sf::IntRect (0,0,50,50));
    pstatebox.setTexture(texture);
    pstatebox.setPosition(750,290);

    sf::Sprite pelvbox;
    pelvbox.setTextureRect(sf::IntRect(0,0,50,50));
    pelvbox.setTexture(texture);
    pelvbox.setPosition(750, 390);

    sf::Sprite resultbox;

    sf::Vector2i mpos;
    while (window.isOpen())
    {
        sf::Event event;
        window.setKeyRepeatEnabled(false);
        //Event Handling
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if(event.type == sf::Event::TextEntered) {
                //Determine which text box is selected, collect input
                if(popbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))){
                    popstr = RemoveCursor(popstr);
                    if(event.text.unicode<128){
                        if(event.text.unicode == 8){
                            popstr = popstr.substr(0, popstr.size()-1);
                            popstr += '|';
                        }
                        else{
                            popstr += event.text.unicode;
                            popstr += '|';
                        }
                    }
                }
                if(statebox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))){
                    statestr = RemoveCursor(statestr);
                    if(event.text.unicode<128){
                        if(event.text.unicode == 8){
                            statestr = statestr.substr(0, statestr.size()-1);
                            statestr += '|';
                        }
                        else{
                            statestr += event.text.unicode;
                            statestr += '|';
                        }
                    }
                }
                if(elvbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))){
                    elvstr = RemoveCursor(elvstr);
                    if(event.text.unicode<128){
                        if(event.text.unicode == 8){
                            elvstr = elvstr.substr(0,elvstr.size()-1);
                            elvstr += '|';
                        }
                        else{
                            elvstr += event.text.unicode;
                            elvstr += '|';
                        }
                    }
                }
                if(ppopbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))){
                    popp = RemoveCursor(popp);
                    if(event.text.unicode<128){
                        if(event.text.unicode == 8){
                            popp = popp.substr(0,popp.size()-1);
                            popp += '|';
                        }
                        else{
                            popp += event.text.unicode;
                            popp += '|';
                        }
                    }
                }
                if(pstatebox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))){
                    statep = RemoveCursor(statep);
                    if(event.text.unicode<128){
                        if(event.text.unicode == 8){
                            statep = statep.substr(0, statep.size()-1);
                            statep += '|';
                        }
                        else{
                            statep += event.text.unicode;
                            statep += '|';
                        }
                    }
                }
                if(pelvbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))){
                    elvp = RemoveCursor(elvp);
                    if(event.text.unicode<128){
                        if(event.text.unicode == 8){
                            elvp = elvp.substr(0,elvp.size()-1);
                            elvp += '|';
                        }
                        else{
                            elvp += event.text.unicode;
                            elvp += '|';
                        }
                    }
                }
            }
            else if(event.type == sf::Event::MouseButtonPressed) {
                //Determine which text box is selected
                mpos = sf::Mouse::getPosition(window);
                if (event.mouseButton.button == sf::Mouse::Left)
                    if (popbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                        if(popstr.find('|') == string::npos){
                            popstr += '|';
                        }
                        statestr = RemoveCursor(statestr);
                        elvstr = RemoveCursor(elvstr);
                        popp = RemoveCursor(popp);
                        statep = RemoveCursor(statep);
                        elvp = RemoveCursor(elvp);
                    }
                if (statebox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                    if(statestr.find('|') == string::npos){
                        statestr += '|';
                    }
                    popstr = RemoveCursor(popstr);
                    elvstr = RemoveCursor(elvstr);
                    popp = RemoveCursor(popp);
                    statep = RemoveCursor(statep);
                    elvp = RemoveCursor(elvp);
                }
                if (elvbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                    if(elvstr.find('|') == string::npos){
                        elvstr += '|';
                    }
                    popstr = RemoveCursor(popstr);
                    statestr = RemoveCursor(statestr);
                    popp = RemoveCursor(popp);
                    statep = RemoveCursor(statep);
                    elvp = RemoveCursor(elvp);
                }
                if(ppopbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))){
                    if(popp.find('|') == string::npos){
                        popp += '|';
                    }
                    popstr = RemoveCursor(popstr);
                    statestr = RemoveCursor(statestr);
                    elvstr = RemoveCursor(elvstr);
                    statep = RemoveCursor(statep);
                    elvp = RemoveCursor(elvp);
                }
                if(pstatebox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))){
                    if(statep.find('|') == string::npos){
                        statep += '|';
                    }
                    popstr = RemoveCursor(popstr);
                    statestr = RemoveCursor(statestr);
                    elvstr = RemoveCursor(elvstr);
                    popp = RemoveCursor(popp);
                    elvp = RemoveCursor(elvp);
                }
                if(pelvbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))){
                    if(elvp.find('|') == string::npos){
                        elvp += '|';
                    }
                    popstr = RemoveCursor(popstr);
                    statestr = RemoveCursor(statestr);
                    elvstr = RemoveCursor(elvstr);
                    popp = RemoveCursor(popp);
                    statep = RemoveCursor(statep);
                }
                //Display results box if search is selected
                if(searchbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))){
                    if(popstr.find('|') != string::npos){
                        popstr.erase(popstr.find('|'));
                    }
                    if(statestr.find('|') != string::npos){
                        statestr.erase(statestr.find('|'));
                    }
                    if(elvstr.find('|') != string::npos){
                        elvstr.erase(elvstr.find('|'));
                    }
                    if(popp.find('|') != string::npos){
                        popp.erase(popp.find('|'));
                    }
                    if(statep.find('|') != string::npos){
                        statep.erase(statep.find('|'));
                    }
                    if(elvp.find('|') != string::npos){
                        elvp.erase(elvp.find('|'));
                    }
                    resultbox.setTextureRect(sf::IntRect(0,0,600,400));
                    resultbox.setTexture(texture);
                    resultbox.setPosition(200,550);
                }
            }
        }
        //Text setup
        title.setString("City Preference Generator");
        title.setFont(font);
        title.setFillColor(sf::Color::White);
        title.setCharacterSize(50);
        title.setPosition(100,0);

        pop.setString("Enter Preferred Population: ");
        pop.setFont(font);
        pop.setFillColor(sf::Color::White);
        pop.setCharacterSize(24);
        pop.setPosition(0,200);

        state.setString("Enter Preferred State: ");
        state.setFont(font);
        state.setFillColor(sf::Color::White);
        state.setCharacterSize(24);
        state.setPosition(0,300);

        elv.setString("Enter Preferred Elevation: ");
        elv.setFont(font);
        elv.setFillColor(sf::Color::White);
        elv.setCharacterSize(24);
        elv.setPosition(0,400);

        searchtext.setString("Search");
        searchtext.setFont(font);
        searchtext.setFillColor(sf::Color::Black);
        searchtext.setCharacterSize(50);
        searchtext.setPosition(410,490);

        poptxt.setString(popstr);
        poptxt.setFont(font);
        poptxt.setFillColor(sf::Color::Black);
        poptxt.setCharacterSize(24);
        poptxt.setPosition(405,200);

        statetxt.setString(statestr);
        statetxt.setFont(font);
        statetxt.setFillColor(sf::Color::Black);
        statetxt.setCharacterSize(24);
        statetxt.setPosition(405,300);

        elvtxt.setString(elvstr);
        elvtxt.setFont(font);
        elvtxt.setFillColor(sf::Color::Black);
        elvtxt.setCharacterSize(24);
        elvtxt.setPosition(405, 400);

        ppop.setString("Priority: ");
        ppop.setFont(font);
        ppop.setFillColor(sf::Color::White);
        ppop.setCharacterSize(24);
        ppop.setPosition(620,200);

        pstate.setString("Priority: ");
        pstate.setFont(font);
        pstate.setFillColor(sf::Color::White);
        pstate.setCharacterSize(24);
        pstate.setPosition(620,300);

        pelv.setString("Priority: ");
        pelv.setFont(font);
        pelv.setFillColor(sf::Color::White);
        pelv.setCharacterSize(24);
        pelv.setPosition(620, 400);

        poppr.setString(popp);
        poppr.setFont(font);
        poppr.setFillColor(sf::Color::Black);
        poppr.setCharacterSize(24);
        poppr.setPosition(760,200);

        statepr.setString(statep);
        statepr.setFont(font);
        statepr.setFillColor(sf::Color::Black);
        statepr.setCharacterSize(24);
        statepr.setPosition(760,300);

        elvpr.setString(elvp);
        elvpr.setFont(font);
        elvpr.setFillColor(sf::Color::Black);
        elvpr.setCharacterSize(24);
        elvpr.setPosition(760,400);

        //Draw Everything
        window.clear();
        window.draw(title);
        window.draw(pop);
        window.draw(popbox);
        window.draw(poptxt);
        window.draw(state);
        window.draw(statebox);
        window.draw(statetxt);
        window.draw(elv);
        window.draw(elvbox);
        window.draw(elvtxt);
        window.draw(searchbox);
        window.draw(searchtext);
        window.draw(resultbox);
        window.draw(ppop);
        window.draw(pstate);
        window.draw(pelv);
        window.draw(ppopbox);
        window.draw(pstatebox);
        window.draw(pelvbox);
        window.draw(poppr);
        window.draw(statepr);
        window.draw(elvpr);
        window.display();
    }
    return 0;
}
