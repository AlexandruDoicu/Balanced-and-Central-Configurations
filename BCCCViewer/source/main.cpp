#include "mainwindow.h"
#include "configurationfile.h"
#include "openfilesdirconfigurations.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <QApplication>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QString>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
