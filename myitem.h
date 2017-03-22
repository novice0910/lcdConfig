#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QRectF>
#include <QPainterPath>
#include <QPen>
#include <unistd.h>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QStyleOptionGraphicsItem>
#include <QCursor>

#define VERTEX_DIS 3
#define SIZE_WIDTH 800
#define SIZE_HIGHT 480
enum DIRECTION{
    NONE,LEFT,RIGHT,TOP,BOTTOM,LEFT_TOP,
    RIGHT_TOP,LEFT_BOTTOM,RIGHT_BOTTOM,MOVE
};

class myItem :public QGraphicsItem
{
public:
    myItem(qreal width = 20,qreal height = 10);
    enum { Type = UserType + 15 };
    int type() const
        { return Type;}
protected:
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape()const;
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
private:
    qreal m_width;
    qreal m_height;
    QCursor *m_cursor;
    bool m_isSelected;
    QPointF start;
    QPointF end;
    DIRECTION direction;
    void judgeMousePosition(QPointF pointF);
};

#endif // MYITEM_H
