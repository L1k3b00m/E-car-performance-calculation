#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->PowerEdit->setVisible(false);
    ui->RpmEdit->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{   //获取输入框数据
    double power_input = ui->PowerEdit->text().toDouble();
    double rpm_input = ui->RpmEdit->text().toDouble();
    bool powerIsEmpt = ui->PowerEdit->text().isEmpty();
    bool rpm_isEmpt = ui->RpmEdit->text().isEmpty();
    //获取勾选框数据
    ui->Result_text->setText("");//textEdit清空数据
    //判断
    if(powerIsEmpt&&rpm_isEmpt){
        QMessageBox::critical(this,"出错了","没有输入数据！","重试");
    }
    if(!ui->Force_Check->isChecked()&&!ui->housePower_Check->isChecked()){
        QMessageBox::critical(this,"出错了","没有勾选数据处理方式","重试");
    }

    if(ui->housePower_Check->isChecked()){
        if(powerIsEmpt){
                QMessageBox::warning(this,"警告","没有监测到数据输入","请重试");
        }
        else{
            double power = HP_Cal(power_input);
            ui->Result_text->append("马力为"+QString::number(power,'f',5)+"（Hp）");//QString为转换函数
        }
    }
    //判断
    if(ui->Force_Check->isChecked()){
        if(!rpm_isEmpt && !powerIsEmpt){
           double Force = Force_Cal(power_input,rpm_input);
           ui->Result_text->append("扭矩为"+QString::number(Force,'f',5)+"（牛N/米M）");
        }else if(rpm_isEmpt){
            QMessageBox::warning(this,"警告","需要转速数据","请重试");
        }else if(powerIsEmpt){
            QMessageBox::warning(this,"警告","需要功率数据","请重试");
        }
    }

}
double MainWindow::HP_Cal(double power_input){
    return power_input/0.735;
}
double MainWindow::Force_Cal(double power_input,double rpm_Input){
    return (9550*power_input) / rpm_Input ;
}
//TODO马力倒推转速
//TODO勾选框条件出现输入栏


void MainWindow::on_housePower_Check_clicked(bool checked)
{
    bool force_isck = ui->Force_Check->isChecked();
    if(checked){
        ui->PowerEdit->setVisible(true);
    }else if(force_isck){
        ui->PowerEdit->setVisible(true);
    }else{
        ui->PowerEdit->setVisible(false);
    }

}

void MainWindow::on_Force_Check_clicked(bool checked)
{
    bool hp_isck = ui->housePower_Check->isChecked();
    if(checked){
        ui->RpmEdit->setVisible(true);
        ui->PowerEdit->setVisible(true);
    }else if(hp_isck){
        ui->RpmEdit->setVisible(false);
    }else{
        ui->RpmEdit->setVisible(false);
        ui->PowerEdit->setVisible(false);
    }
}
