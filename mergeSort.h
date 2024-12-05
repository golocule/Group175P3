//
// Created by Gage Carlson on 12/3/24.
//

class mergeSort {
    vector<movie> movieVect;
    int sortElement;
public:
    mergeSort(vector<movie>& movieVect, int sortElement) {
        this->movieVect = movieVect;
        this->sortElement = sortElement;
        sortVect(movieVect, 0, movieVect.size() - 1);
    }

    // helper function for merging vectors based off indices
    // based off of merge sort code from Aman lecture slides
    void mergeVects(vector<movie>& vect, int left, int middle, int right) {
        int leftSize = middle - left + 1;
        int rightSize = right - middle;

        vector<movie> leftVect(leftSize);
        for (int i = 0; i < leftSize; i++) {
            leftVect[i] = vect[left + i];
        }

        vector<movie> rightVect(rightSize);
        for (int i = 0; i < rightSize; i++) {
            rightVect[i] = vect[middle + 1 + i];
        }

        int Li = 0;
        int Ri = 0;
        int Mi = left;

        while (Li < leftSize and Ri < rightSize) {
            if (sortElement == 1) {
                if (leftVect[Li].popularity >= rightVect[Ri].popularity) {
                    vect[Mi] = leftVect[Li];
                    Li++;
                } else {
                    vect[Mi] = rightVect[Ri];
                    Ri++;
                }
                Mi++;
            } else if (sortElement == 2) {
                if (leftVect[Li].rating >= rightVect[Ri].rating) {
                    vect[Mi] = leftVect[Li];
                    Li++;
                } else {
                    vect[Mi] = rightVect[Ri];
                    Ri++;
                }
                Mi++;
            }
        }

        while (Li < leftSize) {
            vect[Mi] = leftVect[Li];
            Li++;
            Mi++;
        }

        while (Ri < rightSize) {
            vect[Mi] = rightVect[Ri];
            Ri++;
            Mi++;
        }
    }

    void sortVect(vector<movie>& vect, int left, int right) {
        if (left < right) {
            int middle = left + (right - left)/2;

            sortVect(vect, left, middle);
            sortVect(vect, middle + 1, right);
            mergeVects(vect, left, middle, right);
        }
    }

};

#ifndef MOVIESMARTSEARCH_MAIN_MERGESORT_H
#define MOVIESMARTSEARCH_MAIN_MERGESORT_H

#endif //MOVIESMARTSEARCH_MAIN_MERGESORT_H
