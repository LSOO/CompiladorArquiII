#include "mainwindow.h"
#include "ui_mainwindow.h"
using namespace std;
#include <iostream>
#include <fstream>
#include <vector>

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

static vector<string> extractwords(string line){

    vector<string> words;
    string pal;
    string s=" ";
    string c=",";
    for(int unsigned i=0;i<line.size();i++){
        cout << line[i] << endl;
        /*if(line[i].c and line[i]!=c){
            cout << line[i] << endl;
        }*/
    }
    cout << "PASS" << endl;

}

void MainWindow::on_pushButton_clicked()
{
    vector<string> v;

    //Get text from user
    string line;
    ofstream fs("code.txt");
    fs << ui->textEdit->toPlainText().toStdString() << endl;
    fs.close();

    //Extract text from code.txt
    fstream tex;
    tex.open("code.txt");
    while (! tex.eof() ){
      getline (tex,line);
      cout << "PASS" << endl;
      //v = extractwords(line);
    }

    tex.close();

}
