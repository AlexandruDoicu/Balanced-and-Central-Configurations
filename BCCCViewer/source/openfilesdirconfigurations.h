#ifndef OPENFILESDIRCONFIGURATIONS_H
#define OPENFILESDIRCONFIGURATIONS_H

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <QString>
#include "dirent.h"

using namespace std;

/*
 *
 *      GLOBAL FUNCTION
 *
 */

// --- REVERSE STRING ---
bool ReverseString(string &str);

/*
 *
 *      CLASS: OpenFilesDirConfigurations
 *
 */

class OpenFilesDirConfigurations {
public:
    // --- CONSTRUCTOR ---
    OpenFilesDirConfigurations();

    // --- DESTRUCTOR ---
    virtual ~OpenFilesDirConfigurations();

    // --- OPEN DIRECTORY Configurations ---
    vector<string> OpenDirConfigurations() const;

    // --- NUMBER OF CC FILES ---
    int NumberCCFiles() const;

    // --- NUMBER OF BC FILES ---
    int NumberBCFiles() const;

    // --- GET ALL FILES ---
    vector<string> GetFiles() const;

    // --- GET ALL CC FILES ---
    vector<string> GetCCFiles() const;

    // --- GET ALL BC FILES ---
    vector<string> GetBCFiles() const;

    // --- GET MASSES OF CC FILES ---
    vector<string> GetMassCCFiles() const;

    // --- GET MASSES OF BC FILES ---
    vector<string> GetMassBCFiles() const;

    // --- GET sigma_y's OF BC FILES ---
    vector<string> GetMassSigmaFiles() const;

    // --- GET BC MASSES AND sigma_y's THAT ARE POSSIBLE ---
    vector<vector<string>> GetBCMassSigmaPoss() const;

    // --- TEXT OUTPUT POSSIBLE MASSES AND sigma_y's IN CC AND BC ---
    QString AllText() const;
};

#endif // OPENFILESDIRCONFIGURATIONS_H
