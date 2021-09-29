#ifndef SORTLABLES_H
#define SORTLABLES_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// --- STRING TO INT ---
int VecStringToInt(string str);

// --- VECTOR STRING TO VECTOR INT ---
vector<int> VecStringToInt(vector<string> str);

// --- INT TO STRING ---
string VecIntToString(int numbers);

// --- VECTOR INT TO VECTOR STRING ---
vector<string> VecIntToString(vector<int> numbers);

// --- SORT STRING VECTOR ---
void SortStringVecInt(vector<string> &vec);

// --- STRING TO DOUBLE ---
double VecStringToDouble(string str);

// --- OVERLOADING THE OPERATOR < FOR STRINGS ---
bool operator<(vector<string> const &lhs, vector<string> const &rhs);

// --- SORT VECTOR OF STRINGS ---
void SortVecString(vector<vector<string>> &vec);

#endif // SORTLABLES_H
