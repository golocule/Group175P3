//
// Created by azano on 12/2/2024.
//

#ifndef MOVIESMARTSEARCH_HIDDENGEMHEAP_H
#define MOVIESMARTSEARCH_HIDDENGEMHEAP_H

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class MaxHeap {
    int sortElement;
public:
    MaxHeap(int sortElement) {
        this->sortElement = sortElement;
    }

    // push a movie into the heap
    void push(movie m) {
        movies.push_back(m);
        heapifyUp(movies.size() - 1);
    }

    // removes and returns the least popular yet highest-rated movie
    movie pop() {
        if (movies.empty()) {
            throw out_of_range("Heap is empty");
        }
        swap(movies[0], movies[movies.size() - 1]);
        movie top = movies.back();
        movies.pop_back();
        heapifyDown(0);
        return top;
    }

    // returns the least popular yet highest-rated movie (top of heap)
    movie top() {
        if (movies.empty()) {
            throw out_of_range("Heap is empty");
        }
        return movies[0];
    }

    bool empty() {
        return movies.empty();
    }

private:
    vector<movie> movies;

    // creates a weight using both rating and popularity
    double computeScore(const movie& m) {
        const double popularityWeight = 0.1;
        return m.rating - (popularityWeight * m.popularity);
    }

    // helper function for pushing a new movie
    void heapifyUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (sortElement == 0) {
                if (computeScore(movies[parent]) >= computeScore(movies[index])) {
                    break;
                }
                // conditional statements to accommodate user input
            } else if (sortElement == 1) {
                if (movies[parent].popularity >= movies[index].popularity) {
                    break;
                }
            } else if (sortElement == 2) {
                if (movies[parent].rating >= movies[index].rating) {
                    break;
                }
            }

            swap(movies[parent], movies[index]);
            index = parent;
        }
    }

    // helper function after removing a movie
    void heapifyDown(int index) {
        int size = movies.size();
        while (2 * index + 1 < size) {
            int leftChild = 2 * index + 1;
            int rightChild = 2 * index + 2;
            int largest = index;

            if (sortElement == 0) {
                if (leftChild < size && computeScore(movies[leftChild]) > computeScore(movies[largest])) {
                    largest = leftChild;
                }
                if (rightChild < size && computeScore(movies[rightChild]) > computeScore(movies[largest])) {
                    largest = rightChild;
                }
                // conditional statements to accommodate user input
            } else if (sortElement == 1) {
                if (leftChild < size && movies[leftChild].popularity > movies[largest].popularity) {
                    largest = leftChild;
                }
                if (rightChild < size && movies[rightChild].popularity > movies[largest].popularity) {
                    largest = rightChild;
                }
            } else if (sortElement == 2) {
                if (leftChild < size && movies[leftChild].rating > movies[largest].rating) {
                    largest = leftChild;
                }
                if (rightChild < size && movies[rightChild].rating > movies[largest].rating) {
                    largest = rightChild;
                }
            }

            if (largest == index) {
                break;
            }
            swap(movies[index], movies[largest]);
            index = largest;
        }
    }
};

#endif //MOVIESMARTSEARCH_HIDDENGEMHEAP_H
