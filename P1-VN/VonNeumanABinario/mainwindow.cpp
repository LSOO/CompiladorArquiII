#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;
#include <iostream>
#include <fstream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    highlighter = new Highlighter(ui->textEdit->document());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ofstream fs("nombre.txt");

    fs << ui->textEdit->toPlainText().toStdString() << endl;


    fs.close();

}
