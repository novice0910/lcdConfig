#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    centralWidget = new QWidget(ui->centralWidget);
    centralWidget->setStyleSheet("background-image:url(10.bmp)");
    centralWidget->resize(QSize(800,480));
    scene = new myScene(centralWidget);
    int w =static_cast< QWidget *>(scene->parent())->size().width();
    int h =static_cast< QWidget *>(scene->parent())->size().height();
    scene->setSceneRect(QRectF(0, 0, w, h));
    connect(scene,SIGNAL(signalItemHasInserted(myItem*)),this,SLOT(slotItemHasInserted(myItem*)));
    view = new QGraphicsView(scene,centralWidget);
    view->setGeometry(0,0,800,480);
    view->resize(centralWidget->size());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    widgetInit();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::widgetInit()
{
    QDockWidget * dockWidgetPageProperty = new QDockWidget("image",this);
    dockWidgetPageProperty->setAllowedAreas(Qt::LeftDockWidgetArea);
    dockWidgetPageProperty->setFeatures(QDockWidget::DockWidgetMovable);
    this->addDockWidget(Qt::LeftDockWidgetArea,dockWidgetPageProperty);
    QMainWindow *leftDockMainwindow = new QMainWindow;
    leftDockMainwindow->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
//    leftDockMainwindow->setStyleSheet("background-image:url(10.bmp)");
    dockWidgetPageProperty->setWidget(leftDockMainwindow);
    leftDockMainwindow->setParent(dockWidgetPageProperty);
    pageTabWidget = new QTableWidget(leftDockMainwindow);
    leftDockMainwindow->setCentralWidget(pageTabWidget);
    pageTabWidget->setRowCount(2);
    QToolBar *pToolBar = leftDockMainwindow->addToolBar("new");
    pToolBar->addAction(tr("新增"),this,SLOT(slotActionNewPage()));
    pToolBar->addAction(tr("删除"),this,SLOT(slotActionNewPage()));
    pToolBar->addAction(tr("上移"),this,SLOT(slotActionNewPage()));
    pToolBar->addAction(tr("下移"),this,SLOT(slotActionNewPage()));

    QDockWidget *dockWidgetPropertyShow = new QDockWidget(tr("属性"),this);
    dockWidgetPropertyShow->setAllowedAreas(Qt::LeftDockWidgetArea);
    dockWidgetPropertyShow->setFeatures(QDockWidget::DockWidgetMovable);
    this->addDockWidget(Qt::RightDockWidgetArea,dockWidgetPropertyShow);
    QMainWindow *property = new QMainWindow;
    dockWidgetPropertyShow->setWidget(property);
    propertyShow = new QStackedWidget;
    property->setCentralWidget(propertyShow);

    //按键信息页
    btnPropertyShow = new BtnPropertyShow;
    propertyShow->addWidget(btnPropertyShow);
//    propertyShow->setStyleSheet("background-image:url(10.bmp)");
}

void MainWindow::on_drawBtn_triggered()
{
    scene->setItemType(BTN);
}
void MainWindow::mouseDoubleClickEvent(QMouseEvent *)
{
    qDebug()<<"doubule click";
}
void MainWindow::deleteItem()
{
//    foreach (QGraphicsItem *item, scene->selectedItems()) {
//        if (item->type() == Arrow::Type) {
//            scene->removeItem(item);
//            Arrow *arrow = qgraphicsitem_cast<Arrow *>(item);
//            arrow->startItem()->removeArrow(arrow);
//            arrow->endItem()->removeArrow(arrow);
//            delete item;
//        }
//    }

//    foreach (QGraphicsItem *item, scene->selectedItems()) {
//         if (item->type() == DiagramItem::Type) {
//             qgraphicsitem_cast<DiagramItem *>(item)->removeArrows();
//         }
//         scene->removeItem(item);
//         delete item;
//     }
}
void MainWindow::slotItemHasInserted(myItem *item)
{
    scene->setItemType(MOVE_ITEM);
}

void MainWindow::slotActionNewPage()
{

}
