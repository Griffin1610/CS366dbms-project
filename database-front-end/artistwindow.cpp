#include "artistwindow.h"
#include "ui_artistwindow.h"

ArtistWindow::ArtistWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ArtistWindow)
{
    ui->setupUi(this);
}

ArtistWindow::~ArtistWindow()
{
    delete ui;
}

void ArtistWindow::setArtistData(const std::vector<int>& artist_id,
                                 const std::vector<std::string>& name,
                                 const std::vector<std::string>& nationality,
                                 const std::vector<std::string>& style,
                                 const std::vector<int>& birth,
                                 const std::vector<int>& death)
{
    int numRows = artist_id.size();
    //ui->tableWidget->setRowCount(numRows);
}
