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
    // Queries all works and then displays them
    // work_id, name, artist_id, style, url, subject, museum_id, size_id
    std::vector<int> work_id;
    std::vector<std::string> name;
    std::vector<int> artist_id;
    std::vector<std::string> style;
    std::vector<std::string> url;
    std::vector<std::string> subject;
    std::vector<int> museum_id;
    std::vector<int> size_id;

    /*
    Call back-end function here

    */

    // Create window and execute the functions
    WorksWindow *window = new WorksWindow(this);
    window->setWorkData(work_id, name, artist_id, style, url, subject, museum_id, size_id);
    window->exec();
}




void MainWindow::on_museumsButton_clicked()
{
    // Queries all museums and displays them
    // museum_id, name, address_id, phone, url

    std::vector<int> museum_id;
    std::vector<std::string> name;
    std::vector<std::string> address;
    std::vector<std::string> phone;
    std::vector<std::string> url;

    /*
     Call back-end function here

    */

    // Create window and execute the functions
    MuseumWindow *window = new MuseumWindow(this);
    window->setMuseumData(museum_id, name, address, phone, url);
    window->exec();
}


void MainWindow::on_artistsButton_clicked()
{
    // Queries all artists and displays them
    // artist_id, name, nationality, style, birth, death

    std::vector<int> artist_id;
    std::vector<std::string> name;
    std::vector<std::string> nationality;
    std::vector<std::string> style;
    std::vector<int> birth;
    std::vector<int> death;

    /*
     Call back-end function here

    */
    ArtistWindow *window = new ArtistWindow(this);
    window->setArtistData(artist_id, name, nationality, style, birth, death);
    window->exec();
}


void MainWindow::on_searchButton_clicked()
{
    QString getCategory = ui->categoryBox->currentText();
    QString searchText = ui->lineEdit->text();
    if(searchText.isEmpty()) {
        // Warning here to reject it
        return;
    }
    if(getCategory == "Work") {
        // Work function
    }
    else if(getCategory == "Artist") {
        // Artist function
    }
    else if(getCategory == "Museum") {
        // Museum function
    }
    else if(getCategory == "Style") {
        // Style function
    }
    else {
        // ???
    }
}

