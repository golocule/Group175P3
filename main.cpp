#include <iostream>
#include "readData.h"
#include "mergeSort.h"
#include "hiddenGemHeap.h"

int main() {
    readData readData;
    vector<movie> movies = readData.getMovies();

    string terms;
    int sortChoice;

    // user inputs genres and keywords to find movies
    cout << "What kind of movie are you searching for? (enter keywords and/or genres separated by a single comma)" << endl;
    cin >> terms;

    // user is asked how they would like the resulting movies to be shown
    cout << "How would you like the movies to be sorted?\n"
            "1. Popularity\n"
            "2. Rating\n"
            "3. Genre/Keyword Relevancy\n"
            "0. Find Hidden Gems (finds movies with high ratings and low popularity)" << endl;
    cin >> sortChoice;



    // start heap time here
    MaxHeap heap(sortChoice);

    // add movies to heap
    for (const movie& m : movies) {
        heap.push(m);
    }

    // the top of the heap is exctracted and added to a new vector, resulting in the sorted movie vector
    vector<movie> heapSortMovies;
    while (heapSortMovies.size() < movies.size()) {
        heapSortMovies.push_back(heap.top());
        heap.pop();
    }
    // end heap time here


    // start merge time here
    mergeSort(movies, sortChoice);
    // end merge time here

    // for loop to compare sorted vectors
    /*
    for (int i = 0; i < movies.size(); i++) {
        cout << movies[i].title << " || " << heapSortMovies[i].title << endl;
    }
     */

    if (sortChoice == 0) {
        // NOTE: in the actual implementation, it would probably be best to allow the user
        // to go to the next highest rated, least popular movie. Should be just using the
        // pop function and a simple while loop.
        movie highestRated = heap.top();
        cout << "The highest-rated, but least popular movie is \"" << highestRated.title << "\". It has a rating of " << highestRated.rating << " and popularity of " << highestRated.popularity << endl;
    }
    return 0;
}
