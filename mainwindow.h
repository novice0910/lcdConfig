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
#include <QKeyEvent>
#include "myitem.h"
#include "BtnPropertyShow.h"
#include "myscene.h"
#include "data.h"
#include "ComSet.h"

namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
signals:
    void signalSaveAllItemToConfig(QString path);//send the signal to scene save the all item in the path
    void signalOpenAllItemConfig(QString path);//read all config
    void signalDeleteSelectedItemToScene(PROPERETY_SHOW_INDEX index);//send witch  kind item and tell scene to delecte the selected one
public slots:
    void slotGetWhichItemHasSelected(PROPERETY_SHOW_INDEX index);//set the stackedView index
private slots:
    void slotDrawBtnTriggered();//select draw the btn item
    void slotDrawLabTrigger();//select draw the label item
    void mouseDoubleClickEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *ev);
    void keyPressEvent(QKeyEvent *key);
    void actionNewPage();
    void actionDeleteOnePage();
    void actionDeleteAllPage();
    void actionPageUp();
    void actionPageDown();

    void actionNewProject();
    void actionOpenProject();
    void slotSaveProject();
    void actionSetProject();
    void slotPageTableWidgetSelectedChanged();
private:
    Ui::MainWindow *ui;
    QTabWidget * tabWidget;//show the welcome page and stackedView
    QStackedWidget *stackedView;//stackedView to show different page and item
    QTableWidget *pageTableWidget;//on left dockwidget show the page information
    QStackedWidget *propertyShow;//on right dockwidget show widget property when it has been selected
    BtnPropertyShow *btnPropertyShow;//show the btn property
    QDockWidget * dockWidgetPageProperty;
    QDockWidget *dockWidgetPropertyShow;

    //store information
    QFileInfo m_prjFileInfo;//storage the project information include path and project name
    QList<QWidget *> pageList;//storage all the page on stackedView
    QList<QGraphicsView*> viewList;//storage all the view
    QList<myScene*> sceneList;//storage all the scene
    QMap <int,QString> m_background;//storage all the background image name

    int m_pageSum;// page sum
    QLabel *lableCurrentIndex;//the label show the current page index
    int m_selectedPageNum;//current selected page from zero

    void dataInit();
    void centralWidgetCreate();
    void allWidgetCreate();//create all the widget on the mainwindow
    void toolBarCreate();//create toolBar and all aciton on this
    void leftDockWidgetCreate();//create left DockWidget and widget on it
    void rightDockWidgetCreate();//create right dockwidget and widge on it
    void newOnePage();
    void newOnePage(int index); //when read project
    bool removeFolderContent(const QString &folderDir);

};

#endif // MAINWINDOW_H
