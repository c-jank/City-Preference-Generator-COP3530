#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
using namespace std;

struct cityData {
    string name;
    string state;
    int population;
    double altitude;
    double score;

    cityData(string name, string state, int population, double altitude) : name(name), state(state), population(population), altitude(altitude), score(0.0) {}

    bool operator<(const cityData& other) const;
};


class maxHeap {
private:
    vector<cityData> heap;
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    void insert(const cityData& other);
    cityData pop();
    bool empty() const;
};