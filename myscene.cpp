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
    m_selectedItem = 0;
    if (mouseEvent->button() != Qt::LeftButton)
        return;
    switch (m_ItemType) {
    case BTN:
    {
        BTN_INFO btn;
        m_ItemType = MOVE_ITEM;
        BtnWidget *item = new BtnWidget;
        this->addItem(item);
        item->setPos(mouseEvent->scenePos());
        item->setProperty(btn);
    }
        break;
    case LABEL:
    {
        m_ItemType = MOVE_ITEM;
        LabelWidget *item = new LabelWidget;
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
                getItemInfo(m_selectedItem);
            }
        }
    }
        break;
    default:
        break;
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
    m_ItemType = type;
}

void myScene::getItemInfo(myItem *item)
{
    if(item ==0) return;
    qDebug()<<"item type"<<item->getItemType();
    switch (item->getItemType()) {
    case BTN:
    {
        BtnWidget *btnItem = qgraphicsitem_cast<BtnWidget *>(item);
        BTN_INFO btn = btnItem->getInfo();
        emit signalSendBtnInfoToUI(&btn);
    }
        break;
    default:
        break;
    }
}
