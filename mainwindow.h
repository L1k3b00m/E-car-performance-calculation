#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    double HP_Cal(double power_input);
    double Force_Cal(double power_input,double rpm_Input);
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
