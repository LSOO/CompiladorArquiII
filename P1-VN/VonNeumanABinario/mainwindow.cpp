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
    ofstream fs("temp");
    fs << line;
    fs.close();
    ifstream fw("temp");
    while(! fw.eof() ){
           fw >> pal;
           words.push_back(pal);
    }
    return words;

}

void MainWindow::on_pushButton_clicked()
{
    ui->plainTextEdit->ensureCursorVisible();

    vector<string> vwords;
    vector< vector<string> > vtext;

    //Get text from user
    string line;
    ofstream fs("code.txt");
    fs << ui->textEdit->toPlainText().toStdString() << endl;
    fs.close();

    //Extract text from code.txt
    fstream tex;
    tex.open("code.txt");
    while (! tex.eof() ){
      cout << "PASS" << endl;
      getline (tex,line);
      vwords = extractwords(line);
      vtext.push_back(vwords);
    }

    tex.close();

}
