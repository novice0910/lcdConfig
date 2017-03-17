#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QDebug>
#include "myitem.h"
#include <QList>

typedef QList<QGraphicsItem*> ITEM_LIST;
class myScene :public QGraphicsScene
{
    Q_OBJECT
public:
    myScene(QObject *parent = 0);
    void setItemType(itemType type);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);

signals:
    void signalItemHasInserted(myItem *item);


private:
    ITEM_LIST itemList;
    itemType widgetType;
    QGraphicsPathItem * dashRect;
};

#endif // MYSCENE_H
