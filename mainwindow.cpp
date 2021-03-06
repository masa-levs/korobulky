#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "form.h"

#include <QMessageBox>

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
    QObject::connect(ui->bPrint, SIGNAL(clicked()), this, SLOT(generatePdf()));
    QObject::connect(ui->bRemove, SIGNAL(clicked()), this, SLOT(selectToRemove()));
    QObject::connect(this, SIGNAL(selectedToRemove(QString)), catalog, SLOT(removeElem(QString)));
    QObject::connect(ui->bAdd, SIGNAL(clicked()), this, SLOT(addElement()));

}

MainWindow::~MainWindow()
{
  delete catalog;
  delete ui;
}


void MainWindow::generatePdf()
{
    catalog->generatePdfList();
    catalog->generatePdfNameplates();
    QMessageBox::information(this, "Generation PDF", QString::fromUtf8("Файлы list.pdf и nameplates.pdf успешно созданы."));
}

void MainWindow::selectToRemove()
{
  QString name;

  if (ui->results->currentIndex().row() != -1) {
    name = catalog->getModel()->index(ui->results->currentIndex().row(), 1).data().toString();
    emit selectedToRemove(name);
  }
}

void  MainWindow::addElement()
{
    Form *addForm;
    if (ui->filter->currentIndex() == 1)
        addForm = new Form(ui->filter_text->text(),0);
    else
        addForm = new Form("",0);
    addForm->show();
    this->setEnabled(false);

    QObject::connect(addForm, SIGNAL(addedElem(Element)), catalog, SLOT(addElem(Element)));
    QObject::connect(addForm, SIGNAL(closed()), this, SLOT(refresh()));
}

void MainWindow::refresh()
{
  this->setEnabled(true);
  catalog->getModel()->select();
}

