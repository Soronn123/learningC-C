#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "screenmenu.h"
#include "chartxy.h"

#include "parserMath.h"
#include <boost/algorithm/string.hpp>

#include "QDir"
#include "QTableWidget"
#include "QTableWidgetItem"
#include "QStatusBar"
#include "QAbstractButton"
#include <QVector>

#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalBarSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QtCharts>


#include <QFile>
#include <QTextStream>
#include <QtAxContainer/QAxObject>


bool CHANGE_SETTINGS = true;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(800, 600);

    ui->table_->setHidden(true);

    ui->formula_->setText("y*(x*x+1)");
    ui->h_->setText("0.1");
    ui->y_->setText("1");
    ui->x0_->setText("0");
    ui->xn_->setText("1");
}

MainWindow::~MainWindow()
{
    delete ui;
}


bool CreateLog(std::vector<std::vector<double>>& case_)
{
    int COLUMN = 2;
    try{
        QString filename = "log.txt";
        QFile file(filename);
        if (file.open(QIODevice::ReadWrite)) {
            QTextStream stream(&file);
            stream << "x" << "\t" << "y" << "\n";
            for (int row = 0; row < case_.size(); row++)
            {
                for(int col=0; col < COLUMN ; col++)
                {
                    stream << QString::number(case_[row][col]);
                    stream << "\t";
                }
                stream << "\n";
            }
            stream << "Конец" << "\n";
        }
        return true;
    }
    catch(...){
        return false;
    }
}


bool CreateExcel(std::vector<std::vector<double>>& case_)
{
    int COLUMN = 2;
    try{
        const QString fileName = (QDir().absolutePath() + "\\log.xlsx").replace("/", "\\");

        QAxObject* excel = new QAxObject( "Excel.Application", 0 );
        excel->dynamicCall( "SetVisible(bool)", false );
        QAxObject* workbooks = excel->querySubObject( "Workbooks" );
        QAxObject* workbook = workbooks->querySubObject( "Add" );
        QAxObject* sheets = workbook->querySubObject( "Worksheets" );
        QAxObject* sheet = sheets->querySubObject( "Add" );

        for (int row = 0; row < case_.size(); row++)
        {
            for(int col=0; col < COLUMN ; col++)
            {
                QAxObject* cell = sheet->querySubObject("Cells(int,int)", row + 1, col + 1);
                cell->dynamicCall( "SetValue(const QVariant&)",  QString::number(case_[row][col]));
                delete cell;
            }
        }
        delete sheet;
        delete sheets;

        workbook->dynamicCall("SaveAs (const QString&)", fileName);
        delete workbook;

        workbooks->dynamicCall("Close (Boolean)", false);
        delete workbooks;

        excel->dynamicCall("Quit (void)");
        delete excel;
        return true;
    }
    catch(...){
        return false;
    }
}


void MainWindow::on_pushButton_clicked()
{
    const int COLUMN = 2;

    ui->result_->setText("");
    ui->statusbar->showMessage("");

    try{
        std::vector<std::vector<double>> case_;

        std::string expr = (ui->formula_->text()).toStdString();
        std::string expr_copy;

        std::string h_str = (ui->h_->text()).toStdString();
        std::string y_str = (ui->y_->text()).toStdString();
        std::string x0_str = (ui->x0_->text()).toStdString();
        std::string xn_str = (ui->xn_->text()).toStdString();

        double h = CalcArithExpr(h_str.begin(), h_str.end());
        double y = CalcArithExpr(y_str.begin(), y_str.end());
        double x0 = CalcArithExpr(x0_str.begin(), x0_str.end());
        double xn = CalcArithExpr(xn_str.begin(), xn_str.end());

        ui->statusbar->showMessage("Преобразование чисел, произошло успешно");

        while(x0 < xn)
        {
            case_.push_back({x0,y});

            expr_copy = expr;
            boost::replace_all(expr_copy, "x", std::to_string(x0));
            boost::replace_all(expr_copy, "y", std::to_string(y));

            if(ui->post_out->isChecked()){ui->result_->setText(ui->result_->text() + QString::fromStdString(expr_copy) + "\n");}

            y = y + h * CalcArithExpr(expr_copy.begin(), expr_copy.end());
            x0 += h;
        }

        ui->statusbar->showMessage(ui->statusbar->currentMessage() + "     Вычисления все прошли успешно");

        ui->table_->setHidden(false);
        ui->table_->setColumnCount( COLUMN );
        ui->table_->setRowCount( case_.size() );
        ui->table_->setShowGrid( true );
        ui->table_->setSelectionMode( QAbstractItemView::SingleSelection );
        ui->table_->setHorizontalHeaderLabels( {"x", "y"} );
        for (int row = 0; row < case_.size(); row++){
            for(int col=0; col < COLUMN ; col++)
            {
                QTableWidgetItem *item = ui->table_->item(row, col);
                if(!item) {
                    item = new QTableWidgetItem();
                    item->setFlags(Qt::ItemIsEnabled);
                    ui->table_->setItem(row, col, item);
                }
                item->setText(QString::number(case_[row][col]));
            }
        }

        if(ui->post_log->isChecked())
        {
            ui->statusbar->showMessage(ui->statusbar->currentMessage() + "     ");
            if(CreateLog(case_)){ui->statusbar->showMessage(ui->statusbar->currentMessage() + "Log - возможен создан");}
            else{ui->statusbar->showMessage(ui->statusbar->currentMessage() + "Произошла ошибка записи в Log");}
        }
        if(ui->post_excel->isChecked())
        {
            ui->statusbar->showMessage(ui->statusbar->currentMessage() + "     ");
            if(CreateExcel(case_)){ui->statusbar->showMessage(ui->statusbar->currentMessage() + "Excel - успех");}
            else{ui->statusbar->showMessage(ui->statusbar->currentMessage() + "Произошла ошибка записи в Excel");}
        }
        if(ui->post_picture->isChecked())
        {
            Chartxy *w = new Chartxy();
            w->show();
            w->get_dates(case_);
        }
    } catch(const std::exception &ex) {
        ui->statusbar->showMessage(ui->statusbar->currentMessage() + ex.what());}
}


void MainWindow::on_settings__clicked()
{
    if (CHANGE_SETTINGS){
        ui->groupBox->setHidden(true);
        CHANGE_SETTINGS = false;
    }else{
        ui->groupBox->setHidden(false);
        CHANGE_SETTINGS = true;
    }
}

void MainWindow::on_back__clicked()
{
    ScreenMenu *w = new ScreenMenu;
    w->show();
    this->close();
}


