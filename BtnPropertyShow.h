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
signals:

public slots:
    void slotGetBtnInfoFromScene(BTN_INFO *btnInfo);
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

};

#endif // BTNPROPERTYSHOW_H
