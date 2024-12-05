#include <iostream>
#include "readData.h"
#include "mergeSort.h"
#include "hiddenGemHeap.h"
#include <chrono>

int main() {
    readData readData;
    vector<movie> movies = readData.getMovies();

    string terms;
    vector<string> termVect;
    string currTerm;
    int sortChoice;

    // user inputs genres and keywords to find movies
    cout << "What kind of movie are you searching for? (enter keywords and/or genres separated by a single comma)" << endl;
    cin >> terms;

    for (char c : terms) {
        if (c == ',') {
            termVect.push_back(currTerm);
            currTerm.clear();
        } else {
            currTerm += c;
        }
    }
    termVect.push_back(currTerm);

    // user is asked how they would like the resulting movies to be shown
    cout << "How would you like the movies to be sorted?\n"
            "1. Popularity\n"
            "2. Rating\n"
            //"3. Genre/Keyword Relevancy\n"
            "0. Find Hidden Gems (finds movies with high ratings and low popularity)" << endl;
    cin >> sortChoice;



    // start heap time here
    auto start = chrono::high_resolution_clock ::now();
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
    auto stop = chrono::high_resolution_clock::now();
    cout << "Heap sort time to complete: " << chrono::duration<double>(stop-start).count() << endl;


    // merge sort is performed
    if (sortChoice != 0) {
        // start merge time here
        start = chrono::high_resolution_clock::now();

        mergeSort(movies, sortChoice);

        // end merge time here
        stop = chrono::high_resolution_clock::now();
        cout << "Merge sort time to complete: " << chrono::duration<double>(stop-start).count()<< '\n' << endl;
    }

    // for loop to compare sorted vectors
    /*
    for (int i = 0; i < movies.size(); i++) {
        cout << movies[i].title << " || " << heapSortMovies[i].title << endl;
    }
    */


        // NOTE: in the actual implementation, it would probably be best to allow the user
        // to go to the next highest rated, least popular movie. Should be just using the
        // pop function and a simple while loop.


        if (sortChoice == 0) {
            movies = heapSortMovies;
        }
        vector<movie> matchedMovies;
        for (int i = 0; i < movies.size(); i++) {
            bool movieFound = false;
            for (int j = 0; j < movies[i].keywords.size(); j++) {
                for (int k = 0; k < termVect.size(); k++) {
                    if (movies[i].keywords[j] == termVect[k]) {
                        matchedMovies.push_back(movies[i]);
                        movieFound = true;
                        break;
                    }
                }
                if (movieFound) {
                    break;
                }
            }

            if (!movieFound) {
                for (int j = 0; j < movies[i].genres.size(); j++) {
                    for (int k = 0; k < termVect.size(); k++) {
                        if (movies[i].genres[j] == termVect[k]) {
                            matchedMovies.push_back(movies[i]);
                            movieFound = true;
                            break;
                        }
                    }
                    if (movieFound) {
                        break;
                    }
                }
            }
        }
        if (sortChoice != 0) {
            for (int i = 0; i < matchedMovies.size(); i++) {
                cout << matchedMovies[i].title << endl;
            }
        } else {
            movie highestRated = movies[0];
            cout << "The highest-rated, but least popular movie is \"" << highestRated.title << "\". It has a rating of " << highestRated.rating << " and popularity of " << highestRated.popularity << endl;
            for (int i = 1; i < matchedMovies.size(); i++) {
                cout << matchedMovies[i].title << endl;
            }
        }

    return 0;
}
