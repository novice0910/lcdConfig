#include "myitem.h"

myItem::myItem(itemType type)
{
    m_type = type;
    setOpacity(0.4);
    switch (m_type) {
    case BTN:
        setBrush(QBrush(Qt::yellow));
        break;
    case LABEL:
        setBrush(QBrush(Qt::blue));
        break;
    case MSG:
        setBrush(QBrush(Qt::gray));
        break;
    case INPUT_BTN:
        setBrush(QBrush(Qt::yellow));
        break;
    case RTC:
        setBrush(QBrush(Qt::white));
        break;
    default:
        break;
    }
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

