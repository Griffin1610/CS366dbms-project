#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

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

    void on_allArtistsWorksButton_clicked();

    void on_artistStylesButton_clicked();

    void on_paintingPriceButton_clicked();

    void on_artistWorkPricesButton_clicked();

    void on_museumDaysAndHoursButton_clicked();

    void on_addressInfoButton_clicked();

    void on_worksInMuseumButton_clicked();

    void on_museumAddressButton_clicked();

    void on_workInMuseumButton_clicked();

private:
    Ui::MainWindow *ui;

    QSqlDatabase connectToDatabase();

    HomeWindow *homeWindow;
    ArtistWindow *artistWindow;
    WorksWindow *worksWindow;
    MuseumWindow *museumWindow;
};
#endif // MAINWINDOW_H
