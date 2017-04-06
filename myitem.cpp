#include "myitem.h"

myItem::myItem(qreal width, qreal height)
{
    m_width=width;
    m_height=height;
    setAcceptDrops(true);
    setAcceptHoverEvents(true);
    setFlags(ItemIgnoresTransformations|ItemIsSelectable | ItemIsFocusable);
    setZValue(0);
    setOpacity(0.5);
    m_cursor=new QCursor;
    direction = NONE;
    m_isSelected = false;
}

QRectF myItem::boundingRect()const{
    return QRectF(0,0,m_width,m_height);
    //每个item都有自己的一个坐标系，
//这个设置相当于把item相对于自身的坐标系的原点（0,0）放到自己的正中央。
}

QPainterPath myItem::shape()const{
    QPainterPath path;
    path.addRect(QRectF(0,0,m_width,m_height));
    return path;
}

void myItem::setBrushColor(QColor color)
{
    m_brushColor = color;
}

void myItem::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget){
    Q_UNUSED(widget);
    if (option->state & this->isSelected())
    {
        QPen pen;
        pen.setColor(Qt::black);
        pen.setWidth(2);
        pen.setStyle(Qt::DashDotLine);
        painter->setBrush(m_brushColor);
        painter->setPen(pen);
        painter->drawRect(QRectF(0,0,m_width,m_height));
    }
    else
    {
            QPen pen;
            pen.setColor(Qt::black);
            pen.setWidth(2);
            painter->setBrush(m_brushColor);
            painter->setPen(pen);
            painter->drawRect(QRectF(0,0,m_width,m_height));
    }
}

QVariant myItem::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    Q_UNUSED(change);
    sendItemQRectF();
    return value;
}

void myItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        if(m_cursor->shape() == Qt::ArrowCursor)
        {
            m_cursor->setShape(Qt::SizeAllCursor);
            this->setCursor(*m_cursor);
            update();
            direction = MOVE;
            start = event->scenePos();
        }
        else{
            start=event->scenePos();
        }
    }
    update();
    QGraphicsItem::mousePressEvent(event);
}

void myItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    sendItemQRectF();
    QPointF dis;
    end=event->scenePos();
    dis=end-start;
    start=end;
    switch (direction) {
    case TOP://top
    {
        if(end.y()>=0)
        {
            m_height = m_height - dis.y();
            update(boundingRect());
            this->moveBy(0,dis.y());
        }
    }
        break;
    case BOTTOM:
    {
        if(end.y() <= SIZE_HIGHT)
        {
            m_height = m_height + dis.y();
            update(boundingRect());
            prepareGeometryChange();
            this->moveBy(0,0);
        }
    }
        break;
    case LEFT:
    {
        if(end.x() >= 0)
        {
            m_width = m_width - dis.x();
            update(boundingRect());
            prepareGeometryChange();
            this->moveBy(dis.x(),0);
        }
    }
        break;
    case RIGHT:
    {
        if(end.x() <= SIZE_WIDTH)
        {
            m_width = m_width + dis.x();
            update(boundingRect());
            prepareGeometryChange();
            this->moveBy(0,0);
        }
    }
        break;
    case LEFT_TOP:
    {
        if(end.x()>=0 && end.y() >= 0)
        {
            m_width = m_width - dis.x();
            m_height = m_height - dis.y();
            this->moveBy(dis.x(),dis.y());
        }
        else if(end.x() >= 0 && end.y() <= 0)
        {
            m_width = m_width - dis.x();
            m_height = m_height;
            this->moveBy(dis.x(),0);
        }
        else if(end.x() <= 0 && end.y() >= 0)
        {
            m_width = m_width;
            m_height = m_height - dis.y();
            this->moveBy(0,dis.y());
        }
        update(boundingRect());
        prepareGeometryChange();
    }
        break;
    case LEFT_BOTTOM:
    {
        if(end.x() >= 0 && end.y() <= SIZE_HIGHT)
        {
            m_width = m_width - dis.x();
            m_height = m_height + dis.y();
            this->moveBy(dis.x(),0);
        }
        else if(end.x() <= 0 && end.y() <= SIZE_HIGHT)
        {
            m_width = m_width;
            m_height = m_height + dis.y();
            this->moveBy(0,0);
        }
        else if(end.x() >= 0 && end.y() >= SIZE_HIGHT)
        {
            m_width = m_width - dis.x();
            m_height = m_height;
            this->moveBy(dis.x(),0);
        }
        update(boundingRect());
        prepareGeometryChange();
    }
        break;
    case RIGHT_TOP:
    {
        if(end.x() <= SIZE_WIDTH && end.y() >= 0)
        {
            m_width = m_width + dis.x();
            m_height = m_height - dis.y();
            this->moveBy(0,dis.y());
        }
        else if(end.x() >= SIZE_WIDTH && end.y() >= 0)
        {
            m_height = m_height - dis.y();
            m_width = m_width;
            this->moveBy(0,dis.y());
        }
        else if(end.x() <= SIZE_WIDTH && end.y() <= 0)
        {
            m_height = m_height;
            m_width = m_width + dis.x();
            this->moveBy(0,0);
        }
        update(boundingRect());
        prepareGeometryChange();
    }
        break;
    case RIGHT_BOTTOM:
    {
        if(end.x() <= SIZE_WIDTH && end.y() <= SIZE_HIGHT)
        {
            m_width = m_width + dis.x();
            m_height = m_height + dis.y();
            this->moveBy(0,0);
        }
        else if(end.x() >= SIZE_WIDTH && end.y() <= SIZE_HIGHT)
        {
            m_height = m_height + dis.y();
            m_width = m_width;
            this->moveBy(0,0);
        }
        else if(end.x() <= SIZE_WIDTH && end.y() >= SIZE_HIGHT)
        {
            m_height = m_height;
            m_width = m_width + dis.x();
            this->moveBy(0,0);
        }
        update(boundingRect());
        prepareGeometryChange();
    }
        break;
    case MOVE:
    {
        QPointF leftTop,rightTop,leftBottom,rightBottom;
        leftTop = this->scenePos();
        rightTop = QPointF(leftTop.x() + m_width,leftTop.x());
        leftBottom = QPointF(leftTop.x(),leftTop.y() + m_height);
        rightBottom = QPointF(leftTop.x() + m_width,leftTop.y() + m_height);
        if(leftTop.x() >=0 && leftTop.y()>=0 &&
           leftBottom.x() >= 0 && leftBottom.y() <= SIZE_HIGHT &&
           rightTop.x() <= SIZE_WIDTH && rightTop.y() >= 0 &&
           rightBottom.x() <= SIZE_WIDTH && rightBottom.y() <= SIZE_HIGHT)
        {
            this->moveBy(dis.x(),dis.y());
            update(boundingRect());
            prepareGeometryChange();
        }
    }
        break;
    default:
        break;
    }
    QGraphicsItem::mouseMoveEvent(event);
}

void myItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    direction = NONE;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}

void myItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    judgeMousePosition(event->scenePos());
    QGraphicsItem::hoverEnterEvent(event);
}

void myItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    judgeMousePosition(event->scenePos());
    QGraphicsItem::hoverLeaveEvent(event);
}

void myItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    judgeMousePosition(event->scenePos());
    QGraphicsItem::hoverMoveEvent(event);
}

void myItem::sendItemQRectF()
{
    if(this->isSelected())
    {

        QRectF rectF;
        rectF.setX(this->scenePos().x());
        rectF.setY(this->scenePos().y());
        rectF.setWidth(m_width);
        rectF.setHeight(m_height);
        emit signalSendItemQRectF(rectF);
    }
}

void myItem::changeRect(QRectF rect)
{
    if(this->isSelected())
    {
        m_width = rect.width();
        m_height = rect.height();
        update(boundingRect());
        prepareGeometryChange();
        this->setPos(rect.x(),rect.y());
    }
}


void myItem::judgeMousePosition(QPointF pointF)
{
    if(!this->isSelected())
    {
        direction = NONE;
        m_cursor->setShape(Qt::ArrowCursor);
        this->setCursor(*m_cursor);
        return;
    }
    QPointF mousePos = pointF;
    QPointF leftTop = QPointF(this->scenePos().x(),this->scenePos().y());
    QPointF leftBottom = QPointF(this->scenePos().x(),this->scenePos().y()+m_height);
    QPointF rightTop = QPointF(this->scenePos().x()+m_width,this->scenePos().y());
    QPointF rightBottom = QPointF(this->scenePos().x()+m_width,this->scenePos().y()+m_height);
    if((mousePos.x()>= leftTop.x() + VERTEX_DIS) &&
            (mousePos.x() <= rightTop.x() - VERTEX_DIS)
            && (mousePos.y() <= leftTop.y() + VERTEX_DIS)
            && (mousePos.y() >= leftTop.y() -VERTEX_DIS))//top
    {
        m_cursor->setShape(Qt::SizeVerCursor);
        direction = TOP;
    }
    else if((mousePos.x() >= leftBottom.x() + VERTEX_DIS) &&
            (mousePos.x() <= rightTop.x()- VERTEX_DIS) &&
            (mousePos.y() >= leftBottom.y() - VERTEX_DIS) &&
            (mousePos.y() <= leftBottom.y() + VERTEX_DIS))//buttom
    {
        m_cursor->setShape(Qt::SizeVerCursor);
        direction = BOTTOM;
    }
    else if((mousePos.y()>= leftTop.y() + VERTEX_DIS) &&
            (mousePos.y() <= leftBottom.y() - VERTEX_DIS)
            && (mousePos.x() <= leftTop.x() + VERTEX_DIS)
            && (mousePos.x() >= leftTop.x() -VERTEX_DIS))//left
    {
      m_cursor->setShape(Qt::SizeHorCursor);
      direction = LEFT;
    }
    else if((mousePos.y()>= rightTop.y() + VERTEX_DIS) &&
            (mousePos.y() <= rightBottom.y() - VERTEX_DIS)
            && (mousePos.x() <= rightTop.x() + VERTEX_DIS)
            && (mousePos.x() >= rightTop.x() -VERTEX_DIS))//right
    {
        m_cursor->setShape(Qt::SizeHorCursor);
        direction = RIGHT;
    }
    else if((mousePos.x() <= leftTop.x() + VERTEX_DIS)&&
            (mousePos.x() >= leftTop.x() - VERTEX_DIS)&&
            (mousePos.y() <= leftTop.y() + VERTEX_DIS)&&
            (mousePos.y() >= leftTop.y() - VERTEX_DIS))//left top
    {
        m_cursor->setShape(Qt::SizeFDiagCursor);
        direction = LEFT_TOP;
    }
    else if((mousePos.x() <= leftBottom.x() + VERTEX_DIS)&&
             (mousePos.x() >= leftBottom.x() - VERTEX_DIS)&&
             (mousePos.y() <= leftBottom.y() + VERTEX_DIS)&&
             (mousePos.y() >= leftBottom.y() - VERTEX_DIS))//left bottom
    {
         m_cursor->setShape(Qt::SizeBDiagCursor);
         direction = LEFT_BOTTOM;
    }
    else if((mousePos.x() <= rightTop.x() + VERTEX_DIS)&&
            (mousePos.x() >= rightTop.x() - VERTEX_DIS)&&
            (mousePos.y() <= rightTop.y() + VERTEX_DIS)&&
            (mousePos.y() >= rightTop.y() - VERTEX_DIS))//right top
    {
        m_cursor->setShape(Qt::SizeBDiagCursor);
        direction = RIGHT_TOP;
    }
    else if((mousePos.x() <= rightBottom.x() + VERTEX_DIS)&&
             (mousePos.x() >= rightBottom.x() - VERTEX_DIS)&&
             (mousePos.y() <= rightBottom.y() + VERTEX_DIS)&&
             (mousePos.y() >= rightBottom.y() - VERTEX_DIS))//right bottom
    {
         m_cursor->setShape(Qt::SizeFDiagCursor);
         direction = RIGHT_BOTTOM;
    }
    else
    {
        direction = NONE;
        m_cursor->setShape(Qt::ArrowCursor);
    }
    this->setCursor(*m_cursor);
}
