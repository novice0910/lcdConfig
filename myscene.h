#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QDebug>
#include <QObject>
#include <QList>
#include <QSettings>
#include "data.h"
#include "MyWidget.h"

typedef QList<QGraphicsItem*> ITEM_LIST;
typedef QList<BtnWidget*> BTN_ITEM_LIST;
class myScene :public QGraphicsScene
{
    Q_OBJECT
public:
    myScene(QObject *parent = 0);
    void setItemType(ITEM_TYPE type);
    void setScenePageIndex(int index);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
    void clearAllItemSelected();//when this scene is not show clear item select status
public slots:
    void slotBtnRectQRectF(QRectF rect);//get item rect QRectF from myItem
    void slotGetBtnInfoChangedFromShow(BTN_INFO btn);//get btn info change From btn show
    void slotSelectRectChangedByShow(QRectF rect);//change the selected item QRectF
    void slotSaveAllItemOnScene(QString path);//when save all item infomation
    void slotOpenReadAllItemOnScene(QString path);//open project read all item
    void slotGetBtnInfoChangedFromMyWidget(BTN_INFO btn);
    void slotGetDeleteSelectedItemFromUI(PROPERETY_SHOW_INDEX index);
signals:
    void signalSendBtnItemQRectF(QRectF rect);//retransmission btn Item QRectF to btn
    void signalItemHasInserted(myItem *item);
    void signalSendBtnInfoToBtnShow(BTN_INFO *btn);
    void signalSendWhichItemHasSelected(PROPERETY_SHOW_INDEX);//set index of propertyShow index
private:
    int m_page;// which page this scene belongs to ?
    ITEM_LIST itemList;
    BTN_ITEM_LIST btnItemList;
    ITEM_TYPE m_ItemType;
    QGraphicsPathItem * dashRect;
    myItem *m_selectedItem;
    BTN_INFO readBtnInfo();
};

#endif // MYSCENE_H
