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


#include <QString>
#include <QStringList>
#include <QSqlTableModel>

class Catalog : public QObject
{
  Q_OBJECT

  QStringList header;
  QSqlTableModel *model;

public:
  Catalog();
  ~Catalog();

  QSqlTableModel* getModel() {
    return model;
  }

public slots:
  void removeElem(QString name);

public:
  void generatePdfList();
  void generatePdfNameplates();

  static const QString databaseFilename;
  static const QString tableName;
  static const int     tableColumns = 10;
  static const QString pdfListFilename;
  static const QString pdfNameplatesFilename;
};


#endif /* __CATALOG_H */

