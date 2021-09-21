#include <iostream>
#include <vector>
#include <QFile>
#include <QDebug>
#include "savewin.h"
#include "ui_savewin.h"

using namespace std;

SaveWin::SaveWin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SaveWin)
{
    ui->setupUi(this);
    ui->pushButton_5->setEnabled(true);
    ui->pushButton_6->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->label_3->setText("Choose one format.");
    ButtonClose = false;
}

SaveWin::~SaveWin()
{
    delete ui;
}

void SaveWin::on_checkBox_2_stateChanged(int arg1)
{
    int arg2;
    if (arg1 == 2) {
        arg2 = 1;
    } else {
        arg2 = arg1;
    }
    vector<bool> A = {(bool) arg2, ui->checkBox->isChecked()};
    if ((A[0] == true) && (A[1] == false)) {
        ui->pushButton_6->setEnabled(true);
        ui->lineEdit->setEnabled(true);
        ui->label_3->setText("Choose the name\nof the file.");
    } else if ((A[0] == false) && (A[1] == true)) {
        ui->pushButton_6->setEnabled(true);
        ui->lineEdit->setEnabled(true);
        ui->label_3->setText("Choose the name\nof the file.");
    } else if ((A[0] == true) && (A[1] == true)) {
        ui->pushButton_6->setEnabled(false);
        ui->lineEdit->setEnabled(false);
        ui->label_3->setText("Choose just one format.");
    } else {
        ui->pushButton_6->setEnabled(false);
        ui->lineEdit->setEnabled(false);
        ui->label_3->setText("Choose just one format.");
    }
}

void SaveWin::on_checkBox_stateChanged(int arg1)
{
    int arg2;
    if (arg1 == 2) {
        arg2 = 1;
    } else {
        arg2 = arg1;
    }
    vector<bool> A = {ui->checkBox_2->isChecked(), (bool) arg2};
    if ((A[0] == true) && (A[1] == false)) {
        ui->pushButton_6->setEnabled(true);
        ui->lineEdit->setEnabled(true);
        ui->label_3->setText("Choose the name\nof the file.");
    } else if ((A[0] == false) && (A[1] == true)) {
        ui->pushButton_6->setEnabled(true);
        ui->lineEdit->setEnabled(true);
        ui->label_3->setText("Choose the name\nof the file.");
    } else if ((A[0] == true) && (A[1] == true)) {
        ui->pushButton_6->setEnabled(false);
        ui->lineEdit->setEnabled(false);
        ui->label_3->setText("Choose just one format.");
    } else {
        ui->pushButton_6->setEnabled(false);
        ui->lineEdit->setEnabled(false);
        ui->label_3->setText("Choose just one format.");
    }
}

void SaveWin::on_pushButton_6_clicked()
{
    vector<bool> A = {ui->checkBox_2->isChecked(), ui->checkBox->isChecked()};
    QString QFileName = ui->lineEdit->text();
    QFileName.simplified();
    QFileName.replace(" ","");
    if ((A[0] == true) && (A[1] == false)) {
        if (QFileName.length() == 0) {
            ui->label_3->setText("Enter valid file name.");
        } else {
            QFileName = QFileName + ".jpg";
            QFileName = "SavedPlots/" + QFileName;
            FileNameToSave = QFileName;
            JPGorPNG = true;
            this->close();
        }
    } else if ((A[0] == false) && (A[1] == true)) {
        if (QFileName.length() == 0) {
            ui->label_3->setText("Enter valid file name.");
        } else {
            QFileName = QFileName + ".png";
            QFileName = "SavedPlots/" + QFileName;
            FileNameToSave = QFileName;
            JPGorPNG = false;
            this->close();
        }
    }
}

void SaveWin::on_pushButton_5_clicked() {
    ButtonClose = true;
    this->close();
}
