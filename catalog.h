/**
 * \file   catalog.h
 *
 * \author Maria Levshinovskaya <masa.levs@gmail.com>
 * 
 * \brief
 *
 *
 */
#ifndef __CATALOG_H
#define __CATALOG_H

#include "element.h"

#include <QString>
#include <QStringList>
#include <QSqlTableModel>

class Catalog
{
  QStringList header;
  QSqlTableModel *model;

public:
  Catalog();
  ~Catalog();

  QSqlTableModel* getModel() {
    return model;
  }


  void generatePdfList();
  void generatePdfNameplates();

  static const QString databaseFilename;
  static const QString tableName;
  static const int     tableColumns = 10;
};


#endif /* __CATALOG_H */

