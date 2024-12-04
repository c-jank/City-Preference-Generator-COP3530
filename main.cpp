#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <string>
#include "Bridges.h"
#include "DataSource.h"
#include "data_src/City.h"
#include <cmath>

#include "maxHeap.h"
#include "SplayTree.h"
using namespace std;
using namespace bridges;


// User Preferences structure
struct userPreferences {
	int minPopulation;
	int maxPopulation;
	int minAlt;
	int maxAlt;
	string preferredState;
	int resultCount;
	int popRank;
	int altRank;
	int stateRank;

	userPreferences(int minP, int maxP, int minA, int maxA, string state, int results, int popR, int altR, int stateR) : minPopulation(minP), maxPopulation(maxP), minAlt(minA), maxAlt(maxA), preferredState(state), resultCount(results), popRank(popR), altRank(altR), stateRank(stateR) {}
};


// function to calculate a city's "score" based on the user's preferences and priority rankings
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

/*
int main(int argc, char **argv) {
	// create bridges object
	Bridges bridges (3, "c-jankk", "199217990495");
	bridges.setTitle("City Preference Generator");
	DataSource ds (&bridges);

	// create preferences object with inputted user preferences (just example preferences until we incorporate the UI)
	userPreferences preferences(100000, 1000000, 100, 400, "IL", 25, 5, 4, 3);

	// set the city params to search for cities inside the min/max populations and elevations
	unordered_map<string, string> city_params {
			{"min_pop", to_string(preferences.minPopulation)},
			{"max_pop", to_string(preferences.maxPopulation)},
			{"min_elev", to_string(preferences.minAlt)},
			{"max_elev", to_string(preferences.maxAlt)},
			{"limit", "1000"}
	};

	// search for cities and add them to the cities vector
	vector<City> cities = ds.getUSCities(city_params);

	// for each city, create a city object and add it to a new vector of city objects
	vector<cityData> cityObjects;
	for (auto c : cities) {
		cityObjects.push_back(cityData(c.getCity(), c.getState(), c.getPopulation(), c.getElevation()));
	}

    // choose a method to search with by entering 1 or 2, replace with UI elements later
    int method;
    cin >> method;

    if (method == 1) { // do heap method

        // create heap
        maxHeap heap;

        // for each city object in the cityObjects vector, calculate the city's score and add the city to the heap
        for (cityData &c: cityObjects) {
            c.score = calcScore(c, preferences.preferredState, preferences.minPopulation, preferences.maxPopulation,
                                preferences.minAlt, preferences.maxAlt, preferences.popRank, preferences.altRank,
                                preferences.stateRank);
            heap.insert(c);
        }

        // print the cities in order using the pop function
        cout << "cities ranked by priority: " << endl;
        int count = preferences.resultCount;
        while (!heap.empty() && count > 0) {
            cityData top = heap.pop();
            cout << top.name << ' ' << top.state << ' ' << top.population << " " << top.score << endl;
            count--;
        }


        return 0;
    }

    if (method == 2) { // do splay tree method
        SplayTree tree;

        for (cityData &c: cityObjects) { // insert tree elements
            c.score = calcScore(c, preferences.preferredState, preferences.minPopulation, preferences.maxPopulation,
                                preferences.minAlt, preferences.maxAlt, preferences.popRank, preferences.altRank,
                                preferences.stateRank);
            tree.root = tree.Insert(tree.root, c);
        }
        tree.SetResults(preferences.resultCount);
        tree.PrintNames(tree.root);

    }
    return 0;
}
*/