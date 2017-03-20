#include "myscene.h"

myScene::myScene( QObject *parent)
    :QGraphicsScene(parent)
{
    widgetType = MOVE_ITEM;
}

void myScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug()<<"mouse press event";
    if (mouseEvent->button() != Qt::LeftButton)
        return;
    if(widgetType == MOVE_ITEM)
    {
        itemList = selectedItems();
        myItem *item = 0;

        if(itemList.size() == 1 )
        {
             qDebug()<<"item size >1";
            item = qgraphicsitem_cast<myItem*>(itemList.first());
        }
        if(item != 0)
        {
//            item->hitTest(mouseEvent->pos());
            qDebug()<<"item pos x"<<item->scenePos().x();
        }
    }
    else
    {
        myItem *item;
        item = new myItem(widgetType);
        addItem(item);
        item->moveBy(mouseEvent->scenePos().rx(),mouseEvent->scenePos().ry());
        emit signalItemHasInserted(item);
    }
    update();
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void myScene::setItemType(itemType type)
{
    widgetType = type;
}
