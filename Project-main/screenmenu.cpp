#include "screenmenu.h"
#include "ui_screenmenu.h"
#include "mainwindow.h"
#include "dialog.h"
#include "information.h"

ScreenMenu::ScreenMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ScreenMenu)
{
    ui->setupUi(this);
    this->setFixedSize(671, 342);
}

ScreenMenu::~ScreenMenu()
{
    delete ui;
}

void ScreenMenu::on_pushButton_clicked()
{
    MainWindow *w = new MainWindow;
    w->show();
    this->close();
}


void ScreenMenu::on_pushButton_2_clicked()
{
    Dialog *w = new Dialog;
    w->show();
}


void ScreenMenu::on_pushButton_3_clicked()
{
    Information *w = new Information;
    w->show();
}

