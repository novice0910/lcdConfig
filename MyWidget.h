#ifndef MYWIDGET_H
#define MYWIDGET_H
#include <QString>
#include <QObject>
#include <QDebug>
#include "myitem.h"
#include "data.h"
#include <QSettings>
#include <QGraphicsSceneMouseEvent>
class BtnWidget : public myItem
{
    Q_OBJECT
public:
    BtnWidget();

    BTN_INFO m_btnInfo;
    void setProperty(BTN_INFO  btn);
    void setInitProperty(QPointF pointf);
    void saveItemInfo(QString path, int num);//save the item in the path  btn?=btn(num)
    void sendItemSpecialProperty();
signals:
    void signalSendItemInfoToScene(BTN_INFO info);//only emit when it has been selected

private:

};

class LabelWidget : public myItem
{
public:
    LabelWidget();

    void setProperty(LAB_INFO  btn)
    {
        m_btnInfo = btn;
    }
private:
    LAB_INFO m_btnInfo;
};
#endif // MYWIDGET_H
