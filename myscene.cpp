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
        m_ItemType = MOVE_ITEM;
        BtnWidget *item = new BtnWidget;
        btnItemList.append(item);
        this->addItem(item);
        item->setPos(mouseEvent->scenePos());
        connect(item,SIGNAL(signalSendItemQRectF(QRectF)),this,SLOT(slotBtnRectQRectF(QRectF)));
        connect(item,SIGNAL(signalSendItemInfoToScene(BTN_INFO)),this,SLOT(slotGetBtnInfoChangedFromMyWidget(BTN_INFO)));
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

void myScene::slotBtnRectQRectF(QRectF rect)
{
    emit signalSendBtnItemQRectF(rect);
}

void myScene::slotGetBtnInfoChangedFromShow(BTN_INFO btn)
{
    BtnWidget *btnItem;
    foreach (btnItem , btnItemList) {
        if(btnItem->isSelected())
        {
            btnItem->setProperty(btn);
        }
    }
}

void myScene::slotSelectRectChangedByShow(QRectF rect)
{
    if(m_selectedItem == 0)
    {
        return;
    }
    m_selectedItem->changeRect(rect);
}

void myScene::slotGetBtnInfoChangedFromMyWidget(BTN_INFO btn)
{
    emit signalSendBtnInfoToBtnShow(&btn);
}

void myScene::slotOpenReadAllItemOnScene(QString path)
{
    QString openPath = path + tr("/page%1/").arg(m_page) + "config.ini";
    QSettings *conf = new QSettings(openPath,QSettings::IniFormat);
    btnItemList.clear();
    conf->beginGroup("btn");
    int sum = conf->value("btnSum").toInt();
    for(int row=0;row<sum;row++)
    {
        BTN_INFO btnInit;

        btnInit.page = conf->value("page",0).toInt();
        btnInit.ojName = conf->value(tr("btn%1Name").arg(QString::number(row+1)),1).toString();
        btnInit.x = conf->value(tr("btn%1X").arg(QString::number(row+1)),100).toInt();
        btnInit.y = conf->value(tr("btn%1Y").arg(QString::number(row+1)),100).toInt();
        btnInit.w = conf->value(tr("btn%1W").arg(QString::number(row+1)),100).toInt();
        btnInit.h = conf->value(tr("btn%1H").arg(QString::number(row+1)),100).toInt();
        btnInit.image = conf->value(tr("btn%1Image").arg(QString::number(row+1)),1).toString();
        btnInit.regesitData = conf->value(tr("btn%1RegesitData").arg(QString::number(row+1)),-1).toInt();
        btnInit.dataStartAddr = conf->value(tr("btn%1DataStartAddr").arg(QString::number(row+1)),-1).toInt();
        btnInit.dataType = conf->value(tr("btn%1DataType").arg(QString::number(row+1)),0).toInt();
        btnInit.dataData = conf->value(tr("btn%1DataData").arg(QString::number(row+1)),0).toInt();

        BtnWidget *item = new BtnWidget;
        item->setProperty(btnInit);
        btnItemList.append(item);
        this->addItem(item);
        item->setWidthAndHeight(btnInit.w,btnInit.h);
        item->setPos(btnInit.x,btnInit.y);
        connect(item,SIGNAL(signalSendItemQRectF(QRectF)),this,SLOT(slotBtnRectQRectF(QRectF)));
        connect(item,SIGNAL(signalSendItemInfoToScene(BTN_INFO)),this,SLOT(slotGetBtnInfoChangedFromMyWidget(BTN_INFO)));

    }
    conf->endGroup();
    delete conf;
}

void myScene::slotSaveAllItemOnScene(QString path)
{
    QString savePath = path + tr("/page%1/").arg(m_page) + "config.ini";
    QSettings *conf = new QSettings(savePath,QSettings::IniFormat);
    conf->setValue("PAGE/page",m_page);
    if(!btnItemList.isEmpty())
    {
        conf->setValue("btn/btnSum",btnItemList.size());
        for(int i= 0;i<btnItemList.size();i++)
        {
            btnItemList.at(i)->saveItemInfo(savePath,i);
        }
    }
}

void myScene::clearAllItemSelected()
{
    if(!btnItemList.isEmpty())
    {
        for(int i=0;i<btnItemList.size();i++)
        btnItemList.at(i)->setSelected(false);
    }
}
