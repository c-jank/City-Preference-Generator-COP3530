#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <string>
#include <SFML/graphics.hpp>
#include "Bridges.h"
#include "DataSource.h"
#include "data_src/City.h"
#include "maxHeap.h"
#include <cmath>

#include "SplayTree.h"

using namespace std;
using namespace bridges;


// User Preferences structure

string RemoveCursor(string str){
    if(str.find('|') != string::npos){
        str.erase(str.find('|'));
    }
    return str;
}


double calcScore(const cityData& city, const string& state, int minPop, int maxPop, int minAlt, int maxAlt, int popR, int altR, int stateR) {

    double score = 0;

    double popWeight = static_cast<double>(city.population - minPop) / (maxPop - minPop);
    score += popWeight * popR;

    double altWeight = static_cast<double>(city.altitude - minAlt) / (maxAlt - minAlt);
    score += altWeight * altR;

    if (city.state == state) {
        score += stateR;
    }

    return score;
}



int main(int argc, char **argv) {

    // create bridges object
    Bridges bridges (3, "c-jankk", "199217990495");
    bridges.setTitle("City Preference Generator");
    DataSource ds (&bridges);

    //Declaring window, text entities, font
    sf::RenderWindow window(sf::VideoMode(1000, 1000), "City Preference Generator");
    sf::Text title;
    sf::Text popmin;
    sf::Text popmax;
    sf::Text popmintxt;
    sf::Text popmaxtxt;
    sf::Text state;
    sf::Text statetxt;
    sf::Text elvmin;
    sf::Text elvmax;
    sf::Text elvmintxt;
    sf::Text elvmaxtxt;
    sf::Text Heaptext;
    sf::Text treetext;
    sf::Text ppop;
    sf::Text pstate;
    sf::Text pelv;
    sf::Text popr;
    sf::Text statepr;
    sf::Text elvpr;
    sf::Text results;
    sf::Text rescount;
    sf::Text rescnttxt;
    sf::Text resettxt;
    sf::Font font;
    font.loadFromFile("font.ttf");

    //String Containers to catch input
    string popminstr = "";
    string popmaxstr = "";
    string statestr = "";
    string elvminstr = "";
    string elvmaxstr = "";
    string popp = "";
    string statep = "";
    string elvp = "";
    string reslist = "";
    string rescntstr = "";
    int rescnt = 20;
    //Texture for text boxes
    sf::Texture texture;
    texture.loadFromFile("download.png");

    //Text Box Setup

    sf::Sprite numres;
    numres.setTextureRect(sf::IntRect (0,0,50,50));
    numres.setTexture(texture);
    numres.setPosition(380, 90);

    sf::Sprite popminbox;
    popminbox.setTextureRect(sf::IntRect(0, 0, 100, 50));
    popminbox.setTexture(texture);
    popminbox.setPosition(210, 190);

    sf::Sprite popmaxbox;
    popmaxbox.setTextureRect(sf::IntRect(0, 0, 100, 50));
    popmaxbox.setTexture(texture);
    popmaxbox.setPosition(560, 190);

    sf::Sprite statebox;
    statebox.setTextureRect(sf::IntRect(0, 0, 200, 50));
    statebox.setTexture(texture);
    statebox.setPosition(320, 290);

    sf::Sprite elvminbox;
    elvminbox.setTextureRect(sf::IntRect(0, 0, 100, 50));
    elvminbox.setTexture(texture);
    elvminbox.setPosition(210, 390);

    sf::Sprite elvmaxbox;
    elvmaxbox.setTextureRect(sf::IntRect(0, 0, 100, 50));
    elvmaxbox.setTexture(texture);
    elvmaxbox.setPosition(560, 390);

    sf::Sprite Heapbox;
    Heapbox.setTextureRect(sf::IntRect(0, 0, 150, 50));
    Heapbox.setTexture(texture);
    Heapbox.setPosition(250, 500);

    sf::Sprite treebox;
    treebox.setTextureRect(sf::IntRect(0, 0, 150, 50));
    treebox.setTexture(texture);
    treebox.setPosition(550, 500);

    sf::Sprite ppopbox;
    ppopbox.setTextureRect(sf::IntRect(0, 0, 50, 50));
    ppopbox.setTexture(texture);
    ppopbox.setPosition(800, 190);

    sf::Sprite pstatebox;
    pstatebox.setTextureRect(sf::IntRect(0, 0, 50, 50));
    pstatebox.setTexture(texture);
    pstatebox.setPosition(750, 290);

    sf::Sprite pelvbox;
    pelvbox.setTextureRect(sf::IntRect(0, 0, 50, 50));
    pelvbox.setTexture(texture);
    pelvbox.setPosition(800, 390);

    sf::Sprite reset;
    reset.setTextureRect(sf::IntRect(0, 0, 100, 50));
    reset.setTexture(texture);
    reset.setPosition(800, 750);


    sf::Sprite resultbox;



    sf::Vector2i mpos;


    while (window.isOpen()) {
        sf::Event event;
        window.setKeyRepeatEnabled(false);
        //Event Handling
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::TextEntered) {
                //Determine which text box is selected, collect input
                if (popminbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                    popminstr = RemoveCursor(popminstr);
                    if (event.text.unicode < 128) {
                        if (event.text.unicode == 8) {
                            popminstr = popminstr.substr(0, popminstr.size() - 1);
                            popminstr += '|';
                        } else {
                            popminstr += event.text.unicode;
                            popminstr += '|';
                        }
                    }
                }
                if (popmaxbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                    popmaxstr = RemoveCursor(popmaxstr);
                    if (event.text.unicode < 128) {
                        if (event.text.unicode == 8) {
                            popmaxstr = popmaxstr.substr(0, popmaxstr.size() - 1);
                            popmaxstr += '|';
                        } else {
                            popmaxstr += event.text.unicode;
                            popmaxstr += '|';
                        }
                    }
                }
                if (statebox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                    statestr = RemoveCursor(statestr);
                    if (event.text.unicode < 128) {
                        if (event.text.unicode == 8) {
                            statestr = statestr.substr(0, statestr.size() - 1);
                            statestr += '|';
                        } else {
                            statestr += event.text.unicode;
                            statestr += '|';
                        }
                    }
                }
                if (elvminbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                    elvminstr = RemoveCursor(elvminstr);
                    if (event.text.unicode < 128) {
                        if (event.text.unicode == 8) {
                            elvminstr = elvminstr.substr(0, elvminstr.size() - 1);
                            elvminstr += '|';
                        } else {
                            elvminstr += event.text.unicode;
                            elvminstr += '|';
                        }
                    }
                }
                if (elvmaxbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                    elvmaxstr = RemoveCursor(elvmaxstr);
                    if (event.text.unicode < 128) {
                        if (event.text.unicode == 8) {
                            elvmaxstr = elvmaxstr.substr(0, elvmaxstr.size() - 1);
                            elvmaxstr += '|';
                        } else {
                            elvmaxstr += event.text.unicode;
                            elvmaxstr += '|';
                        }
                    }
                }
                if (ppopbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                    popp = RemoveCursor(popp);
                    if (event.text.unicode < 128) {
                        if (event.text.unicode == 8) {
                            popp = popp.substr(0, popp.size() - 1);
                            popp += '|';
                        } else {
                            popp += event.text.unicode;
                            popp += '|';
                        }
                    }
                }
                if (pstatebox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                    statep = RemoveCursor(statep);
                    if (event.text.unicode < 128) {
                        if (event.text.unicode == 8) {
                            statep = statep.substr(0, statep.size() - 1);
                            statep += '|';
                        } else {
                            statep += event.text.unicode;
                            statep += '|';
                        }
                    }
                }
                if (pelvbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                    elvp = RemoveCursor(elvp);
                    if (event.text.unicode < 128) {
                        if (event.text.unicode == 8) {
                            elvp = elvp.substr(0, elvp.size() - 1);
                            elvp += '|';
                        } else {
                            elvp += event.text.unicode;
                            elvp += '|';
                        }
                    }
                }
                if(numres.getGlobalBounds().contains(window.mapPixelToCoords(mpos))){
                    rescntstr = RemoveCursor(rescntstr);
                    if(event.text.unicode<128){
                        if(event.text.unicode == 8){
                            rescntstr = rescntstr.substr(0,rescntstr.size()-1);
                            rescntstr += '|';
                        }
                        else{
                            rescntstr += event.text.unicode;
                            rescntstr += '|';
                        }
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                //Determine which text box is selected
                mpos = sf::Mouse::getPosition(window);
                if (event.mouseButton.button == sf::Mouse::Left)
                    if (popminbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                        if (popminstr.find('|') == string::npos) {
                            popminstr += '|';
                        }
                        popmaxstr = RemoveCursor(popmaxstr);
                        statestr = RemoveCursor(statestr);
                        elvminstr = RemoveCursor(elvminstr);
                        elvmaxstr = RemoveCursor(elvmaxstr);
                        popp = RemoveCursor(popp);
                        statep = RemoveCursor(statep);
                        elvp = RemoveCursor(elvp);
                        rescntstr = RemoveCursor(rescntstr);
                    }
                    if (popmaxbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                        if (popmaxstr.find('|') == string::npos) {
                            popmaxstr += '|';
                        }
                        popminstr = RemoveCursor(popminstr);
                        statestr = RemoveCursor(statestr);
                        elvminstr = RemoveCursor(elvminstr);
                        elvmaxstr = RemoveCursor(elvmaxstr);
                        popp = RemoveCursor(popp);
                        statep = RemoveCursor(statep);
                        elvp = RemoveCursor(elvp);
                        rescntstr = RemoveCursor(rescntstr);
                    }
                    if (statebox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                        if (statestr.find('|') == string::npos) {
                            statestr += '|';
                        }
                        popminstr = RemoveCursor(popminstr);
                        popmaxstr = RemoveCursor(popmaxstr);
                        elvminstr = RemoveCursor(elvminstr);
                        elvmaxstr = RemoveCursor(elvmaxstr);
                        popp = RemoveCursor(popp);
                        statep = RemoveCursor(statep);
                        elvp = RemoveCursor(elvp);
                        rescntstr = RemoveCursor(rescntstr);
                    }
                    if (elvminbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                        if (elvminstr.find('|') == string::npos) {
                            elvminstr += '|';
                        }
                        popminstr = RemoveCursor(popminstr);
                        popmaxstr = RemoveCursor(popmaxstr);
                        statestr = RemoveCursor(statestr);
                        elvmaxstr = RemoveCursor(elvmaxstr);
                        popp = RemoveCursor(popp);
                        statep = RemoveCursor(statep);
                        elvp = RemoveCursor(elvp);
                        rescntstr = RemoveCursor(rescntstr);
                    }
                    if (elvmaxbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                        if (elvmaxstr.find('|') == string::npos) {
                            elvmaxstr += '|';
                        }
                        popminstr = RemoveCursor(popminstr);
                        popmaxstr = RemoveCursor(popmaxstr);
                        statestr = RemoveCursor(statestr);
                        elvminstr = RemoveCursor(elvminstr);
                        popp = RemoveCursor(popp);
                        statep = RemoveCursor(statep);
                        elvp = RemoveCursor(elvp);
                        rescntstr = RemoveCursor(rescntstr);
                    }
                    if (ppopbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                        if (popp.find('|') == string::npos) {
                            popp += '|';
                        }
                        popminstr = RemoveCursor(popminstr);
                        popmaxstr = RemoveCursor(popmaxstr);
                        statestr = RemoveCursor(statestr);
                        elvminstr = RemoveCursor(elvminstr);
                        elvmaxstr = RemoveCursor(elvmaxstr);
                        statep = RemoveCursor(statep);
                        elvp = RemoveCursor(elvp);
                        rescntstr = RemoveCursor(rescntstr);
                    }
                    if (pstatebox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                        if (statep.find('|') == string::npos) {
                            statep += '|';
                        }
                        popminstr = RemoveCursor(popminstr);
                        popmaxstr = RemoveCursor(popmaxstr);
                        statestr = RemoveCursor(statestr);
                        elvminstr = RemoveCursor(elvminstr);
                        elvmaxstr = RemoveCursor(elvmaxstr);
                        popp = RemoveCursor(popp);
                        elvp = RemoveCursor(elvp);
                        rescntstr = RemoveCursor(rescntstr);
                    }
                    if (pelvbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                        if (elvp.find('|') == string::npos) {
                            elvp += '|';
                        }
                        popminstr = RemoveCursor(popminstr);
                        popmaxstr = RemoveCursor(popmaxstr);
                        statestr = RemoveCursor(statestr);
                        elvminstr = RemoveCursor(elvminstr);
                        elvmaxstr = RemoveCursor(elvmaxstr);
                        popp = RemoveCursor(popp);
                        statep = RemoveCursor(statep);
                        rescntstr = RemoveCursor(rescntstr);
                    }
                    if(numres.getGlobalBounds().contains(window.mapPixelToCoords(mpos))){
                        if(rescntstr.find('|') == string::npos){
                            rescntstr += '|';
                        }
                        popminstr = RemoveCursor(popminstr);
                        popmaxstr = RemoveCursor(popmaxstr);
                        statestr = RemoveCursor(statestr);
                        elvminstr = RemoveCursor(elvminstr);
                        elvmaxstr = RemoveCursor(elvmaxstr);
                        popp = RemoveCursor(popp);
                        statep = RemoveCursor(statep);
                        elvp = RemoveCursor(elvp);
                    }
                    //Display results box if search is selected
                    if (Heapbox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                        popminstr = RemoveCursor(popminstr);
                        popmaxstr = RemoveCursor(popmaxstr);
                        statestr = RemoveCursor(statestr);
                        elvminstr = RemoveCursor(elvminstr);
                        elvmaxstr = RemoveCursor(elvmaxstr);
                        popp = RemoveCursor(popp);
                        statep = RemoveCursor(statep);
                        elvp = RemoveCursor(elvp);
                        rescntstr = RemoveCursor(rescntstr);
                        resultbox.setTextureRect(sf::IntRect(0, 0, 600, 400));
                        resultbox.setTexture(texture);
                        resultbox.setPosition(200, 550);
                        //PLACE HEAP HERE: Inputs(strings): popminstr, popmaxstr, elvminstr, elvmaxstr, statestr, Priorities: popp, statep, elvp
                        //Use this loop to write results
                        unordered_map<string, string> city_params {
			            {"min_pop", popminstr},
                        {"max_pop", popmaxstr},
                        {"min_elev", elvminstr},
                        {"max_elev", elvmaxstr},
                        {"limit", "1000"}
                        };

                        vector<City> cities = ds.getUSCities(city_params);
                        vector<cityData> cityObjects;
                        for (auto c : cities) {
                            cityObjects.push_back(cityData(c.getCity(), c.getState(), c.getPopulation(), c.getElevation()));
                        }

                        maxHeap heap;
                        for (cityData &c: cityObjects) {
                            c.score = calcScore(c, statestr, stoi(popminstr), stoi(popmaxstr),
                                                stoi(elvminstr), stoi(elvmaxstr), stoi(popp), stoi(elvp),
                                                stoi(statep));
                            heap.insert(c);
                        }

                        for(int i = 1; i<=stoi(rescntstr); i++){
                            if (!heap.empty()) {
                                cityData top = heap.pop();
                                reslist += to_string(i)+". "+top.name+" | "+top.state+" | " +"Pop: "+ to_string(top.population)+" | "+"Alt: "+to_string(top.altitude)+"\n";
                            }
                        }
                    }
                    if (treebox.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                        popminstr = RemoveCursor(popminstr);
                        popmaxstr = RemoveCursor(popmaxstr);
                        statestr = RemoveCursor(statestr);
                        elvminstr = RemoveCursor(elvminstr);
                        elvmaxstr = RemoveCursor(elvmaxstr);
                        popp = RemoveCursor(popp);
                        statep = RemoveCursor(statep);
                        elvp = RemoveCursor(elvp);
                        rescntstr = RemoveCursor(rescntstr);
                        resultbox.setTextureRect(sf::IntRect(0, 0, 600, 400));
                        resultbox.setTexture(texture);
                        resultbox.setPosition(200, 550);
                        //PLACE TREE HERE: Inputs(strings): popminstr, popmaxstr, elvminstr, elvmaxstr, statestr, Priorities: popp, statep, elvp
                        //Use this loop to write results
                        unordered_map<string, string> city_params {
			                {"min_pop", popminstr},
                            {"max_pop", popmaxstr},
                            {"min_elev", elvminstr},
                            {"max_elev", elvmaxstr},
                            {"limit", "1000"}
                        };

                        vector<City> cities = ds.getUSCities(city_params);
                        vector<cityData> cityObjects;
                        for (auto c : cities) {
                            cityObjects.push_back(cityData(c.getCity(), c.getState(), c.getPopulation(), c.getElevation()));
                        }

                        SplayTree tree;
                        for (cityData &c: cityObjects) {
                            c.score = calcScore(c, statestr, stoi(popminstr), stoi(popmaxstr),
                                                stoi(elvminstr), stoi(elvmaxstr), stoi(popp), stoi(elvp),
                                                stoi(statep));
                            tree.root = tree.Insert(tree.root, c);
                        }

                        for(int i = 1; i<=stoi(rescntstr); i++){
                            reslist += to_string(i)+".\n";
                        }
                    }
                    if(reset.getGlobalBounds().contains(window.mapPixelToCoords(mpos))) {
                        reslist.erase();
                    }
            }
            //Text setup
            title.setString("City Preference Generator");
            title.setFont(font);
            title.setFillColor(sf::Color::White);
            title.setCharacterSize(50);
            title.setPosition(100, 0);

            rescount.setString("Number of Results (Max 20): ");
            rescount.setFont(font);
            rescount.setFillColor(sf::Color::White);
            rescount.setCharacterSize(24);
            rescount.setPosition(0,100);

            popmin.setString("Population Min: ");
            popmin.setFont(font);
            popmin.setFillColor(sf::Color::White);
            popmin.setCharacterSize(24);
            popmin.setPosition(0, 200);

            popmax.setString("Population Max: ");
            popmax.setFont(font);
            popmax.setFillColor(sf::Color::White);
            popmax.setCharacterSize(24);
            popmax.setPosition(350, 200);

            state.setString("Enter Preferred State: ");
            state.setFont(font);
            state.setFillColor(sf::Color::White);
            state.setCharacterSize(24);
            state.setPosition(0, 300);

            elvmin.setString("Elevation Min: ");
            elvmin.setFont(font);
            elvmin.setFillColor(sf::Color::White);
            elvmin.setCharacterSize(24);
            elvmin.setPosition(0, 400);

            elvmax.setString("Elevation Max: ");
            elvmax.setFillColor(sf::Color::White);
            elvmax.setFont(font);
            elvmax.setCharacterSize(24);
            elvmax.setPosition(350, 400);

            Heaptext.setString("Heap");
            Heaptext.setFont(font);
            Heaptext.setFillColor(sf::Color::Black);
            Heaptext.setCharacterSize(50);
            Heaptext.setPosition(260, 490);

            treetext.setString("Tree");
            treetext.setFont(font);
            treetext.setFillColor(sf::Color::Black);
            treetext.setCharacterSize(50);
            treetext.setPosition(560, 490);

            popmintxt.setString(popminstr);
            popmintxt.setFont(font);
            popmintxt.setFillColor(sf::Color::Black);
            popmintxt.setCharacterSize(24);
            popmintxt.setPosition(220, 200);

            popmaxtxt.setString(popmaxstr);
            popmaxtxt.setFont(font);
            popmaxtxt.setFillColor(sf::Color::Black);
            popmaxtxt.setCharacterSize(24);
            popmaxtxt.setPosition(570, 200);

            statetxt.setString(statestr);
            statetxt.setFont(font);
            statetxt.setFillColor(sf::Color::Black);
            statetxt.setCharacterSize(24);
            statetxt.setPosition(330, 300);

            elvmintxt.setString(elvminstr);
            elvmintxt.setFont(font);
            elvmintxt.setFillColor(sf::Color::Black);
            elvmintxt.setCharacterSize(24);
            elvmintxt.setPosition(215, 400);

            elvmaxtxt.setString(elvmaxstr);
            elvmaxtxt.setFont(font);
            elvmaxtxt.setFillColor(sf::Color::Black);
            elvmaxtxt.setCharacterSize(24);
            elvmaxtxt.setPosition(565, 400);

            ppop.setString("Priority: ");
            ppop.setFont(font);
            ppop.setFillColor(sf::Color::White);
            ppop.setCharacterSize(24);
            ppop.setPosition(670, 200);

            pstate.setString("Priority: ");
            pstate.setFont(font);
            pstate.setFillColor(sf::Color::White);
            pstate.setCharacterSize(24);
            pstate.setPosition(620, 300);

            pelv.setString("Priority: ");
            pelv.setFont(font);
            pelv.setFillColor(sf::Color::White);
            pelv.setCharacterSize(24);
            pelv.setPosition(670, 400);

            popr.setString(popp);
            popr.setFont(font);
            popr.setFillColor(sf::Color::Black);
            popr.setCharacterSize(24);
            popr.setPosition(810, 200);

            statepr.setString(statep);
            statepr.setFont(font);
            statepr.setFillColor(sf::Color::Black);
            statepr.setCharacterSize(24);
            statepr.setPosition(760, 300);

            elvpr.setString(elvp);
            elvpr.setFont(font);
            elvpr.setFillColor(sf::Color::Black);
            elvpr.setCharacterSize(24);
            elvpr.setPosition(810, 400);

            results.setString(reslist);
            results.setFont(font);
            results.setFillColor(sf::Color::Black);
            results.setCharacterSize(20);
            results.setPosition(210,550);

            rescnttxt.setString(rescntstr);
            rescnttxt.setFont(font);
            rescnttxt.setFillColor(sf::Color::Black);
            rescnttxt.setCharacterSize(24);
            rescnttxt.setPosition(390,100);

            resettxt.setString("Reset");
            resettxt.setFont(font);
            resettxt.setFillColor(sf::Color::Black);
            resettxt.setCharacterSize(24);
            resettxt.setPosition(810, 750);
            //Draw Everything
            window.clear();
            window.draw(title);
            window.draw(popmin);
            window.draw(popmax);
            window.draw(popminbox);
            window.draw(popmaxbox);
            window.draw(popmintxt);
            window.draw(popmaxtxt);
            window.draw(state);
            window.draw(statebox);
            window.draw(statetxt);
            window.draw(elvmin);
            window.draw(elvmax);
            window.draw(elvminbox);
            window.draw(elvmaxbox);
            window.draw(elvmintxt);
            window.draw(elvmaxtxt);
            window.draw(Heapbox);
            window.draw(treebox);
            window.draw(Heaptext);
            window.draw(treetext);
            window.draw(resultbox);
            window.draw(ppop);
            window.draw(pstate);
            window.draw(pelv);
            window.draw(ppopbox);
            window.draw(pstatebox);
            window.draw(pelvbox);
            window.draw(popr);
            window.draw(statepr);
            window.draw(elvpr);
            window.draw(results);
            window.draw(rescount);
            window.draw(numres);
            window.draw(rescnttxt);
            window.draw(reset);
            window.draw(resettxt);
            window.display();
        }
    }
    return 0;
}