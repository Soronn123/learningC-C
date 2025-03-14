#include "chartxy.h"
#include "ui_chartxy.h"

#include <QVector>


Chartxy::Chartxy(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Chartxy)
{
    ui->setupUi(this);
}

Chartxy::~Chartxy()
{
    delete ui;
}

void Chartxy::get_dates(std::vector<std::vector<double>>& case_)
{
    QVector<double> x_chart, y_chart;

    for(std::vector<double> coords : case_)
    {
        x_chart.push_back(coords[0]);
        y_chart.push_back(coords[1]);
    }

    ui->chartss->xAxis->setRange(*std::min_element(x_chart.begin(), x_chart.end()), *std::max_element(x_chart.begin(), x_chart.end()));
    ui->chartss->yAxis->setRange(*std::min_element(y_chart.begin(), y_chart.end()), *std::max_element(y_chart.begin(), y_chart.end()));

    ui->chartss->addGraph();
    ui->chartss->graph(0)->addData(x_chart, y_chart);
    ui->chartss->replot();
}
