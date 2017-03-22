#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QDebug>
#include <QList>
#include "data.h"
#include "MyWidget.h"

typedef QList<QGraphicsItem*> ITEM_LIST;

class myScene :public QGraphicsScene
{
    Q_OBJECT
public:
    myScene(QObject *parent = 0);
    void setItemType(ITEM_TYPE type);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:
    void signalItemHasInserted(myItem *item);
    void signalSendBtnInfoToUI(BTN_INFO *);

private:
    ITEM_LIST itemList;
    ITEM_TYPE m_ItemType;
    QGraphicsPathItem * dashRect;
    myItem *m_selectedItem;
    void getItemInfo(myItem *item);
};

#endif // MYSCENE_H
