#include "myscene.h"

myScene::myScene( QObject *parent)
    :QGraphicsScene(parent)
{
    widgetType = MOVE_ITEM;
    m_selectedItem = new myItem;
}

void myScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug()<<"mouse press event";
    if (mouseEvent->button() != Qt::LeftButton)
        return;
    if(widgetType == MOVE_ITEM)
    {
        itemList = selectedItems();

        foreach(QGraphicsItem *item,selectedItems())
        {
            if(item->type() == myItem::Type)
            {
                m_selectedItem = qgraphicsitem_cast<myItem *>(item);
//                qDebug()<<"select item type"<<m_selectedItem->getItemType();
                qDebug()<<"item pos x"<<item->scenePos().x();
            }
        }
    }
    else
    {
        myItem *item;
        item = new myItem();
        this->addItem(item);
        item->setPos(mouseEvent->scenePos());
        emit signalItemHasInserted(item);
    }
    update();
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void myScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    getItemInfo(m_selectedItem);
}

void myScene::setItemType(ITEM_TYPE type)
{
    widgetType = type;
}

void myScene::getItemInfo(myItem *item)
{
    BTN_INFO btn;
   btn.x = m_selectedItem->scenePos().x();
   btn.y = m_selectedItem->scenePos().y();
//   m_selectedItem->m_rect.width();
//   m_selectedItem->m_rect.height();
//    BTN_INFO btn =  item->getBtnInfo();
    emit signalSendBtnInfoToUI(&btn);
}
