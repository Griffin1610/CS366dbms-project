#ifndef WORKSWINDOW_H
#define WORKSWINDOW_H

#include <QDialog>
#include <vector>

namespace Ui {
class WorksWindow;
}

class WorksWindow : public QWidget
{
    Q_OBJECT

public:
    explicit WorksWindow(QWidget *parent = nullptr);
    ~WorksWindow();

void setWorkData(const std::vector<int>& work_id,
             const std::vector<std::string>& name,
             const std::vector<int>& artist_id,
             const std::vector<std::string>& style,
             const std::vector<std::string>& url,
             const std::vector<std::string>& subject,
             const std::vector<int>& museum_id,
             const std::vector<int>& size_id);

private:
    Ui::WorksWindow *ui;
};

#endif // WORKSWINDOW_H
