#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new myScene(ui->widget);
    scene->setSceneRect(QRectF(0, 0, 10, 10));

    view = new QGraphicsView(scene,ui->widget);
    view->setGeometry(0,0,800,480);
}

MainWindow::~MainWindow()
{
    delete ui;
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
