//
// Created by Gage Carlson on 11/26/24.
//

using namespace std;
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

struct movie {
    vector<string> actors;
    string director;
    string title;
    int budget;
    vector<string> genres;
    string homepage;
    int id;
    vector<string> keywords;
    string language;
    double popularity;
    vector<string> productionComps;
    string releaseDate;
    int runtime;
    string status;
    string description;
    double rating;
};

class readData {

public:
    readData() {
    }
    vector<movie> getMovies() {
        ifstream movieFile("../tmdb_5000_movies.csv");
        vector<movie> movies;
        movie currMovie;
        string line;
        int lineIndex = 0;
        while (getline(movieFile, line)) {
            int i = 0;
            //string currLine = line;
            vector<string> lists;
            vector<string> quotes;
            string currList;
            string currQuote;
            for (char c : line) {
                if (c == '[' or c == '"') {
                    if (c == '[') {
                        for (int k = i; k < line.length(); k++) {
                            if (line[k] == ']') {
                                line.erase(i, k-i+1);
                                //i -= (k-i);
                                //i--;
                                break;
                            }
                            currList += line[k];
                        }
                        lists.push_back(currList);
                        currList = "";
                    } else if (c == '"' and (isalpha(line[i+1]) or isdigit(line[i+1]) or line[i+1] == '(' or line[i+1] == '\'' or (line[i+1] == '"' and line[i+2] == '"') or line[i+1] == '.') and line[i-1] == ',') {
                        //cout << "entered loop" << endl;
                        //cout << line[i+1] << endl;
                        for (int k = i+1; k < line.length(); k++) {
                            if (line[k] == '"' and line[k+1] == ',' and line[k+2] != ' ') {
                                line.erase(i, k-i+1);
                                //i -= (k-i);
                                //i--;
                                break;
                            }
                            currQuote += line[k];
                        }
                        //cout << currQuote << endl;
                        quotes.push_back(currQuote);
                        currQuote = "";
                    }
                }
                i++;
            }

            stringstream ss(line);
            string element;
            if (lineIndex > 0) {
                i = 0;
                while (getline(ss, element, ',')) {
                    //cout << element << endl;
                    if (element == "") {
                        //continue;
                    }
                    if (i == 0) {
                        currMovie.budget = stoi(element);
                    } else if (i == 2) {
                        currMovie.homepage = element;
                    } else if (i == 3) {
                        currMovie.id = stoi(element);
                    } else if (i == 5) {
                        currMovie.language = element;
                    } else if (i == 7) {
                        //currMovie.description = element;
                    } else if (i == 8) {
                        currMovie.popularity = stod(element);
                    } else if (i == 11) {
                        currMovie.releaseDate = element;
                    } else if (i == 13) {
                        currMovie.runtime = stoi(element);
                    } else if (i == 15) {
                        currMovie.status = element;
                    } else if (i == 17) {
                        currMovie.title = element;
                    } else if (i == 18) {
                        currMovie.rating = stod(element);
                    }
                    i++;
                }
            }
            lineIndex++;
            movies.push_back(currMovie);
        }

        return movies;
    }
};

#ifndef MOVIESMARTSEARCH_MAIN_READDATA_H
#define MOVIESMARTSEARCH_MAIN_READDATA_H

#endif //MOVIESMARTSEARCH_MAIN_READDATA_H
