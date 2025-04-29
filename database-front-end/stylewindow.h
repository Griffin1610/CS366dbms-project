#ifndef STYLEWINDOW_H
#define STYLEWINDOW_H

#include <QDialog>

namespace Ui {
class StyleWindow;
}

class StyleWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StyleWindow(QWidget *parent = nullptr);
    ~StyleWindow();

private:
    Ui::StyleWindow *ui;
};

#endif // STYLEWINDOW_H
