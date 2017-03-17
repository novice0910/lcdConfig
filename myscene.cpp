#include "myscene.h"

myScene::myScene( QObject *parent)
    :QGraphicsScene(parent)
{
    widgetType = MOVE_ITEM;
}

void myScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;
    if(widgetType == MOVE_ITEM)
    {
        itemList = selectedItems();
        myItem *item = 0;

        if(itemList.count() == 1 )
        {
            item = qgraphicsitem_cast<myItem*>(itemList.first());
        }
        if(item != 0)
        {
//            item->hitTest(mouseEvent->pos());
        }
    }
    else
    {
        myItem *item;
        item = new myItem(widgetType);
        addItem(item);
        item->setPos(mouseEvent->scenePos());
        emit signalItemHasInserted(item);
    }
    update();
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void myScene::setItemType(itemType type)
{
    qDebug()<<"type"<<type;
    widgetType = type;
}
