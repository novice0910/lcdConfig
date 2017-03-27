#include "myscene.h"

myScene::myScene( QObject *parent)
    :QGraphicsScene(parent)
{
    m_ItemType = MOVE_ITEM;
    m_selectedItem = new myItem;
}

void myScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    m_selectedItem = 0;
    if (mouseEvent->button() != Qt::LeftButton)
        return;
    switch (m_ItemType) {
    case BTN:
    {
        BTN_INFO btn;
        m_ItemType = MOVE_ITEM;
        BtnWidget *item = new BtnWidget;
        m_selectedItem = item;
        btnItemList.append(item);
        this->addItem(item);
        item->setPos(mouseEvent->scenePos());
//        item->setProperty(btn);
//        getItemInfo(item);
        connect(item,SIGNAL(signalSendItemQRectF(QRectF)),this,SLOT(slotBtnRectQRectF(QRectF)));
    }
        break;
    case LABEL:
    {
        m_ItemType = MOVE_ITEM;
        LabelWidget *item = new LabelWidget;
        m_selectedItem = item;
        this->addItem(item);
        item->setPos(mouseEvent->scenePos());
    }
        break;
    case MOVE_ITEM:
    {
        QTransform transform;
        QGraphicsItem *item = itemAt(mouseEvent->scenePos(),transform);
        if(item)
        {
            m_selectedItem = qgraphicsitem_cast<myItem *>(item);
            ITEM_TYPE type = m_selectedItem->getItemType();
            switch (type){
            case BTN:
                emit signalSendWhichItemHasSelected(BTN_INDEX);
                break;
            case LABEL:
                emit signalSendWhichItemHasSelected(LABEL_INDEX);
                break;
            default:
                break;
            }
        }
        else
        {
            emit signalSendWhichItemHasSelected(MAIN_INDEX);
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
//    getItemInfo(m_selectedItem);
}

void myScene::setItemType(ITEM_TYPE type)
{
    m_ItemType = type;
}

void myScene::getItemInfo(myItem *item)
{
    if(item ==0) return;
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

void myScene::slotBtnRectQRectF(QRectF rect)
{
    emit signalSendBtnItemQRectF(rect);
}

void myScene::slotGetBtnInfoChanged(BTN_INFO *btn)
{
    if(m_selectedItem == 0) return;
    BtnWidget *btnItem = qgraphicsitem_cast<BtnWidget *>(m_selectedItem);
    btnItem->setProperty(*btn);
}

void myScene::slotSelectRectChanged(QRectF rect)
{
    if(m_selectedItem == 0)
    {
        return;
    }
    m_selectedItem->slotChangeRect(rect);
}
