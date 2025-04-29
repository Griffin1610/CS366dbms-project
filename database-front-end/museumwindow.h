#ifndef MUSEUMWINDOW_H
#define MUSEUMWINDOW_H

#include <QDialog>
#include <vector>
#include <string>
namespace Ui {
class MuseumWindow;
}

class MuseumWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MuseumWindow(QWidget *parent = nullptr);
    ~MuseumWindow();

void setMuseumData(const std::vector<int>& museum_id,
                   const std::vector<std::string>& name,
                   const std::vector<std::string>& address,
                   const std::vector<std::string>& phone,
                   const std::vector<std::string>& url);

private:
    Ui::MuseumWindow *ui;
};

#endif // MUSEUMWINDOW_H
