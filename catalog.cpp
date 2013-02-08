/**
 * \file   catalog.cpp
 *
 * \author Maria Levshinovskaya <masa.levs@gmail.com>
 * 
 * \brief
 *
 *
 */

#include "catalog.h"

#include <QSqlDatabase>
#include <QMessageBox>
#include <QPrinter>
#include <QTextDocument>
#include <QTextCursor>
#include <QTextTable>

#include <cstdio>

const QString Catalog::databaseFilename = "catalog.db";
const QString Catalog::tableName = "details";
const QString Catalog::pdfListFilename = "list.pdf";
const QString Catalog::pdfNameplatesFilename = "nameplates.pdf";

Catalog::Catalog()
{
  header << QString::fromUtf8("ID") <<  QString::fromUtf8("Название") << QString::fromUtf8("Категория") << QString::fromUtf8("Описание") <<
            QString::fromUtf8("Ящик") << QString::fromUtf8("Ряд") << QString::fromUtf8("Столбец") <<
            QString::fromUtf8("Количество") << QString::fromUtf8("URL") << QString::fromUtf8("Цена") << QString::fromUtf8("Комментарий");

  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(databaseFilename);
  if (!db.open()) {
      QMessageBox::critical(0, "Cannot open database",
          "Unable to establish a database connection.\nClick Cancel to exit.", QMessageBox::Cancel);
  }

  model = new QSqlTableModel();
  model->setTable(tableName);

  model->setEditStrategy(QSqlTableModel::OnManualSubmit);

  for (int i=0; i<=tableColumns; i++) {
    model->setHeaderData(i, Qt::Horizontal, header.at(i));
  }

  model->setSort(1, Qt::AscendingOrder);

  model->select();
 
}

Catalog::~Catalog()
{
}


void Catalog::generatePdfList()
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(pdfListFilename);

    QTextDocument doc;
    QTextCursor cursor(&doc);

    QString categ = "test"; // такой категории не должно быть!
    model->setSort(2, Qt::AscendingOrder);

    for (int i=0; i<model->rowCount(); i++) {
        if (model->index(i, 2).data().toString() != categ) {
          categ = model->index(i, 2).data().toString();
          if (categ == "") {
            cursor.insertText(QString::fromUtf8("Прочее"));
          } else {
            cursor.insertText(categ);
          }
          cursor.insertText("\n");
        }
        cursor.insertText("\t");
        cursor.insertText(model->index(i, 1).data().toString());
        cursor.insertText("\n");
        doc.print(&printer);
    }
    model->setSort(1, Qt::AscendingOrder);
}

void Catalog::generatePdfNameplates()
{
    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(pdfNameplatesFilename);

    QTextDocument doc;
    QTextCursor cursor(&doc);

    int cols=5;
    int rows=model->rowCount()/cols + 1;
    QTextTable *table = cursor.insertTable(rows, cols);

    for (int i=0; i<model->rowCount(); i++) {
        QString text;
        text.sprintf("%d:%d:%d\n", model->index(i, 4).data().toInt(), model->index(i, 5).data().toInt(), model->index(i, 6).data().toInt() );
        text.append(model->index(i, 1).data().toString());
        text.append("\n\n");

        QTextTableCell cell = table->cellAt(i/cols, i%cols);
        QTextCursor cellCursor = cell.firstCursorPosition();
        cellCursor.insertText(text);
        
        doc.print(&printer);
    }
}


void Catalog::removeElem(QString name)
{
  int i = 0;
  while (i<model->rowCount()) {
    if (model->index(i, 1).data().toString() == name) {
      model->removeRow(i);
      model->submitAll();
      return;
    }
    i++;
  }
}

void Catalog::addElem(Element elem)
{
    int modelrow = model->rowCount();
    model->insertRows(modelrow, 1);
    model->setData(model->index(modelrow, 1), elem.getName());
    model->setData(model->index(modelrow, 2), elem.getCategory());
    model->setData(model->index(modelrow, 3), elem.getDescription());
    model->setData(model->index(modelrow, 4), elem.getBox());
    model->setData(model->index(modelrow, 5), elem.getRow());
    model->setData(model->index(modelrow, 6), elem.getColumn());
    model->setData(model->index(modelrow, 7), elem.getCount());
    model->setData(model->index(modelrow, 8), elem.getLink());
    model->setData(model->index(modelrow, 9), elem.getPrice());

    if (!model->submitAll()) {
        printf("$$$\n");
    }

}

