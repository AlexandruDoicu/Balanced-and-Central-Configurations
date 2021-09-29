#ifndef CONFIGURATIONFILE_H
#define CONFIGURATIONFILE_H

#include <iostream>
#include <vector>
#include <string>
#include "openfilesdirconfigurations.h"

using namespace std;

/*
 *
 *      GLOBAL FUNCTIONS
 *
 */

// --- DOES A STRING CONTAIN EQUAL ELEMENTS ---
bool EqualElements(vector<string> vec_str);

/*
 *
 *      CLASS: ConfigurationFile
 *
 */

class ConfigurationFile : public OpenFilesDirConfigurations {
private:
    bool CCorBC; // CC: true, BC: false
    int NrMass;
    double sigmay;
public:
    // --- CONSTRUCTOR ---
    ConfigurationFile();
    ConfigurationFile(bool CCorBC_i, int NrMass_i, double sigmay_i);

    // --- DESTRUCTOR ---
    ~ConfigurationFile();

    // --- CHANGE TO STRING ---
    string ToStringNrMass() const;
    string ToStringSigmaY() const;

    // --- FILE AVAILABLE (by the number of masses) ---
    bool IsFileAvailableMass() const;

    // --- NUMBER OF CONFIGURATIONS IN THE FILE ---
    int NrConfigurationsInFile() const;

    // --- READ WHOLE CONFIGURATION MATRIX IN DOUBLE MATRIX ---
    vector<vector<double>> GetAllConfigs() const;

    // --- GET X-COORDINATES OF Nr_Conf-TH CONFIGURATION ---
    vector<double> GetXCoord(int Nr_Conf) const;

    // --- GET Y-COORDINATES OF Nr_Conf-TH CONFIGURATION ---
    vector<double> GetYCoord(int Nr_Conf) const;
};

#endif // CONFIGURATIONFILE_H
