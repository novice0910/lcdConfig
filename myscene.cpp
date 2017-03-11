#include "myscene.h"

myScene::myScene()
{
}

void myScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;

    myItem *item;
    item = new myItem(widgetType);
    addItem(item);
    item->setPos(mouseEvent->scenePos());
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void myScene::setItemType(itemType type)
{
    widgetType = type;
}
