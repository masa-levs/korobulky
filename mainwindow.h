#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "catalog.h"

#include <QMainWindow>


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
  /**
   * \brief Форма.
   */
  Ui::MainWindow *ui;

  Catalog *catalog;

};

#endif // MAINWINDOW_H
