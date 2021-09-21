#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <stdlib.h>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QString>
#include <Qt>
#include <QVector>
#include <QDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configurationfile.h"
#include "openfilesdirconfigurations.h"
#include "savewin.h"

using namespace std;

// --- GLOBAL VARIABLE ---
int index_conf = 0;

/*
 *
 *      GLOBAL FUNCTIONS
 *
 */

string del_empty_space(string st) {
    int st_size = st.size();
    if (st_size == 0) {
        return st;
    } else {
        int index_beginning = 0;
        int index_ending = st_size;
        string sol;
        for (int i = 0; i < st_size; i++) {
            if (st[i] == ' ') {
                index_beginning = index_beginning + 1;
            } else {
                break;
            }
        }
        for (int i = 0; i < st_size; i++) {
            if (st[st_size-1-i] == ' ') {
                index_ending = index_ending - 1;
            } else {
                break;
            }
        }
        for (int i = index_beginning; i < index_ending; i++) {
            sol = sol + st[i];
        }
        return sol;
    }
}

int str_to_int(string st) {
    int sol;
    if (st == "") {
        sol = 0;
        return sol;
    } else {
        stringstream strValue;
        strValue << st;
        strValue >> sol;
        return sol;
    }
}

double str_to_doub(string st) {
    double sol;
    istringstream(st) >> sol;
    return sol;
}

/*
 *
 *      CLASS: MainWindow
 *
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit_2->setEnabled(false);
    ui->label_4->setText("Choose between balanced or central configurations.");
    ui->label_5->setText(" ");
    ui->scrollArea->setEnabled(true);
    ui->pushButton_5->setEnabled(false);

    // set the scroll area widget
    QWidget *central_scroll = new QWidget;
    QVBoxLayout *layout_scroll = new QVBoxLayout(central_scroll);
    ui->scrollArea->setWidget(central_scroll);
    ui->scrollArea->setWidgetResizable(true);

    QLabel *lab_mass_name = new QLabel;
    layout_scroll->addWidget(lab_mass_name);
    layout_scroll->setAlignment(lab_mass_name,Qt::AlignTop);
    OpenFilesDirConfigurations Folder;

    lab_mass_name->setText(Folder.AllText());

    this->DrawCenter();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// --- DRAW THE CENTER (0,0) ---
void MainWindow::DrawCenter() {
    QVector<double> x0(1), y0(1);
    x0[0] = 0;
    y0[0] = 0;
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(x0,y0);
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->widget->xAxis->setRange(-1, 1);
    ui->widget->yAxis->setRange(-1, 1);
    QCPScatterStyle myScatter;
    myScatter.setShape(QCPScatterStyle::ssCircle);
    myScatter.setPen(QPen(Qt::blue));
    myScatter.setBrush(Qt::white);
    myScatter.setSize(10);
    ui->widget->graph(0)->setScatterStyle(myScatter);
    ui->widget->replot();
}

// --- DRAW THE I-TH CONFIGURATION ---
void MainWindow::DrawIthConf(int ind) {
    vector<bool> Confs = {ui->checkBox->isChecked(),
                          ui->checkBox_2->isChecked()};
    if ((Confs[0] == true) && (Confs[1] == false)) {
        QString QNrMass = ui->lineEdit->text();
        string SNrMass = del_empty_space(QNrMass.toUtf8().constData());
        int NrMass = str_to_int(SNrMass);

        // check if NrMass is in the available CC Files
        OpenFilesDirConfigurations Folder;
        vector<string> MassCCFiles = Folder.GetMassCCFiles();
        vector<int> I_MassCCFiles;
        I_MassCCFiles.resize((int) MassCCFiles.size());
        for (int i = 0; i < (int) MassCCFiles.size(); i++) {
            I_MassCCFiles[i] = str_to_int(MassCCFiles[i]);
        }
        // check if NrMass is in Doub_MassCCFiles
        bool NrMassAvailable = false;
        for (int i = 0; i < (int) MassCCFiles.size(); i++) {
            if (NrMass == I_MassCCFiles[i]) {
                NrMassAvailable = true;
                break;
            }
        }
        if (NrMassAvailable == false) {
            ui->label_5->setText("No File");
        } else {
            ConfigurationFile File(true,NrMass,0.1);
            vector<double> xCoord = File.GetXCoord(ind);
            vector<double> yCoord = File.GetYCoord(ind);
            QVector<double> QxCoord(NrMass);
            QVector<double> QyCoord(NrMass);
            for (int i = 0; i < NrMass; i++) {
                QxCoord[i] = xCoord[i];
                QyCoord[i] = yCoord[i];
            }
            QVector<double> x0(1), y0(1);
            x0[0] = 0;
            y0[0] = 0;
            // determine x_lim, y_lim
            double x_lim = 0;
            double y_lim = 0;
            double range = 0;
            for (int i = 0; i < (int) NrMass; i++) {
                if (abs(xCoord[i]) >= x_lim) {
                    x_lim = abs(xCoord[i]);
                }
                if (abs(yCoord[i]) >= y_lim) {
                    y_lim = abs(yCoord[i]);
                }
            }
            x_lim = x_lim + 1;
            y_lim = y_lim + 1;
            if (abs(x_lim) >= abs(y_lim)) {
                range = abs(x_lim);
            } else {
                range = abs(y_lim);
            }
            ui->widget->addGraph();
            // add the coordinates of the configuration
            ui->widget->graph(0)->setData(QxCoord,QyCoord);
            ui->widget->xAxis->setRange((-1)*range, range);
            ui->widget->yAxis->setRange((-1)*range, range);
            QCPScatterStyle Scatter_coord;
            Scatter_coord.setShape(QCPScatterStyle::ssDisc);
            Scatter_coord.setPen(QPen(Qt::red));
            Scatter_coord.setBrush(Qt::red);
            Scatter_coord.setSize(10);
            ui->widget->graph(0)->setScatterStyle(Scatter_coord);
            ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
            // add the center
            ui->widget->graph(1)->setData(x0,y0);
            QCPScatterStyle Scatter_center;
            Scatter_center.setShape(QCPScatterStyle::ssCross);
            Scatter_center.setPen(QPen(Qt::blue));
            Scatter_center.setBrush(Qt::white);
            Scatter_center.setSize(10);
            ui->widget->graph(1)->setScatterStyle(Scatter_center);
            // plot everything
            ui->widget->replot();
        }
    } else if ((Confs[0] == false) && (Confs[1] == true)) {
        QString QNrMass = ui->lineEdit->text();
        string SNrMass = del_empty_space(QNrMass.toUtf8().constData());
        int NrMass = str_to_int(SNrMass);
        QString QSigma = ui->lineEdit_2->text();
        string SSigma = del_empty_space(QSigma.toUtf8().constData());
        double Sigma;
        // convert SSigma to double Sigma
        Sigma = str_to_doub(SSigma);

        // check if NrMass and Sigma is an available configuration
        OpenFilesDirConfigurations Folder;
        vector<vector<string>> MassSigmaBCFiles = Folder.GetBCMassSigmaPoss();
        vector<vector<double>> D_MassSigmaBCFiles((int) MassSigmaBCFiles.size());
        for (int i = 0; i < (int) MassSigmaBCFiles.size(); i++) {
            D_MassSigmaBCFiles[i].resize(2);
            D_MassSigmaBCFiles[i][0] = str_to_doub(MassSigmaBCFiles[i][0]);
            D_MassSigmaBCFiles[i][1] = str_to_doub(MassSigmaBCFiles[i][1]);
        }
        bool NrMassSigmaAvailable = false;
        for (int i = 0; i < (int) MassSigmaBCFiles.size(); i++) {
            if ((((int) D_MassSigmaBCFiles[i][0]) == NrMass) && (D_MassSigmaBCFiles[i][1] == Sigma)) {
                NrMassSigmaAvailable = true;
                break;
            }
        }
        if (NrMassSigmaAvailable == false) {
            ui->label_5->setText("No File!");
        } else {
            ConfigurationFile File(false,NrMass,Sigma);
            vector<double> xCoord = File.GetXCoord(ind);
            vector<double> yCoord = File.GetYCoord(ind);
            QVector<double> QxCoord(NrMass);
            QVector<double> QyCoord(NrMass);
            for (int i = 0; i < NrMass; i++) {
                QxCoord[i] = xCoord[i];
                QyCoord[i] = yCoord[i];
            }
            QVector<double> x0(1), y0(1);
            x0[0] = 0;
            y0[0] = 0;
            // determine x_lim, y_lim
            double x_lim = 0;
            double y_lim = 0;
            double range = 0;
            for (int i = 0; i < (int) NrMass; i++) {
                if (abs(xCoord[i]) >= x_lim) {
                    x_lim = abs(xCoord[i]);
                }
                if (abs(yCoord[i]) >= y_lim) {
                    y_lim = abs(yCoord[i]);
                }
            }
            x_lim = x_lim + 1;
            y_lim = y_lim + 1;
            if (abs(x_lim) >= abs(y_lim)) {
                range = abs(x_lim);
            } else {
                range = abs(y_lim);
            }
            ui->widget->addGraph();
            // add the coordinates of the configuration
            ui->widget->graph(0)->setData(QxCoord,QyCoord);
            ui->widget->xAxis->setRange((-1)*range, range);
            ui->widget->yAxis->setRange((-1)*range, range);
            QCPScatterStyle Scatter_coord;
            Scatter_coord.setShape(QCPScatterStyle::ssDisc);
            Scatter_coord.setPen(QPen(Qt::red));
            Scatter_coord.setBrush(Qt::red);
            Scatter_coord.setSize(10);
            ui->widget->graph(0)->setScatterStyle(Scatter_coord);
            ui->widget->graph(0)->setLineStyle(QCPGraph::lsNone);
            // add the center
            ui->widget->graph(1)->setData(x0,y0);
            QCPScatterStyle Scatter_center;
            Scatter_center.setShape(QCPScatterStyle::ssCross);
            Scatter_center.setPen(QPen(Qt::blue));
            Scatter_center.setBrush(Qt::white);
            Scatter_center.setSize(10);
            ui->widget->graph(1)->setScatterStyle(Scatter_center);
            // plot everything
            ui->widget->replot();
        }
    }
}

void MainWindow::on_pushButton_clicked()
{
    index_conf = 0;
    vector<bool> Confs = {ui->checkBox->isChecked(),
                          ui->checkBox_2->isChecked()};
    if ((Confs[0] == true) && (Confs[1] == false)) {
        QString QNrMass = ui->lineEdit->text();
        string SNrMass = del_empty_space(QNrMass.toUtf8().constData());
        int NrMass = str_to_int(SNrMass);
        ConfigurationFile File(true,NrMass,0.01);
        if (File.IsFileAvailableMass() == true) {
            ui->pushButton_5->setEnabled(true);
            ui->label_5->setText(QString::number(index_conf+1) + " / "
                               + QString::number(File.NrConfigurationsInFile()));
            this->DrawIthConf(index_conf);
            if ((index_conf+1) != File.NrConfigurationsInFile()) {
                ui->pushButton_2->setEnabled(true);
            }
        } else {
            ui->label_4->setText("Configuration file not available!");
        }
    } else if ((Confs[0] == false) && (Confs[1] == true)) {
        QString QNrMass = ui->lineEdit->text();
        string SNrMass = del_empty_space(QNrMass.toUtf8().constData());
        int NrMass = str_to_int(SNrMass);
        QString QSigma = ui->lineEdit_2->text();
        string SSigma = del_empty_space(QSigma.toUtf8().constData());
        double Sigma;
        // convert SSigma to double Sigma
        Sigma = str_to_doub(SSigma);
        ConfigurationFile File(false,NrMass,Sigma);
        if (File.IsFileAvailableMass() == true) {
            ui->pushButton_5->setEnabled(true);
            ui->label_5->setText(QString::number(index_conf+1) + " / "
                               + QString::number(File.NrConfigurationsInFile()));
            this->DrawIthConf(index_conf);
            if ((index_conf+1) != File.NrConfigurationsInFile()) {
                ui->pushButton_2->setEnabled(true);
            }
        } else {
            ui->label_4->setText("Configuration file not available!");
        }
    }
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{
    int arg2;
    if (arg1 == 2) {
        arg2 = 1;
    } else {
        arg2 = arg1;
    }
    vector<bool> A = {(bool) arg2, ui->checkBox_2->isChecked()};
    if ((A[0] == true) && (A[1] == false)) {
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(false);
        ui->label_4->setText("Enter the number of masses.");
    } else if ((A[0] == false) && (A[1] == true)) {
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->label_4->setText("Enter the number of masses and the value of sigma_y (between 0 and 1).");
    } else if ((A[0] == true) && (A[1] == true)) {
        ui->pushButton_5->setEnabled(false);
        this->DrawCenter();
        ui->label_5->setText(" ");
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->lineEdit->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);
        ui->label_4->setText("Choose just one type of configuration CC or BC.");
    } else {
        ui->pushButton_5->setEnabled(false);
        this->DrawCenter();
        ui->label_5->setText(" ");
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->lineEdit->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);
        ui->label_4->setText("Choose between balanced or central configurations.");
    }
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{
    int arg2;
    if (arg1 == 2) {
        arg2 = 1;
    } else {
        arg2 = arg1;
    }
    vector<bool> A = {ui->checkBox->isChecked(), (bool) arg2};
    if ((A[0] == true) && (A[1] == false)) {
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(false);
        ui->label_4->setText("Enter the number of masses.");
    } else if ((A[0] == false) && (A[1] == true)) {
        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->lineEdit->setEnabled(true);
        ui->lineEdit_2->setEnabled(true);
        ui->label_4->setText("Enter the number of masses and the value of sigma_y (between 0 and 1).");
    } else if ((A[0] == true) && (A[1] == true)) {
        ui->pushButton_5->setEnabled(false);
        this->DrawCenter();
        ui->label_5->setText(" ");
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->lineEdit->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);
        ui->label_4->setText("Choose just one type of configuration CC or BC.");
    } else {
        ui->pushButton_5->setEnabled(false);
        this->DrawCenter();
        ui->label_5->setText(" ");
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->lineEdit->setEnabled(false);
        ui->lineEdit_2->setEnabled(false);
        ui->label_4->setText("Choose between balanced or central configurations.");
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    index_conf = index_conf + 1;
    ui->pushButton_3->setEnabled(true);
    this->DrawIthConf(index_conf);
    vector<bool> Confs = {ui->checkBox->isChecked(),
                          ui->checkBox_2->isChecked()};
    if ((Confs[0] == true) && (Confs[1] == false)) {
        QString QNrMass = ui->lineEdit->text();
        string SNrMass = del_empty_space(QNrMass.toUtf8().constData());
        int NrMass = str_to_int(SNrMass);
        ConfigurationFile File(true,NrMass,0.01);
        ui->label_5->setText(QString::number(index_conf+1) + " / "
                           + QString::number(File.NrConfigurationsInFile()));
        if ((index_conf+1) == File.NrConfigurationsInFile()) {
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_3->setEnabled(true);
        }
    } else if ((Confs[0] == false) && (Confs[1] == true)) {
        QString QNrMass = ui->lineEdit->text();
        string SNrMass = del_empty_space(QNrMass.toUtf8().constData());
        int NrMass = str_to_int(SNrMass);
        QString QSigma = ui->lineEdit_2->text();
        string SSigma = del_empty_space(QSigma.toUtf8().constData());
        double Sigma;
        Sigma = str_to_doub(SSigma);
        ConfigurationFile File(false,NrMass,Sigma);
        ui->label_5->setText(QString::number(index_conf+1) + " / "
                           + QString::number(File.NrConfigurationsInFile()));
        if ((index_conf+1) == File.NrConfigurationsInFile()) {
            ui->pushButton_2->setEnabled(false);
            ui->pushButton_3->setEnabled(true);
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    index_conf = index_conf - 1;
    ui->pushButton_2->setEnabled(true);
    this->DrawIthConf(index_conf);
    vector<bool> Confs = {ui->checkBox->isChecked(),
                          ui->checkBox_2->isChecked()};
    if ((Confs[0] == true) && (Confs[1] == false)) {
        QString QNrMass = ui->lineEdit->text();
        string SNrMass = del_empty_space(QNrMass.toUtf8().constData());
        int NrMass = str_to_int(SNrMass);
        ConfigurationFile File(true,NrMass,0.01);
        ui->label_5->setText(QString::number(index_conf+1) + " / "
                           + QString::number(File.NrConfigurationsInFile()));
        if ((index_conf+1) == 1) {
            ui->pushButton_3->setEnabled(false);
            ui->pushButton_2->setEnabled(true);
        }
    } else if ((Confs[0] == false) && (Confs[1] == true)) {
        QString QNrMass = ui->lineEdit->text();
        string SNrMass = del_empty_space(QNrMass.toUtf8().constData());
        int NrMass = str_to_int(SNrMass);
        QString QSigma = ui->lineEdit_2->text();
        string SSigma = del_empty_space(QSigma.toUtf8().constData());
        double Sigma;
        Sigma = str_to_doub(SSigma);
        ConfigurationFile File(false,NrMass,Sigma);
        ui->label_5->setText(QString::number(index_conf+1) + " / "
                           + QString::number(File.NrConfigurationsInFile()));
        if ((index_conf+1) == 1) {
            ui->pushButton_3->setEnabled(false);
            ui->pushButton_2->setEnabled(true);
        }
    }
}

void MainWindow::on_pushButton_5_clicked() {
    SaveWin sav;
    sav.setModal(true);
    sav.exec();
    if (sav.ButtonClose == false) {
        if (sav.JPGorPNG == true) {
            QFile file(sav.FileNameToSave);
            if (!file.open(QIODevice::WriteOnly)) {
                qDebug() << file.errorString();
            } else {
                ui->widget->saveJpg(sav.FileNameToSave);
            }
        } else {
            QFile file(sav.FileNameToSave);
            if (!file.open(QIODevice::WriteOnly)) {
                qDebug() << file.errorString();
            } else {
                ui->widget->savePng(sav.FileNameToSave);
            }
        }
    }
}
