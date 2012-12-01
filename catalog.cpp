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


const QString Catalog::databaseFilename = "catalog.db";
const QString Catalog::tableName = "details";

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

  model->select();
 
}

Catalog::~Catalog()
{
}


void Catalog::generatePdfList()
{
}

void Catalog::generatePdfNameplates()
{
}



