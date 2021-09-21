#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QScrollArea>
#include "configurationfile.h"
#include "openfilesdirconfigurations.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // --- DRAW THE CENTER (0,0) ---
    void DrawCenter();

    // --- DRAW THE I-TH CONFIGURATION ---
    void DrawIthConf(int ind);

private slots:
    void on_pushButton_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_checkBox_2_stateChanged(int arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
