#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(840,320);

    catalog = new Catalog();
    
    ui->results->setModel(catalog->getModel());
//    ui->results->setItemDelegate(new QSqlRelationalDelegate(ui->results));

    ui->results->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->results->setColumnHidden(0, true);
    ui->results->resizeColumnsToContents();
    ui->results->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->hint->setText("");
    ui->filter_text->setEnabled(false);

    ui->bEdit->setEnabled(false);

    QObject::connect(ui->bExit, SIGNAL(clicked()), this, SLOT(close()));

}

MainWindow::~MainWindow()
{
  delete catalog;
  delete ui;
}

