#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include "dirent.h"
#include "configurationfile.h"

using namespace std;

/*
 *
 *      GLOBAL FUNCTIONS
 *
 */

// --- DOES A STRING CONTAIN EQUAL ELEMENTS ---
bool EqualElements(vector<string> vec_str) {
    bool sol = false;
    int size_vec = vec_str.size();
    if (size_vec == 1) {
        sol = false;
    } else if (size_vec > 1) {
        for (int i = 0; i < size_vec-1; i++) {
            for (int j = i+1; j < size_vec; j++) {
                if (vec_str[i] == vec_str[j]) {
                    sol = true;
                    break;
                }
            }
            if (sol == true) {
                break;
            }
        }
    }
    return sol;
}

/*
 *
 *      CLASS: Configurations
 *
 */

// --- CONSTRUCTOR ---
ConfigurationFile::ConfigurationFile() : OpenFilesDirConfigurations() {
    CCorBC = true;
    NrMass = 3;
    sigmay = 0;
}

ConfigurationFile::ConfigurationFile(bool CCorBC_i, int NrMass_i, double sigmay_i) : OpenFilesDirConfigurations() {
    CCorBC = CCorBC_i;
    NrMass = NrMass_i;
    sigmay = sigmay_i;
}

// --- DESTRUCTOR ---
ConfigurationFile::~ConfigurationFile() {};

// --- CHANGE TO STRING ---
string ConfigurationFile::ToStringNrMass() const {
    return to_string(NrMass);
}

string ConfigurationFile::ToStringSigmaY() const {
    string sigmay_s;
    ostringstream temp;
    temp << sigmay;
    sigmay_s = temp.str();
    if (sigmay_s.length() == 3) {
        sigmay_s = sigmay_s + "0";
    }
    sigmay_s = sigmay_s.substr(2,2);
    return sigmay_s;
}

// --- FILE AVAILABLE (by the number of masses) ---
bool ConfigurationFile::IsFileAvailableMass() const {
    string NrMass_s = this->ToStringNrMass();
    string sigmay_s = this->ToStringSigmaY();
    string FileName;
    if (CCorBC == true) {
        FileName = "Configurations/CCNMAS"+NrMass_s+".txt";
        ifstream files(FileName.c_str());
        if (files) {
            return true;
        } else {
            return false;
        }
    } else {
        FileName = "Configurations/BCNMAS"+NrMass_s+"SY"+sigmay_s+".txt";
        ifstream files(FileName);
        if (files) {
            return true;
        } else {
            return false;
        }
    }
}

// --- NUMBER OF CONFIGURATIONS IN THE FILE ---
int ConfigurationFile::NrConfigurationsInFile() const {
    string NrMass_s = this->ToStringNrMass();
    string sigmay_s = this->ToStringSigmaY();
    string FileName;
    int Number = 0;
    string temp;
    if (CCorBC == true) {
        FileName = "Configurations/CCNMAS"+NrMass_s+".txt";
        ifstream files(FileName.c_str());
        while (getline(files,temp)) {
            Number = Number + 1;
        }
    } else {
        FileName = "Configurations/BCNMAS"+NrMass_s+"SY"+sigmay_s+".txt";
        ifstream files(FileName);
        while (getline(files,temp)) {
            Number = Number + 1;
        }
    }
    return Number;
}

// --- READ WHOLE CONFIGURATION MATRIX IN DOUBLE MATRIX ---
vector<vector<double>> ConfigurationFile::GetAllConfigs() const {
    string NrMass_s = this->ToStringNrMass();
    string sigmay_s = this->ToStringSigmaY();
    int NrConfs = this->NrConfigurationsInFile();
    string FileName;
    vector<string> All_conf_str_vec;
    vector<vector<double>> All_conf_double;
    All_conf_str_vec.resize(NrConfs);
    All_conf_double.resize(NrConfs);
    if (CCorBC == true) {
        FileName = "Configurations/CCNMAS"+NrMass_s+".txt";
        ifstream files(FileName.c_str());
        for (int i = 0; i < NrConfs; i++) {
            getline(files,All_conf_str_vec[i]);
            All_conf_double[i].resize(2*NrMass + 3);
        }
        for (int i = 0; i < NrConfs; i++) {
            stringstream temp_ss;
            string temp_string;
            int index = 0;
            double found;
            temp_ss << All_conf_str_vec[i];
            while (!temp_ss.eof()) {
                temp_ss >> temp_string;
                if (stringstream(temp_string) >> found) {
                    All_conf_double[i][index] = found;
                }
                index = index + 1;
            }
        }
    } else {
        FileName = "Configurations/BCNMAS"+NrMass_s+"SY"+sigmay_s+".txt";
        ifstream files(FileName.c_str());
        for (int i = 0; i < NrConfs; i++) {
            getline(files,All_conf_str_vec[i]);
            All_conf_double[i].resize(2*NrMass + 2);
        }
        for (int i = 0; i < NrConfs; i++) {
            stringstream temp_ss;
            string temp_string;
            int index = 0;
            double found;
            temp_ss << All_conf_str_vec[i];
            while (!temp_ss.eof()) {
                temp_ss >> temp_string;
                if (stringstream(temp_string) >> found) {
                    All_conf_double[i][index] = found;
                }
                index = index + 1;
            }
        }
    }
    return All_conf_double;
}

// --- GET X-COORDINATES OF Nr_Conf-TH CONFIGURATION ---
vector<double> ConfigurationFile::GetXCoord(int Nr_Conf) const {
    vector<vector<double>> All_confs = this->GetAllConfigs();
    vector<double> Nr_Conf_conf = All_confs[Nr_Conf];
    vector<double> sol;
    sol.resize(NrMass);
    if (CCorBC == true) {
        for (int i = 0; i < NrMass; i++) {
            sol[i] = Nr_Conf_conf[3+2*i];
        }
    } else {
        for (int i = 0; i < NrMass; i++) {
            sol[i] = Nr_Conf_conf[2+2*i];
        }
    }
    return sol;
}

// --- GET Y-COORDINATES OF Nr_Conf-TH CONFIGURATION ---
vector<double> ConfigurationFile::GetYCoord(int Nr_Conf) const {
    vector<vector<double>> All_confs = this->GetAllConfigs();
    vector<double> Nr_Conf_conf = All_confs[Nr_Conf];
    vector<double> sol;
    sol.resize(NrMass);
    if (CCorBC == true) {
        for (int i = 0; i < NrMass; i++) {
            sol[i] = Nr_Conf_conf[3+2*i+1];
        }
    } else {
        for (int i = 0; i < NrMass; i++) {
            sol[i] = Nr_Conf_conf[2+2*i+1];
        }
    }
    return sol;
}
