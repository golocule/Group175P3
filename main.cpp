#include <iostream>
#include "readData.h"

int main() {
    readData readData;
    vector<movie> movies = readData.getMovies();
    return 0;
}
