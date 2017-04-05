#ifndef MYWIDGET_H
#define MYWIDGET_H
#include <QString>
#include <QObject>
#include <QDebug>
#include "myitem.h"
#include "data.h"
#include <QSettings>

class BtnWidget : public myItem
{
public:
    BtnWidget();

    BTN_INFO m_btnInfo;

    BTN_INFO getInfo() {

        m_btnInfo.x = this->scenePos().x();
        m_btnInfo.y = this->scenePos().y();
        m_btnInfo.w = this->m_width;
        m_btnInfo.h = this->m_height;

        return m_btnInfo;
    }
    void setProperty(BTN_INFO  btn)
    {
        m_btnInfo = btn;
    }
    void saveItemInfo(QString path, int num);//save the item in the path  btn?=btn(num)
private:
};

class LabelWidget : public myItem
{
public:
    LabelWidget();
    LAB_INFO getInfo() const{
        return m_btnInfo;
    }
    void setProperty(LAB_INFO  btn)
    {
        m_btnInfo = btn;
    }
private:
    LAB_INFO m_btnInfo;
};
#endif // MYWIDGET_H
