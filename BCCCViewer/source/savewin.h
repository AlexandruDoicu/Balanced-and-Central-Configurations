#ifndef SAVEWIN_H
#define SAVEWIN_H

#include <QDialog>
#include <QString>

namespace Ui {
class SaveWin;
}

class SaveWin : public QDialog
{
    Q_OBJECT

public:
    QString FileNameToSave;
    bool JPGorPNG;
    bool ButtonClose;

    explicit SaveWin(QWidget *parent = nullptr);
    ~SaveWin();

private slots:
    void on_checkBox_2_stateChanged(int arg1);

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::SaveWin *ui;
};

#endif // SAVEWIN_H
