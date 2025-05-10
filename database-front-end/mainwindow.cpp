#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "workswindow.h"
#include "artistwindow.h"
#include "museumwindow.h"
#include "ui_homewindow.h"
#include "homewindow.h"

#include <QWidget>
#include <QDebug>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Windows
    homeWindow = new HomeWindow(this);
    artistWindow = new ArtistWindow(this);
    worksWindow = new WorksWindow(this);
    museumWindow = new MuseumWindow(this);

    ui->stackedWidget->addWidget(homeWindow);
    ui->stackedWidget->addWidget(worksWindow);
    ui->stackedWidget->addWidget(museumWindow);
    ui->stackedWidget->addWidget(artistWindow);

    ui->stackedWidget->setCurrentWidget(homeWindow);

    bool connected;
    connected = connect(ui->homeButton, &QPushButton::clicked, this, &MainWindow::on_homeButton_clicked);
    qDebug() << "Home button connected:" << connected;

    connected = connect(ui->worksButton, &QPushButton::clicked, this, &MainWindow::on_worksButton_clicked);
    qDebug() << "Works button connected:" << connected;

    connected = connect(ui->museumsButton, &QPushButton::clicked, this, &MainWindow::on_museumsButton_clicked);
    qDebug() << "Museums button connected:" << connected;

    connected = connect(ui->artistsButton, &QPushButton::clicked, this, &MainWindow::on_artistsButton_clicked);
    qDebug() << "Artists button connected:" << connected;

    qDebug() << "Buttons connected.";

    // Appearances

    this->setStyleSheet(
        "QMainWindow { background-color: #e7e2f3; color: black; }"
        "QFrame { border: 2px solid #688cca; background-color: #a7b2e6; }"
        //"QWidget#wotd { border: 1px solid #688cca; background-color: #e7e2f3; }"
        //"QWidget#statistics { border: 1px solid #688cca; background-color: #e7e2f3; }"
        "QLabel { border: none; color: white; }"
        "QPushButton { background-color: #e7e2f3; color: black }"
        );

}

MainWindow::~MainWindow()
{
    delete ui;
    delete artistWindow;
    delete worksWindow;
    delete museumWindow;
    delete homeWindow;
}

// --- SIDEBAR BUTTONS ---
void MainWindow::on_worksButton_clicked()
{
    // Go to works window
    qDebug() << "Works button clicked.";
    ui->stackedWidget->setCurrentWidget(ui->worksPage);
}

void MainWindow::on_museumsButton_clicked()
{
    // Go to museum window
    qDebug() << "Museum button clicked.";
    ui->stackedWidget->setCurrentWidget(ui->museumsPage);
}


void MainWindow::on_artistsButton_clicked()
{
    // Go to artist window
    qDebug() << "Artist button clicked.";
    ui->stackedWidget->setCurrentWidget(ui->artistsPage);
}

void MainWindow::on_homeButton_clicked()
{
    qDebug() << "Home button clicked.";
    ui->stackedWidget->setCurrentWidget(ui->homePage);
}

// --- artistPage BUTTONS ---

// Get artist info
void MainWindow::on_artistInfoButton_clicked()
{
    QString input = ui->artistPageInput->text();
    qDebug() << "Search input:" << input;
    if(input.isEmpty()) {
        qDebug() << "NO INPUT PROVIDED";
    }
}

// Get all artists' nationality
void MainWindow::on_artistsNationalitiesButton_clicked()
{

}

// Get all artists
void MainWindow::on_listAllArtistsButton_clicked()
{

}

// --- museumPage BUTTONS ---

// Get all artists in a museum
void MainWindow::on_artistsInMuseumButton_clicked()
{

}

// Get all museums
void MainWindow::on_listAllMuseumsButton_clicked()
{

}

// Get museum information
void MainWindow::on_museumInfoButton_clicked()
{

}

// --- workPage BUTTONS ---

// Get all paintings
void MainWindow::on_listAllWorksButton_clicked()
{

}

// Get painting information
void MainWindow::on_workInfoButton_clicked()
{

}

