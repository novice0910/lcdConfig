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
#include <QButtonGroup>
#include "data.h"
class BtnPropertyShow : public QWidget
{
    Q_OBJECT
public:
    explicit BtnPropertyShow(QWidget *parent = 0);
    void widgetInit();
    void connectInit();
signals:
    void signalSendBtnRectChanged(QRectF rect);//send the select btn item has changed to scene
    void signalSendBtnInfoToScene(BTN_INFO *btn_info);//send the show btn information to scene's item

public slots:
    void slotGetBtnItemQRectF(QRectF rect);//get item QRectF from scene because of item has changed
    void slotGetBtnInfoFromScene(BTN_INFO *btnInfo);//show the btn information when it has selected

private slots:
    void slotBtnXChanged(int x);
    void slotBtnYChanged(int y);
    void slotBtnWChanged(int w);
    void slotBtnHChanged(int h);
    void slotRBtnClicked();
private:
    //
    BTN_INFO *m_btnInfo;

    //widget
    QSpinBox *btn_x;
    QSpinBox *btn_y;
    QSpinBox *btn_w;
    QSpinBox *btn_h;
    QLineEdit * lEditkeyNum;//
    QLineEdit *lEditAddr;
    QSpinBox *sBoxNextPage;
    QButtonGroup *btnGroup;
    QRadioButton *rBtninputByByte;
    QRadioButton *rBtninputByBit;
    QRadioButton *rBtninputByHighByte;
    QRadioButton *rBtninputByLowByte;
    QRectF readRectF();
    void getAndSendRectF();
    BTN_INFO readBtnInfo();
    void getAndSendBtnInfo();
};

#endif // BTNPROPERTYSHOW_H
