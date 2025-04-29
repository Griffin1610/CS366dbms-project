#include "stylewindow.h"
#include "ui_stylewindow.h"

StyleWindow::StyleWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::StyleWindow)
{
    ui->setupUi(this);
}

StyleWindow::~StyleWindow()
{
    delete ui;
}
