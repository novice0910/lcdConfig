#ifndef MYITEM_H
#define MYITEM_H

#include <QGraphicsPolygonItem>
#include <QBrush>

enum itemType { BTN,LABEL,MSG ,INPUT_BTN,RTC};

class myItem :public QGraphicsPolygonItem
{
public:
    enum { Type = UserType + 15 };

    myItem(itemType type);

private:
    itemType m_type;

};

#endif // MYITEM_H
