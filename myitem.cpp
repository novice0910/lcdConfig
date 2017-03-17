#include "myitem.h"

myItem::myItem(itemType type)
{
    m_type = type;
    setOpacity(0.4);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    setPen(pen);
    switch (m_type) {
    case BTN:
        setBrush(QBrush(Qt::yellow));
        break;
    case LABEL:
        setBrush(QBrush(Qt::blue));
        break;
    case MSG:
        setBrush(QBrush(Qt::gray));
        break;
    case INPUT_BTN:
        setBrush(QBrush(Qt::yellow));
        break;
    case RTC:
        setBrush(QBrush(Qt::white));
        break;
    default:
        break;
    }
    myPolygon << QPointF(-50, -25) << QPointF(50, -25)
              << QPointF(50, 25) << QPointF(-50, 25)
              << QPointF(-50, -25);
    m_rect = QRectF(0,0,100,50);
    setRect(0,0,100,50);
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    setZValue(0);
    setAcceptDrops(true);
    setAcceptsHoverEvents(true);
    cScale=false;
    m_cursor=new QCursor;
    direction=0;
}

void myItem::ResetRect(QRectF rect){
    m_rect=rect;
    update(boundingRect());
}

QRectF myItem::boundingRect()const
{
    return QRectF(m_rect.x()-2,m_rect.y()-2,m_rect.width()+4,m_rect.height()+4);
}

QPainterPath myItem::shape()const{
    QPainterPath path;
    path.addRect(m_rect);
    return path;
}

void myItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    setBrush(QBrush(Qt::yellow));
    painter->setBrush(Qt::yellow);
    painter->setPen(pen);
    painter->drawRect(m_rect);
}

void myItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
//    qDebug()<<"hover enter event"<<direction;
    QPointF pos1=event->scenePos();
    QPointF lt=this->scenePos()+QPointF(m_rect.x(),m_rect.y());
    QPointF lb=this->scenePos()+QPointF(m_rect.x(),m_rect.y()+m_rect.height());
    QPointF rt=this->scenePos()+QPointF(m_rect.x()+m_rect.width(),m_rect.y());
    QPointF rb=this->scenePos()+QPointF(m_rect.x()+m_rect.width(),m_rect.y()+m_rect.height());
    if((pos1.x()<=lt.x()+2&&pos1.y()<=lt.y()+2)
     ||(pos1.x()>=rb.x()-2&&pos1.y()>=rb.y()-2))
    {
        usleep(5);
        if((pos1.x()<=lt.x()+2&&pos1.y()<=lt.y()+2)
         ||(pos1.x()>=rb.x()-2&&pos1.y()>=rb.y()-2))
        {
            m_cursor->setShape(Qt::SizeFDiagCursor);
            if(pos1.x()<=lt.x()+2)direction=8;
            else direction=4;

        }
    }
    else if((pos1.x()<=lb.x()+2&&pos1.y()>=lb.y()-2)
             ||(pos1.x()>=rt.x()-2&&pos1.y()<=rt.y()+2))
    {
        usleep(5);
        if((pos1.x()<=lb.x()+2&&pos1.y()>=lb.y()-2)
                ||(pos1.x()>=rt.x()-2&&pos1.y()<=rt.y()+2))
        {
            m_cursor->setShape(Qt::SizeBDiagCursor);
            if(pos1.x()<=lb.x()+2)direction=6;
            else direction=2;
        }
    }
    else if((pos1.x()<=lt.x()+2||pos1.x()>=rt.x()-2)
             &&(pos1.y()<=lb.y()&&pos1.y()>=lt.y()))
    {
        usleep(5);
        if((pos1.x()<=lt.x()+2||pos1.x()>=rt.x()-2)
                     &&(pos1.y()<=lb.y()&&pos1.y()>=lt.y()))
        {
            m_cursor->setShape(Qt::SizeHorCursor);
            if(pos1.x()<=lt.x()+2)direction=7;
            else direction=3;
        }
    }
    else if((pos1.y()<=lt.y()+2||pos1.y()>=lb.y()-2)
             &&(pos1.x()>=lt.x()&&pos1.x()<=rt.x()))
    {
        usleep(5);
        if((pos1.y()<=lt.y()+2||pos1.y()>=lb.y()-2)
                     &&(pos1.x()>=lt.x()&&pos1.x()<=rt.x()))
        {
            m_cursor->setShape(Qt::SizeVerCursor);
            if(pos1.y()<=lt.y()+2)direction=1;
            else direction=5;
        }
    }
    else
    {
        direction =0;
        cScale=false;
        m_cursor->setShape(Qt::ArrowCursor);
    }
    this->setCursor(*m_cursor);
    update();
    QGraphicsItem::hoverEnterEvent(event);
}
void myItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
//    qDebug()<<"move event"<<direction;
    QPointF pos1=event->scenePos();
    QPointF lt=this->scenePos()+QPointF(m_rect.x(),m_rect.y());
    QPointF lb=this->scenePos()+QPointF(m_rect.x(),m_rect.y()+m_rect.height());
    QPointF rt=this->scenePos()+QPointF(m_rect.x()+m_rect.width(),m_rect.y());
    QPointF rb=this->scenePos()+QPointF(m_rect.x()+m_rect.width(),m_rect.y()+m_rect.height());
    if((pos1.x()<=lt.x()+2&&pos1.y()<=lt.y()+2)
     ||(pos1.x()>=rb.x()-2&&pos1.y()>=rb.y()-2))
    {
        usleep(5);
        if((pos1.x()<=lt.x()+2&&pos1.y()<=lt.y()+2)
         ||(pos1.x()>=rb.x()-2&&pos1.y()>=rb.y()-2))
        {
            m_cursor->setShape(Qt::SizeFDiagCursor);
            if(pos1.x()<=lt.x()+2)direction=8;
            else direction=4;

        }
    }
    else if((pos1.x()<=lb.x()+2&&pos1.y()>=lb.y()-2)
             ||(pos1.x()>=rt.x()-2&&pos1.y()<=rt.y()+2))
    {
        usleep(5);
        if((pos1.x()<=lb.x()+2&&pos1.y()>=lb.y()-2)
                ||(pos1.x()>=rt.x()-2&&pos1.y()<=rt.y()+2))
        {
            m_cursor->setShape(Qt::SizeBDiagCursor);
            if(pos1.x()<=lb.x()+2)direction=6;
            else direction=2;
        }
    }
    else if((pos1.x()<=lt.x()+2||pos1.x()>=rt.x()-2)
             &&(pos1.y()<=lb.y()&&pos1.y()>=lt.y()))
    {
        usleep(5);
        if((pos1.x()<=lt.x()+2||pos1.x()>=rt.x()-2)
                     &&(pos1.y()<=lb.y()&&pos1.y()>=lt.y()))
        {
            m_cursor->setShape(Qt::SizeHorCursor);
            if(pos1.x()<=lt.x()+2)direction=7;
            else direction=3;
        }
    }
    else if((pos1.y()<=lt.y()+2||pos1.y()>=lb.y()-2)
             &&(pos1.x()>=lt.x()&&pos1.x()<=rt.x()))
    {
        usleep(5);
        if((pos1.y()<=lt.y()+2||pos1.y()>=lb.y()-2)
                     &&(pos1.x()>=lt.x()&&pos1.x()<=rt.x()))
        {
            m_cursor->setShape(Qt::SizeVerCursor);
            if(pos1.y()<=lt.y()+2)direction=1;
            else direction=5;
        }
    }
    else
    {
        cScale=false;
        direction = 0;
        m_cursor->setShape(Qt::ArrowCursor);
    }
    this->setCursor(*m_cursor);
    update();
    QGraphicsItem::hoverMoveEvent(event);
}
void myItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
//    qDebug()<<"hover leave event"<<direction;
    direction = 0;
    m_cursor->setShape(Qt::ArrowCursor);
    cScale=false;
    this->setCursor(*m_cursor);
    update();
    QGraphicsItem::hoverLeaveEvent(event);
}
void myItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug()<<"Scale"<<cScale<<direction;
    if(event->button()==Qt::LeftButton){
        start=event->scenePos();
        cScale=true;
    }
    update();
    QGraphicsItem::mousePressEvent(event);
}
void myItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    int t=0;
    t++;
    t--;
    if(cScale){
        QPointF dis;
        end=event->scenePos();
        dis=end-start;
        start=end;
        switch(direction){
            case 1:
            {
                QRectF tem=QRectF(m_rect.x(),m_rect.y()+dis.y()/2,m_rect.width(),m_rect.height()-dis.y());
                this->ResetRect(tem);
                update(boundingRect());
                this->moveBy(0,dis.y()/2);
                break;
            }
            case 2:
            {
                QRectF tem=QRectF(m_rect.x()+dis.x()/2,m_rect.y()+dis.y()/2,
                                  m_rect.width()+dis.x(),m_rect.height()-dis.y());
                this->ResetRect(tem);
                update(boundingRect());
                this->moveBy(-dis.x()/2,-dis.y()/2);
                break;
            }
            case 3:
            {
                QRectF tem=QRectF(m_rect.x()+dis.x()/2,m_rect.y(),m_rect.width()+dis.x(),m_rect.height());
                this->ResetRect(tem);
                update(boundingRect());
                this->moveBy(-dis.x()/2,0);
                break;
            }
            case 4:
            {
                QRectF tem=QRectF(m_rect.x()+dis.x()/2,m_rect.y()+dis.y()/2,
                                  m_rect.width()+dis.x(),m_rect.height()+dis.y());
                this->ResetRect(tem);
                update(boundingRect());
                this->moveBy(-dis.x()/2,-dis.y()/2);
                break;
            }
            case 5:
            {
                QRectF tem=QRectF(m_rect.x(),m_rect.y()+dis.y()/2,m_rect.width(),m_rect.height()+dis.y());
                this->ResetRect(tem);
                update(boundingRect());
                this->moveBy(0,-dis.y()/2);
                break;
            }
            case 6:
            {
                QRectF tem=QRectF(m_rect.x()+dis.x()/2,m_rect.y()+dis.y()/2,
                                  m_rect.width()-dis.x(),m_rect.height()+dis.y());
                this->ResetRect(tem);
                update(boundingRect());
                this->moveBy(-dis.x()/2,-dis.y()/2);
                break;
            }
            case 7:
            {
                QRectF tem=QRectF(m_rect.x()+dis.x()/2,m_rect.y(),m_rect.width()-dis.x(),m_rect.height());
                this->ResetRect(tem);
                update(boundingRect());
                this->moveBy(dis.x()/2,0);
                break;
            }
            case 8:
            {
                QRectF tem=QRectF(m_rect.x()+dis.x()/2,m_rect.y()+dis.y()/2,
                                  m_rect.width()-dis.x(),m_rect.height()-dis.y());
                this->ResetRect(tem);
                update(boundingRect());
                this->moveBy(dis.x()/2,dis.y()/2);
                break;
            }
        }
    }
    update();
    QGraphicsItem::mouseMoveEvent(event);
}

void myItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    cScale=false;
    direction = 0;
    qDebug()<<"release event"<<cScale<<direction;
    update();
    QGraphicsItem::mouseReleaseEvent(event);
}
