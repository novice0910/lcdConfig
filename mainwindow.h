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
#include <QToolButton>
#include <QMessageBox>
#include <QSettings>
#include <QTabWidget>
#include <QDir>
#include <QLabel>
#include <QSpinBox>
#include <QFileDialog>
#include <QList>
#include <QMap>
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
    void slotDrawBtnTriggered();//select draw the btn item
    void slotDrawLabTrigger();//select draw the label item
    void mouseDoubleClickEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *ev);
    void slotActionNewPage();
    void slotActionDeletePage();
    void slotActionUp();
    void slotActionDown();
    void slotNewProject();
    void slotOpenProject();
    void slotSaveProject();
    void slotSetProject();
    void slotPageTableWidgetSelectedChanged();
private:
    Ui::MainWindow *ui;
    myScene *scene;
    QGraphicsView *view;
    QWidget *centralWidget;
    QTabWidget * tabWidget;//show the welcome page and stackedView
    QStackedWidget *stackedView;//stackedView to show different page and item
    QTableWidget *pageTableWidget;//on left dockwidget show the page information
    QStackedWidget *propertyShow;//on right dockwidget show widget property when it has been selected
    BtnPropertyShow *btnPropertyShow;//show the btn property
    QDockWidget * dockWidgetPageProperty;
    QDockWidget *dockWidgetPropertyShow;
    QFileInfo m_prjFileInfo;//storage the project information include path and project name
    QList<QGraphicsView*> viewList;//storage all the view
    QList<myScene*> sceneList;//storage all the scene
    int m_pageSum;
    QMap <int,QString> m_background;
    int m_selectedPageNum;//current selected page

    void dataInit();
    void centralWidgetCreate();
    void allWidgetCreate();//create all the widget on the mainwindow
    void toolBarCreate();//create toolBar and all aciton on this
    void leftDockWidgetCreate();//create left DockWidget and widget on it
    void rightDockWidgetCreate();//create right dockwidget and widge on it
    void deleteItem();//delete the select Item
    void newOnePage();
    void delectOnePage();
};

#endif // MAINWINDOW_H
