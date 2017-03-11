#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QColor>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include "myitem.h"

class myScene :public QGraphicsScene
{
    Q_OBJECT
public:
    myScene(QObject *parent = 0);
    void setItemType(itemType type);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
private:
    itemType widgetType;
};

#endif // MYSCENE_H
