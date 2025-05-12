#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "workswindow.h"
//#include "artistwindow.h"
//#include "museumwindow.h"
//#include "ui_homewindow.h"
#include <backend.h>
#include <mainwindow.h>

#include <QWidget>
#include <QDebug>
#include <QVBoxLayout>
#include <QSqlDatabase>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Windows
    /*
    homeWindow = new HomeWindow(this);
    artistWindow = new ArtistWindow(this);
    worksWindow = new WorksWindow(this);
    museumWindow = new MuseumWindow(this);

    ui->stackedWidget->addWidget(homeWindow);
    ui->stackedWidget->addWidget(worksWindow);
    ui->stackedWidget->addWidget(museumWindow);
    ui->stackedWidget->addWidget(artistWindow);

    ui->stackedWidget->setCurrentWidget(homeWindow);
*/

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

    //connect(ui->listAllWorksButton, &QPushButton::clicked, this, &MainWindow::on_listAllWorksButton_clicked);
    connect(ui->listAllArtistsButton, &QPushButton::clicked, this, &MainWindow::on_listAllArtistsButton_clicked);
    // Appearances

    this->setStyleSheet(
        "QMainWindow { background-color: #e7e2f3; color: black; }"
        "QFrame { border: 2px solid #688cca; background-color: #a7b2e6; }"
        //"QWidget#wotd { border: 1px solid #688cca; background-color: #e7e2f3; }"
        //"QWidget#statistics { border: 1px solid #688cca; background-color: #e7e2f3; }"
        "QTableWidget { background-color: #e7e2f3; color: black; }"
        "QLabel { border: none; color: white; }"
        "QPushButton { background-color: #e7e2f3; color: black }"
        );

}

MainWindow::~MainWindow()
{
    delete ui;
    /*
    delete artistWindow;
    delete worksWindow;
    delete museumWindow;
    delete homeWindow;
*/
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
    Backend backend;

    QString artistName = ui->artistPageInput->text();
    if(artistName.isEmpty()) {
        qDebug() << "Artist name is empty.";
    }

    string name = artistName.toStdString();

    vector<string> artistInfo = backend.searchArtistByName(name);

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(5);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Artist Information" << "Nationality" << "Style" << "Birth" << "Death");

    if (!artistInfo.empty()) {
        int row = 0;
        ui->tableWidget->insertRow(row);  // Insert a new row
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(artistInfo[0])));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(artistInfo[1])));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(artistInfo[2])));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(artistInfo[3])));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(artistInfo[4])));
    }
}

// Get all artists' nationality
void MainWindow::on_artistsNationalitiesButton_clicked()
{

}

// Get all artists
void MainWindow::on_listAllArtistsButton_clicked()
{
    Backend backend;
    vector<string> artists = backend.artistNameList();

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Name");

    ui->tableWidget->setColumnWidth(0,250);

    for(int i = 0; i < artists.size(); i++) {
        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(artists[i])));
    }
}

// --- museumPage BUTTONS ---

// Get all artists in a museum
void MainWindow::on_artistsInMuseumButton_clicked()
{
    Backend backend;
    QString museumName = ui->museumsPageInput->text();

    if(museumName.isEmpty()) {
        qDebug() << "Museum name is empty.";
        return;
    }

    string mName = museumName.toStdString();
    vector<string> artists = backend.searchMuseumArtist(mName);

    ui->museumTableWidget->clear();
    ui->museumTableWidget->setRowCount(0);
    ui->museumTableWidget->setColumnCount(1);
    ui->museumTableWidget->setHorizontalHeaderLabels(QStringList() << "Name");

    ui->museumTableWidget->setColumnWidth(0, 250);

    if(!artists.empty()) {
        for(int i = 0; i < artists.size(); i++) {
            ui->museumTableWidget->insertRow(i);
            ui->museumTableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(artists[i])));
        }
    }
    else {
        qDebug() << "No museum found for the given name.";
    }
}

// Get all museums
void MainWindow::on_listAllMuseumsButton_clicked()
{

}

// Get museum information
void MainWindow::on_museumInfoButton_clicked()
{
    Backend backend;
    QString museumName = ui->museumsPageInput->text();

    if(museumName.isEmpty()) {
        qDebug() << "Museum name is empty.";
        return;
    }

    string mName = museumName.toStdString();

    vector<string> museumInfo = backend.searchMuseumInfoByName(mName);

    ui->museumTableWidget->clear();
    ui->museumTableWidget->setRowCount(0);
    ui->museumTableWidget->setColumnCount(3);
    ui->museumTableWidget->setHorizontalHeaderLabels(QStringList() << "Name" << "Phone" << "URL");

    if (!museumInfo.empty()) {
        int row = 0;
        ui->museumTableWidget->insertRow(row);
        ui->museumTableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(museumInfo[0])));
        ui->museumTableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(museumInfo[1])));
        ui->museumTableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(museumInfo[2])));
    }
    else {
        qDebug() << "No museum found for the given name.";
    }
}

// --- workPage BUTTONS ---

// Get painting information
void MainWindow::on_workInfoButton_clicked()
{
    Backend backend;
    QString workName = ui->worksPageInput->text();

    if(workName.isEmpty()) {
        qDebug() << "Work name is empty.";
        return;
    }

    string name = workName.toStdString();

    vector<string> workInfo = backend.searchWorkInfo(name);

    ui->workTableWidget->clear();
    ui->workTableWidget->setRowCount(0);
    ui->workTableWidget->setColumnCount(4);
    ui->workTableWidget->setHorizontalHeaderLabels(QStringList() << "Work Name" << "Style" << "URL" << "Subject");

    if (!workInfo.empty()) {
        int row = 0;
        ui->workTableWidget->insertRow(row);
        ui->workTableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(workInfo[0])));
        ui->workTableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(workInfo[1])));
        ui->workTableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(workInfo[2])));
        ui->workTableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(workInfo[3])));
    }
    else {
        qDebug() << "No work found for the given name.";
    }
}




void MainWindow::on_allArtistsWorksButton_clicked()
{
    Backend backend;
    QString artistName = ui->artistPageInput->text();
    if (artistName.isEmpty()) {
        qDebug() << "Artist name is empty.";
        return;
    }

    string name = artistName.toStdString();

    vector<string> works = backend.searchArtistWork(name);

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(works.size());
    ui->tableWidget->setColumnCount(1);
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Work Name");

    for(int i = 0; i < works.size(); i++) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(works[i])));
    }
    ui->tableWidget->setColumnWidth(0, 250);
}


void MainWindow::on_artistStylesButton_clicked()
{
    Backend backend;
    QString artistName = ui->artistPageInput->text();

    if (artistName.isEmpty()) {
        qDebug() << "Artist name is empty.";
        return;
    }

    string name = artistName.toStdString();
    vector<string> styles = backend.searchArtistStyle(name);

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(styles.size()); // Set the number of rows based on the works
    ui->tableWidget->setColumnCount(1); // Only one column for work name
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Styles");

    for(int i = 0; i < styles.size(); i++) {
        // Insert work name into the table
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(styles[i])));
    }

     ui->tableWidget->setColumnWidth(0, 250);
}


void MainWindow::on_paintingPriceButton_clicked()
{
    Backend backend;
    QString workName = ui->worksPageInput->text();

    if(workName.isEmpty()) {
        qDebug() << "Artist name is empty.";
        return;
    }

    string name = workName.toStdString();

    vector<string> workInfo = backend.searchWorkPrice(name);

    ui->workTableWidget->clear();
    ui->workTableWidget->setRowCount(0);
    ui->workTableWidget->setColumnCount(3);

    ui->workTableWidget->setHorizontalHeaderLabels(QStringList() << "Work Name" << "Sale Price" << "Regular Price");

    if (!workInfo.empty()) {
        int row = 0;
        ui->workTableWidget->insertRow(row);
        ui->workTableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(workInfo[0])));
        ui->workTableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(workInfo[1])));
        ui->workTableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(workInfo[2])));
    }
    else {
        qDebug() << "No work found for the given name.";
    }
}


void MainWindow::on_artistWorkPricesButton_clicked()
{
    Backend backend;
    QString artistName = ui->artistPageInput->text();

    if(artistName.isEmpty()) {
        qDebug() << "Artist name is empty";
        return;
    }

    string name = artistName.toStdString();

    vector<string> workInfo = backend.searchArtistWorkPrice(name);

    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(4);

    ui->workTableWidget->setHorizontalHeaderLabels(QStringList() << "Artist Name" << "Work Name" << "Sale Price" << "Regular Price");

    int totalRows = workInfo.size()/4;
    for(int i = 0; i < totalRows; i++) {
        ui->workTableWidget->insertRow(i);
        ui->workTableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(workInfo[i*4+0])));
        ui->workTableWidget->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(workInfo[i*4+1])));
        ui->workTableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(workInfo[i*4+2])));
        ui->workTableWidget->setItem(i, 3, new QTableWidgetItem(QString::fromStdString(workInfo[i*4+3])));
    }
}


void MainWindow::on_museumDaysAndHoursButton_clicked()
{
    Backend backend;
    QString museumName = ui->museumsPageInput->text();

    if(museumName.isEmpty()) {
        qDebug() << "Museum name is empty.";
        return;
    }

    string mName = museumName.toStdString();

    vector<string> museumInfo = backend.searchMuseumDaysAndHoursByName(mName);

    ui->museumTableWidget->clear();
    ui->museumTableWidget->setRowCount(0);
    ui->museumTableWidget->setColumnCount(3);
    ui->museumTableWidget->setHorizontalHeaderLabels(QStringList() << "Day" << "Open" << "Close");

    if (!museumInfo.empty()) {
        int row = 0;
        ui->museumTableWidget->insertRow(row);
        ui->museumTableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(museumInfo[0])));
        ui->museumTableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(museumInfo[1])));
        ui->museumTableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(museumInfo[2])));
    }
    else {
        qDebug() << "No museum found for the given name.";
    }
}


void MainWindow::on_addressInfoButton_clicked()
{
    Backend backend;

    vector<string> addressInfo = backend.searchAddressInfo();

    ui->museumTableWidget->clear();
    ui->museumTableWidget->setRowCount(addressInfo.size());
    ui->museumTableWidget->setColumnCount(3);
    ui->museumTableWidget->setHorizontalHeaderLabels(QStringList() << "Country" << "State" << "City");

    if (!addressInfo.empty()) {
        int row = 0;
        ui->museumTableWidget->insertRow(row);
        ui->museumTableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(addressInfo[0])));
        ui->museumTableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(addressInfo[1])));
        ui->museumTableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(addressInfo[2])));
    }
    else {
        qDebug() << "No museum found for the given name.";
    }
}


void MainWindow::on_worksInMuseumButton_clicked()
{
    Backend backend;
    QString name = ui->museumsPageInput->text();
    string museumName = name.toStdString();

    vector<string> works = backend.searchMuseumWork(museumName);

    ui->museumTableWidget->clear();
    ui->museumTableWidget->setRowCount(0);
    ui->museumTableWidget->setColumnCount(1);
    ui->museumTableWidget->setHorizontalHeaderLabels(QStringList() << "Painting name");

    ui->museumTableWidget->setColumnWidth(0, 250);

    if(!works.empty()) {
        for(int i = 0; i < works.size(); i++) {
            ui->museumTableWidget->insertRow(i);
            ui->museumTableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(works[i])));
        }
    }
    else {
        qDebug() << "No museum found for the given name.";
    }
}


void MainWindow::on_museumAddressButton_clicked()
{
    Backend backend;
    QString name = ui->museumsPageInput->text();
    string museumName = name.toStdString();

    vector<string> address = backend.searchMuseumAddress(museumName);

    ui->museumTableWidget->clear();
    ui->museumTableWidget->setRowCount(0);
    ui->museumTableWidget->setColumnCount(4);
    ui->museumTableWidget->setHorizontalHeaderLabels(QStringList() << "Name" << "Country" << "State" << "City");

    if(!address.empty()) {
        int row = 0;
        ui->museumTableWidget->insertRow(row);
        ui->museumTableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(address[0])));
        ui->museumTableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(address[1])));
        ui->museumTableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(address[2])));
        ui->museumTableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(address[3])));
    }
    else {
        qDebug() << "No museum found for the given name.";
    }
}



void MainWindow::on_workInMuseumButton_clicked()
{
    Backend backend;
    QString name = ui->worksPageInput->text();
    string mName = name.toStdString();

    vector<string> museums = backend.searchWorkInMuseum(mName);

    ui->workTableWidget->clear();
    ui->workTableWidget->setRowCount(0);
    ui->workTableWidget->setColumnCount(1);
    ui->workTableWidget->setHorizontalHeaderLabels(QStringList() << "Name");

    ui->workTableWidget->setColumnWidth(0, 250);

    if(!museums.empty()) {
        for(int i = 0; i < museums.size(); i++) {
            ui->workTableWidget->insertRow(i);
            ui->workTableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(museums[0])));
        }
    }
    else {
        qDebug() << "No museum found for the given name.";
    }
}


void MainWindow::on_statsButton_clicked()
{

    Backend backend;
    vector<int> stats = backend.getTotals();

    ui->statsList->clear();

    if (!stats.empty() && stats[0] >= 0) {
        ui->statsList->addItem("Total Works: " + QString::number(stats[0]));
        ui->statsList->addItem("Total Artists: " + QString::number(stats[1]));
        ui->statsList->addItem("Total Museums: " + QString::number(stats[2]));
    }
    else {
        qDebug() << "Not found.";
    }
}


void MainWindow::on_paintingSizeInfoButton_clicked()
{
    Backend backend;
    QString name = ui->worksPageInput->text();
    string workName = name.toStdString();

    vector<string> workSize = backend.searchWorkSize(workName);

    ui->workTableWidget->clear();
    ui->workTableWidget->setRowCount(0);
    ui->workTableWidget->setColumnCount(3);
    ui->workTableWidget->setHorizontalHeaderLabels(QStringList() << "Name" << "Width" << "Height");

    if(!workName.empty()) {
        int row = 0;
        ui->workTableWidget->insertRow(row);
        ui->workTableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(workSize[0])));
        ui->workTableWidget->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(workSize[1])));
        ui->workTableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(workSize[2])));

    }
    else {
        qDebug() << "No museum found for the given name.";
    }
}

