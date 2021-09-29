#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <algorithm>
#include "SortLables.h"

using namespace std;

// --- STRING TO INT ---
int VecStringToInt(string str) {
    int sol;
    stringstream strs;
    strs << str;
    strs >> sol;
    return sol;
}

// --- VECTOR STRING TO VECTOR INT ---
vector<int> VecStringToInt(vector<string> str) {
    vector<int> sol((int) str.size());
    for (int i = 0; i < (int) str.size(); i++) {
        sol[i] = VecStringToInt(str[i]);
    }
    return sol;
}

// --- INT TO STRING ---
string VecIntToString(int numbers) {
    string sol;
    ostringstream ostr;
    ostr << numbers;
    sol = ostr.str();
    return sol;
}

// --- VECTOR INT TO VECTOR STRING ---
vector<string> VecIntToString(vector<int> numbers) {
    vector<string> sol((int) numbers.size());
    for (int i = 0; i < (int) numbers.size(); i++) {
        sol[i] = VecIntToString(numbers[i]);
    }
    return sol;
}

// --- SORT STRING VECTOR ---
void SortStringVecInt(vector<string> &vec) {
    vector<int> temp_vec = VecStringToInt(vec);
    sort(temp_vec.begin(),temp_vec.end());
    vec = VecIntToString(temp_vec);
}

// --- STRING TO DOUBLE ---
double VecStringToDouble(string str) {
    double sol;
    double temp_sol;
    stringstream strs;
    strs << str;
    strs >> temp_sol;
    sol = ((double) temp_sol) / 100.0;
    return sol;
}

// --- OVERLOADING THE OPERATOR < FOR STRINGS ---
bool operator<=(vector<string> const &lhs, vector<string> const &rhs) {
    if (VecStringToInt(lhs[0]) < VecStringToInt(rhs[0])) {
        return true;
    } else if (VecStringToInt(lhs[0]) == VecStringToInt(rhs[0])) {
        if (VecStringToDouble(lhs[1]) <= VecStringToDouble(rhs[1])) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

// --- SORT VECTOR OF STRINGS ---
void SortVecString(vector<vector<string>> &vec) {
    if ((int) vec.size() != 1) {
        for (int i = 0; i < ((int) vec.size()) - 1; i++) {
            for (int j = i+1; j < (int) vec.size(); j++) {
                if (vec[j] <= vec[i]) {
                    vector<string> temp;
                    temp = vec[i];
                    vec[i] = vec[j];
                    vec[j] = temp;
                }
            }
        }
    }
}
