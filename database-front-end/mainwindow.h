#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "artistwindow.h"
#include "workswindow.h"
#include "museumwindow.h"
#include "homewindow.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // Switch pages
    void on_worksButton_clicked();
    void on_museumsButton_clicked();
    void on_artistsButton_clicked();
    void on_homeButton_clicked();

    // homePage stuff

    // workPage buttons

    // museumPage buttons
    //void onMuseumInfoClicked();

    // artistPage buttons
    //void onListAllArtistsClicked();

    void on_artistInfoButton_clicked();

    void on_artistsNationalitiesButton_clicked();

    void on_listAllArtistsButton_clicked();

    void on_artistsInMuseumButton_clicked();

    void on_listAllMuseumsButton_clicked();

    void on_museumInfoButton_clicked();

    void on_listAllWorksButton_clicked();

    void on_workInfoButton_clicked();

private:
    Ui::MainWindow *ui;

    HomeWindow *homeWindow;
    ArtistWindow *artistWindow;
    WorksWindow *worksWindow;
    MuseumWindow *museumWindow;
};
#endif // MAINWINDOW_H
