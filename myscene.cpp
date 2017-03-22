#include "myscene.h"

myScene::myScene( QObject *parent)
    :QGraphicsScene(parent)
{
    m_ItemType = MOVE_ITEM;
    m_selectedItem = new myItem;
}

void myScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    qDebug()<<"mouse press event";
    if (mouseEvent->button() != Qt::LeftButton)
        return;
    switch (m_ItemType) {
    case BTN:
    {
        m_ItemType = MOVE_ITEM;
        BtnWidget *item = new BtnWidget;
        this->addItem(item);
        item->setPos(mouseEvent->scenePos());
    }
        break;
    case MOVE_ITEM:
    {
        itemList = selectedItems();
        foreach (QGraphicsItem *item, selectedItems()) {
            if(item->type() == myItem::Type)
            {
                m_selectedItem = qgraphicsitem_cast<myItem *>(item);
            }
        }
    }
        break;
    default:
        break;
    }
//    if(m_ItemType == MOVE_ITEM)
//    {
//        itemList = selectedItems();

//        foreach(QGraphicsItem *item,selectedItems())
//        {
//            if(item->type() == myItem::Type)
//            {
//                m_selectedItem = qgraphicsitem_cast<myItem *>(item);
//            }
//        }
//    }
//    else
//    {
//        myItem *item;
//        item = new myItem();
//        item->setBrushColor(Qt::white);
//        this->addItem(item);
//        item->setPos(mouseEvent->scenePos());
//        emit signalItemHasInserted(item);
//    }
    update();
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void myScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    getItemInfo(m_selectedItem);
}

void myScene::setItemType(ITEM_TYPE type)
{
    m_ItemType = type;
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
