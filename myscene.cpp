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

    }
    else
    {
        myItem *item;
        item = new myItem(widgetType);
        addItem(item);
        item->setPos(mouseEvent->scenePos());
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void myScene::setItemType(itemType type)
{
    qDebug()<<"type"<<type;
    widgetType = type;
}
