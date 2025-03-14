#ifndef CHARTXY_H
#define CHARTXY_H

#include <QMainWindow>

namespace Ui {
class Chartxy;
}

class Chartxy : public QMainWindow
{
    Q_OBJECT

public:
    explicit Chartxy(QWidget *parent = nullptr);
    ~Chartxy();

    void get_dates(std::vector<std::vector<double>>& case_);

private:
    Ui::Chartxy *ui;
};

#endif // CHARTXY_H
