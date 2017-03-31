#ifndef MYSCENE_H
#define MYSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QColor>
#include <QDebug>
#include <QObject>
#include <QList>
#include "data.h"
#include "MyWidget.h"

typedef QList<QGraphicsItem*> ITEM_LIST;
typedef QList<BtnWidget*> BTN_ITEM_LIST;
class myScene :public QGraphicsScene
{
    Q_OBJECT
public:
    myScene(int page, QObject *parent = 0);
    void setItemType(ITEM_TYPE type);
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
public slots:
    void slotBtnRectQRectF(QRectF rect);//get item rect QRectF from myItem
    void slotGetBtnInfoChanged(BTN_INFO btn);
    void slotSelectRectChanged(QRectF rect);//change the selected item QRectF
    void slotSaveAllItemOnScene();
signals:
    void signalSendBtnItemQRectF(QRectF rect);//retransmission btn Item QRectF to btn
    void signalItemHasInserted(myItem *item);
    void signalSendBtnInfoToUI(BTN_INFO *);
    void signalSendWhichItemHasSelected(PROPERETY_SHOW_INDEX);//set index of propertyShow index

private:
    int m_page;// which page this scene belongs to ?
    ITEM_LIST itemList;
    BTN_ITEM_LIST btnItemList;
    ITEM_TYPE m_ItemType;
    QGraphicsPathItem * dashRect;
    myItem *m_selectedItem;
    void getItemInfo(myItem *item);
};

#endif // MYSCENE_H
