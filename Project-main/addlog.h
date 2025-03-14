#ifndef ADD_LOG_H
#define ADD_LOG_H

#include <QFile>
#include <QTextStream>
#include <QtAxContainer/QAxObject>

void MainWindow::CreateFile()
{
    //log.xlsx

    QAxObject *excel = new QAxObject("Excel.Application", this);
}




#endif // ADD_LOG_H
