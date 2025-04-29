#ifndef ARTISTWINDOW_H
#define ARTISTWINDOW_H

#include <QDialog>
#include <string>
#include <vector>

namespace Ui {
class ArtistWindow;
}

class ArtistWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ArtistWindow(QWidget *parent = nullptr);
    ~ArtistWindow();

void setArtistData(const std::vector<int>& artist_id,
                   const std::vector<std::string>& name,
                   const std::vector<std::string>& nationality,
                   const std::vector<std::string>& style,
                   const std::vector<int>& birth,
                   const std::vector<int>& death);


private:
    Ui::ArtistWindow *ui;
};

#endif // ARTISTWINDOW_H
