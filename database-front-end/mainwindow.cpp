#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workswindow.h"
#include "artistwindow.h"
#include "museumwindow.h"
#include <string>
#include <vector>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Appearances
    this->setStyleSheet(
        "QMainWindow { background-color: #e7e2f3; color: black; }"
        "QFrame { border: 2px solid #688cca; background-color: #a7b2e6; }"
        "QWidget#wotd { border: 1px solid #688cca; background-color: #e7e2f3; }"
        "QWidget#statistics { border: 1px solid #688cca; background-color: #e7e2f3; }"
        "QLabel { border: none; color: white; }"
        "QPushButton { background-color: #e7e2f3; color: black }"
        "QPushButton#searchButton {background-color: #a7b2e6; color: white; }"
        "QLineEdit { background-color: white; color: black }"
        "QComboBox { background-color: #a7b2e6; color: white }"
        );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_worksButton_clicked()
{
    // Go to works window
}

void MainWindow::on_museumsButton_clicked()
{
    // Go to museum window
}


void MainWindow::on_artistsButton_clicked()
{
    // Go to artistwindow
}
