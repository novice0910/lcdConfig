#include "MyWidget.h"

BtnWidget::BtnWidget()
{
    setBrushColor(Qt::yellow);
    setItemType(BTN);
    setToolTip("btn");
}

LabelWidget::LabelWidget()
{
    setBrushColor(QColor(128,255,255));
    setItemType(LABEL);
    setToolTip("data display");
}

