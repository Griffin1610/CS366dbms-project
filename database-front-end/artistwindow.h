#ifndef ARTISTWINDOW_H
#define ARTISTWINDOW_H

#include <QDialog>
#include <string>
#include <vector>

namespace Ui {
class ArtistWindow;
}


class ArtistWindow : public QWidget
{
    Q_OBJECT

public:
    ArtistWindow(QWidget *parent = nullptr);
    ~ArtistWindow();

private:
    Ui::ArtistWindow *ui;
};

#endif // ARTISTWINDOW_H
