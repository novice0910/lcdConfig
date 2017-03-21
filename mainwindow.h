#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsPathItem>
#include <QDockWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QToolBar>
#include <QTableWidget>
#include <QStackedWidget>
#include <QGridLayout>
#include <QLabel>
#include <QSpinBox>
#include "myitem.h"
#include "BtnPropertyShow.h"
#include "myscene.h"
#include "data.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void slotItemHasInserted(myItem *item);
    void slotGetBtnInfoFromScene(BTN_INFO *);
private slots:
    void slotDrawBtnTriggered();
    void slotDrawLabTrigger();
    void mouseDoubleClickEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *ev);
    void slotActionNewPage();
    void slotActionDeletePage();
    void slotActionUp();
    void slotActionDown();
private:
    Ui::MainWindow *ui;
    myScene *scene;
    QGraphicsView *view;
    QWidget *centralWidget;
    QTableWidget *pageTabWidget;
    QStackedWidget *propertyShow;
    BtnPropertyShow *btnPropertyShow;
    void widgetCreate();
    void toolBarCreate();
    void leftDockWidgetCreate();
    void rightDockWidgetCreate();
    void deleteItem();

};

#endif // MAINWINDOW_H
