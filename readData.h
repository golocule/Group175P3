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
        string line;
        int lineIndex = 0;
        while (getline(movieFile, line)) {
            movie currMovie;
            vector<string> lists;
            vector<string> quotes;
            int i = 0;

            if (lineIndex > 0) {
                quotes.clear();
                lists.clear();
                string currList;
                string currQuote;
                for (char c : line) {
                    if (c == '[' or c == '"') {
                        if (c == '[') {
                            for (int k = i+1; k < line.length(); k++) {
                                if (line[k] == ']') {
                                    line.erase(i, k-i+1);
                                    break;
                                }
                                currList += line[k];
                            }
                            if (currList != "") {
                                lists.push_back(currList);
                            }
                            currList = "";
                        } else if (c == '"' and (isalpha(line[i+1]) or isdigit(line[i+1]) or line[i+1] == '(' or line[i+1] == '\'' or (line[i+1] == '"' and line[i+2] == '"') or line[i+1] == '.') and line[i-1] == ',') {
                            for (int k = i+1; k < line.length(); k++) {
                                if (line[k] == '"' and line[k+1] == ',' and line[k+2] != ' ') {
                                    line.erase(i, k-i+1);
                                    break;
                                }
                                currQuote += line[k];
                            }
                            if (currQuote != "") {
                                quotes.push_back(currQuote);
                            }
                            currQuote = "";
                        }
                    }
                    i++;
                }

                for (int j = 0; j < lists.size(); j++) {
                    int pos = 0;
                    string currStr = "";
                    while ((pos = lists[j].find("""name""", pos)) != string::npos) {
                        pos += 10;
                        while (pos < lists[j].length() and lists[j][pos] != '"') {
                            currStr += lists[j][pos];
                            pos++;
                        }
                        if (j == 0) {
                            currMovie.genres.push_back(currStr);
                        } else if (j == 1) {
                            currMovie.keywords.push_back(currStr);
                        } else if (j == 2) {
                            currMovie.productionComps.push_back(currStr);
                        }
                        currStr = "";
                        pos += 6;
                    }
                }
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
                        if (quotes.size() >= 1) {
                            currMovie.description = quotes[0];
                        }
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
