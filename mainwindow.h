#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include "myitem.h"
#include "myscene.h"
#include <QMouseEvent>
#include <QDebug>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_drawBtn_triggered();
    void mouseDoubleClickEvent(QMouseEvent *);
private:
    Ui::MainWindow *ui;
    myScene *scene;
    QGraphicsView *view;

    void deleteItem();
};

#endif // MAINWINDOW_H
