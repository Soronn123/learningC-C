#ifndef SCREENMENU_H
#define SCREENMENU_H

#include <QMainWindow>

namespace Ui {
class ScreenMenu;
}

class ScreenMenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit ScreenMenu(QWidget *parent = nullptr);
    ~ScreenMenu();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::ScreenMenu *ui;
};

#endif // SCREENMENU_H
