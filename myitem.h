#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPainter>
#include <unistd.h>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QStyleOptionGraphicsItem>
#include <QPen>
#include <QCursor>
#include <QDebug>

enum itemType { BTN,LABEL,MSG ,INPUT_BTN,RTC,MOVE_ITEM};
enum Direction { LeftTop , Top, RightTop, Right, RightBottom, Bottom, LeftBottom, Left , Center, None};

class myItem :public QGraphicsRectItem
{
public:
    enum { Type = UserType + 15 };

    myItem(itemType type);

    void ResetRect(QRectF rect);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
private:
    itemType m_type;
    QPolygonF myPolygon;
    typedef QList<QGraphicsItem*> Handles;
    QRectF m_rect;
    QCursor *m_cursor;
    bool cScale;
    QPointF start;
    QPointF end;
    int direction;
    QTimer *timer;

};

#endif // MYITEM_H
