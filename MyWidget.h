#ifndef MYWIDGET_H
#define MYWIDGET_H
#include <QString>
#include <QObject>
#include "myitem.h"
#include "data.h"

class BtnWidget : public myItem
{
public:
    BtnWidget();
    BTN_INFO getInfo() {

        m_btnInfo.x = this->scenePos().x();
        m_btnInfo.y = this->scenePos().y();
        m_btnInfo.w = this->m_width;
        m_btnInfo.h = this->m_height;

        return m_btnInfo;
    }
    void setProperty(BTN_INFO  btn)//set except QPointF
    {
        m_btnInfo = btn;
        m_btnInfo.x = this->scenePos().x();
        m_btnInfo.y = this->scenePos().y();
        m_btnInfo.w = this->m_width;
        m_btnInfo.h = this->m_height;
    }
    BTN_INFO m_btnInfo;

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
