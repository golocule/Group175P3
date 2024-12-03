#include <iostream>
#include <vector>
#include <algorithm>
#include "hiddenGemHeap.h"
#include "readData.h"

using namespace std;

int main() {
    readData readData;
    vector<movie> movies = readData.getMovies();

    MaxHeap heap;

    // add movies to heap
    for (const movie& m : movies) {
        heap.push(m);
    }


    // NOTE: in the actual implementation, it would probably be best to allow the user
    // to go to the next highest rated, least popular movie. Should be just using the
    // pop function and a simple while loop.
    movie highestRated = heap.top();
    cout << "The highest-rated, but least popular movie is \"" << highestRated.title << "\". It has a rating of " << highestRated.rating << " and popularity of " << highestRated.popularity << endl;

    return 0;
}
