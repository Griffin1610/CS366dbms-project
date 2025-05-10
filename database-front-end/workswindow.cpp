#include "workswindow.h"
#include "ui_workswindow.h"
#include <QWidget>

WorksWindow::WorksWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::WorksWindow)
{
    ui->setupUi(this);
}

WorksWindow::~WorksWindow()
{
    delete ui;
}

void WorksWindow::setWorkData(const std::vector<int>& work_id,
                          const std::vector<std::string>& name,
                          const std::vector<int>& artist_id,
                          const std::vector<std::string>& style,
                          const std::vector<std::string>& url,
                          const std::vector<std::string>& subject,
                          const std::vector<int>& museum_id,
                          const std::vector<int>& size_id) {
    int numRows = work_id.size();
    //ui->tableWidget->setRowCount(numRows);

}
