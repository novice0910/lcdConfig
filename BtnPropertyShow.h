#ifndef BTNPROPERTYSHOW_H
#define BTNPROPERTYSHOW_H

#include <QWidget>
#include <QLabel>
#include <QSpinBox>
#include <QLayout>
#include <QGroupBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QDebug>
#include "data.h"
class BtnPropertyShow : public QWidget
{
    Q_OBJECT
public:
    explicit BtnPropertyShow(QWidget *parent = 0);
    void widgetInit();
    void connectInit();
signals:
    void signalSendBtnInfo(BTN_INFO *btn_info);
    void signalSendBtnRectChanged(QRectF rect);//send the select btn item has changed to scene
public slots:
    void slotGetBtnItemQRectF(QRectF rect);
    void slotGetBtnInfoFromScene(BTN_INFO *btnInfo);
private slots:
    void slotBtnXChanged(int x);
    void slotBtnYChanged(int y);
    void slotBtnWChanged(int w);
    void slotBtnHChanged(int h);
private:
    QSpinBox *btn_x;
    QSpinBox *btn_y;
    QSpinBox *btn_w;
    QSpinBox *btn_h;

    QLineEdit * lEditkeyNum;
    QSpinBox *sBoxNextPage;
    QRadioButton *rBtninputByByte;
    QRadioButton *rBtninputByBit;
    QRadioButton *rBtninputByHighByte;
    QRadioButton *rBtninputByLowByte;
    BTN_INFO *m_btnInfo;
};

#endif // BTNPROPERTYSHOW_H
