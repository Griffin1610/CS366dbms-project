#include "museumwindow.h"
#include "ui_museumwindow.h"

MuseumWindow::MuseumWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MuseumWindow)
{
    ui->setupUi(this);
}

MuseumWindow::~MuseumWindow()
{
    delete ui;
}

void MuseumWindow::setMuseumData(const std::vector<int>& museum_id,
                                 const std::vector<std::string>& name,
                                 const std::vector<std::string>& address,
                                 const std::vector<std::string>& phone,
                                 const std::vector<std::string>& url)
{
    int numRows = museum_id.size();
}
