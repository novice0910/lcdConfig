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
#include "data.h"

#define VERTEX_DIS 3
#define SIZE_WIDTH 800
#define SIZE_HIGHT 480
enum DIRECTION{
    NONE,LEFT,RIGHT,TOP,BOTTOM,LEFT_TOP,
    RIGHT_TOP,LEFT_BOTTOM,RIGHT_BOTTOM,MOVE
};

class myItem :public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    myItem(qreal width = 100, qreal height = 30);
    enum { Type = UserType + 15 };
    int type() const
        { return Type;}
    void setBrushColor(QColor color);
    virtual ITEM_TYPE getItemType() const
    {
        return m_itemType;
    }

    void setItemType(ITEM_TYPE type)
    {
        m_itemType = type;
    }
    ITEM_TYPE m_itemType;
    qreal m_width;
    qreal m_height;
    bool m_isSelected;

    void changeRect(QRectF rect);//change Rect by others
public slots:
signals:
    void signalSendItemQRectF(QRectF);

protected:
    QRectF boundingRect()const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QPainterPath shape()const;
    QVariant itemChange(GraphicsItemChange change,
                         const QVariant &value);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
private:
    QColor m_brushColor;
    QCursor *m_cursor;
    QPointF start;
    QPointF end;
    DIRECTION direction;
    void judgeMousePosition(QPointF pointF);
    void sendItemQRectF();

};

#endif // MYITEM_H
