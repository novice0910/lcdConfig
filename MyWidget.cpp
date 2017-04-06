#include "MyWidget.h"

BtnWidget::BtnWidget()
{
    setBrushColor(Qt::yellow);
    setItemType(BTN);
    setToolTip("btn");
}

void BtnWidget::saveItemInfo(QString path,int num)
{
    QSettings *conf = new QSettings(path,QSettings::IniFormat);
    conf->setValue(tr("btn/btn%1Name").arg(num + 1),tr("btn%1").arg(num + 1));
    conf->setValue(tr("btn/btn%1X").arg(num + 1),m_btnInfo.x);
    conf->setValue(tr("btn/btn%1Y").arg(num + 1),m_btnInfo.y);
    conf->setValue(tr("btn/btn%1W").arg(num + 1),m_btnInfo.w);
    conf->setValue(tr("btn/btn%1H").arg(num + 1),m_btnInfo.h);
    conf->setValue(tr("btn/btn%1Image").arg(num + 1),m_btnInfo.image);
    conf->setValue(tr("btn/btn%1RegesitData").arg(num + 1),m_btnInfo.regesitData);
    conf->setValue(tr("btn/btn%1DataStartAddr").arg(num + 1),m_btnInfo.dataStartAddr);
    conf->setValue(tr("btn/btn%1DataType").arg(num + 1),m_btnInfo.dataType);
    conf->setValue(tr("btn/btn%1DataData").arg(num + 1),m_btnInfo.dataData);
    delete conf;
}

void BtnWidget::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    sendItemQRectF();
    QGraphicsItem::mouseMoveEvent(event);
}

QVariant BtnWidget::itemChange(GraphicsItemChange change,
                     const QVariant &value)
{
    Q_UNUSED(change);
    sendItemQRectF();
    return value;
}

void BtnWidget::sendItemQRectF()
{
    if(this->isSelected())
    {

        QRectF rectF;
        rectF.setX(this->scenePos().x());
        rectF.setY(this->scenePos().y());
        rectF.setWidth(m_width);
        rectF.setHeight(m_height);
        emit signalSendItemQRectF(rectF);
    }
}

LabelWidget::LabelWidget()
{
    setBrushColor(QColor(128,255,255));
    setItemType(LABEL);
    setToolTip("data display");
}

