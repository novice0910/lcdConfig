#include "myscene.h"

myScene::myScene(QObject *parent)
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

void myScene::setItemType(ITEM_TYPE type)
{
    m_ItemType = type;
}
void myScene::setScenePageIndex(int index)
{
    m_page = index;
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

void myScene::slotGetBtnInfoChanged(BTN_INFO btn)
{
    BtnWidget *btnItem;
    foreach (btnItem , btnItemList) {
        if(btnItem->isSelected())
        {
            btnItem->setProperty(btn);
        }
    }
}

void myScene::slotSelectRectChanged(QRectF rect)
{
    if(m_selectedItem == 0)
    {
        return;
    }
    m_selectedItem->slotChangeRect(rect);
}

void myScene::slotSaveAllItemOnScene(QString path)
{
    QString savePath = path + tr("/page%1/").arg(m_page) + "config.ini";
    QSettings *conf = new QSettings(savePath,QSettings::IniFormat);
    if(!btnItemList.isEmpty())
    {
        conf->setValue("btn/btnSum",btnItemList.size());
        for(int i= 0;i<btnItemList.size();i++)
        {
            btnItemList.at(i)->saveItemInfo(savePath,i);
        }
    }


}
