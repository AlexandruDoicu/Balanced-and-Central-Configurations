#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <QString>
#include <QDebug>
#include "SortLables.h"
#include "dirent.h"
#include "openfilesdirconfigurations.h"

/*
 *
 *      GLOBAL FUNCTION
 *
 */

// --- REVERSE STRING ---
bool ReverseString(string &str) {
    int str_length = str.length();
    if (str_length == 0) {
        return false;
    } else if (str_length == 1) {
        return true;
    } else {
        string temp = "";
        for (int i = 0; i < str_length; i++) {
            temp = temp + str[str_length-1-i];
        }
        str = temp;
        return true;
    }
}

/*
 *
 *      CLASS: OpenFilesDirConfigurations
 *
 */


// --- CONSTRUCTOR ---
OpenFilesDirConfigurations::OpenFilesDirConfigurations() {};

// --- DESTRUCTOR ---
OpenFilesDirConfigurations::~OpenFilesDirConfigurations() {};

// --- OPEN DIRECTORY Configurations ---
vector<string> OpenFilesDirConfigurations::OpenDirConfigurations() const {
    vector<string> sol;
    DIR *dir; struct dirent *diread;
    vector<char *> files;
    if ((dir = opendir("Configurations")) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            files.push_back(diread->d_name);
        }
        closedir(dir);
    } else {
        perror("opendir");
    }
    int nr_files_dir = files.size();
    for (int i = 0; i < nr_files_dir; i++) {
        sol.push_back(files[i]);
    }
    return sol;
}

// --- NUMBER OF CC FILES ---
int OpenFilesDirConfigurations::NumberCCFiles() const {
    vector<string> AllFiles = this->OpenDirConfigurations();
    int sol = 0;
    for (int i = 0; i < (int) AllFiles.size(); i++) {
        if (AllFiles[i][0] == 'C') {
            sol = sol + 1;
        }
    }
    return sol;
}

// --- NUMBER OF BC FILES ---
int OpenFilesDirConfigurations::NumberBCFiles() const {
    vector<string> AllFiles = this->OpenDirConfigurations();
    int sol = 0;
    for (int i = 0; i < (int) AllFiles.size(); i++) {
        if (AllFiles[i][0] == 'B') {
            sol = sol + 1;
        }
    }
    return sol;
}

// --- GET ALL FILES ---
vector<string> OpenFilesDirConfigurations::GetFiles() const {
    return this->OpenDirConfigurations();
}

// --- GET ALL CC FILES ---
vector<string> OpenFilesDirConfigurations::GetCCFiles() const {
    vector<string> AllFiles = this->OpenDirConfigurations();
    int size_all_files = AllFiles.size();
    vector<string> sol;
    for (int i = 0; i < size_all_files; i++) {
        if (AllFiles[i][0] == 'C') {
            sol.push_back(AllFiles[i]);
        }
    }
    return sol;
}

// --- GET ALL BC FILES ---
vector<string> OpenFilesDirConfigurations::GetBCFiles() const {
    vector<string> AllFiles = this->OpenDirConfigurations();
    int size_all_files = AllFiles.size();
    vector<string> sol;
    for (int i = 0; i < size_all_files; i++) {
        if (AllFiles[i][0] == 'B') {
            sol.push_back(AllFiles[i]);
        }
    }
    return sol;
}

// --- GET MASSES OF CC FILES ---
vector<string> OpenFilesDirConfigurations::GetMassCCFiles() const {
    vector<string> AllCCFiles = this->GetCCFiles();
    vector<string> sol;
    string temp;
    string number;
    int temp_length;
    int NrFiles = AllCCFiles.size();
    sol.resize(NrFiles);
    for (int i = 0; i < NrFiles; i++) {
        temp = AllCCFiles[i];
        temp_length = temp.length();
        number = "";
        for (int j = 0; j < temp_length; j++) {
            if (isdigit(temp[j])) {
                number = number + temp[j];
            }
        }
        sol[i] = number;
    }
    return sol;
}

// --- GET MASSES OF BC FILES ---
vector<string> OpenFilesDirConfigurations::GetMassBCFiles() const {
    vector<string> AllBCFiles = this->GetBCFiles();
    vector<string> sol;
    string temp;
    string number;
    int temp_length;
    int NrFiles = AllBCFiles.size();
    sol.resize(NrFiles);
    for (int i = 0; i < NrFiles; i++) {
        temp = AllBCFiles[i];
        temp_length = temp.length();
        number = "";
        for (int j = 0; j < temp_length; j++) {
            if (isdigit(temp[j])) {
                number = number + temp[j];
            }
            if (j+1 <= temp_length-1) {
                if ((isdigit(temp[j])) && (!isdigit(temp[j+1]))) {
                    break;
                }
            }

        }
        sol[i] = number;
    }
    return sol;
}

// --- GET sigma_y's OF BC FILES ---
vector<string> OpenFilesDirConfigurations::GetMassSigmaFiles() const {
    vector<string> AllBCFiles = this->GetBCFiles();
    vector<string> sol;
    string temp;
    string number;
    int temp_length;
    int NrFiles = AllBCFiles.size();
    bool Reverse;
    sol.resize(NrFiles);
    for (int i = 0; i < NrFiles; i++) {
        temp = AllBCFiles[i];
        temp_length = temp.length();
        number = "";
        for (int j = 0; j < temp_length; j++) {
            if (isdigit(temp[temp_length-1-j])) {
                number = number + temp[temp_length-1-j];
            }
            if (j+1 <= temp_length-1) {
                if ((isdigit(temp[temp_length-1-j])) && (!isdigit(temp[temp_length-2-j]))) {
                    break;
                }
            }
        }
        sol[i] = number;
        Reverse = ReverseString(sol[i]);
        if (Reverse == true) {
            sol[i] = "0." + sol[i];
        }
    }
    return sol;
}

// --- GET BC MASSES AND sigma_y's THAT ARE POSSIBLE ---
vector<vector<string>> OpenFilesDirConfigurations::GetBCMassSigmaPoss() const {
    vector<string> Mass = this->GetMassBCFiles();
    vector<string> Sigma = this->GetMassSigmaFiles();
    vector<vector<string>> sol;
    int MS_size = Mass.size();
    sol.resize(MS_size);
    for (int i = 0; i < MS_size; i++) {
        sol[i].resize(2);
        sol[i][0] = Mass[i];
        sol[i][1] = Sigma[i];
    }
    return sol;
}

// --- TEXT OUTPUT POSSIBLE MASSES AND sigma_y's IN CC AND BC ---
QString OpenFilesDirConfigurations::AllText() const {
    vector<string> MassCC = this->GetMassCCFiles();
    // --- sorting the mass array for CC
    SortStringVecInt(MassCC);
    vector<vector<string>> MassSigmaBC = this->GetBCMassSigmaPoss();
    // --- sorting the mass array for BC
    SortVecString(MassSigmaBC);
    QString sol = "";
    sol = "The possible CC masses are:\n";
    for (int i = 0; i < (int) MassCC.size(); i++) {
        sol = sol + QString::fromStdString(MassCC[i]) + "\n";
    }
    sol = sol + "\n";
    sol = sol + "The possible BC masses and sigma_y's are:\n";
    for (int i = 0; i < (int) MassSigmaBC.size(); i++) {
        sol = sol + QString::fromStdString(MassSigmaBC[i][0])
              + " --- " + QString::fromStdString(MassSigmaBC[i][1]) + "\n";
    }
    return sol;
}
