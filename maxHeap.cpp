#include "maxHeap.h"


bool cityData::operator<(const cityData& other) const {
    return score < other.score;
}


void maxHeap::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (heap[index] < heap[parent]) {
            break;
        }
        swap(heap[index], heap[parent]);
        index = parent;
    }
}


void maxHeap::heapifyDown(int index) {
    int size = heap.size();
    while (true) {
        int biggest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        if (left < size && heap[biggest] < heap[left]) {
            biggest = left;
        }
        if (right < size && heap[biggest] < heap[right]) {
            biggest = right;
        }
        if (biggest == index) {
            break;
        }
        swap(heap[index], heap[biggest]);
        index = biggest;
    }
}


void maxHeap::insert(const cityData& other) {
    heap.push_back(other);
    heapifyUp(heap.size() - 1);
}


cityData maxHeap::pop() {
    cityData max = heap[0];
    heap[0] = heap[heap.size() - 1];
    heap.pop_back();
    if (!heap.empty()) {
        heapifyDown(0);
    }
    return max;
}


bool maxHeap::empty() const {
    return heap.empty();
}