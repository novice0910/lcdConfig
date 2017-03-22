#ifndef MYWIDGET_H
#define MYWIDGET_H
#include "myitem.h"
#include "data.h"

class BtnWidget : public myItem
{
public:
    BtnWidget();
    BTN_INFO getInfo() const{
        return m_btnInfo;
    }
    ITEM_TYPE getItemType() const{
        return m_itemType;
    }
    void setInfo(BTN_INFO  btn)
    {
        m_btnInfo = btn;
    }
private:
    BTN_INFO m_btnInfo;
    ITEM_TYPE m_itemType;
};

#endif // MYWIDGET_H
