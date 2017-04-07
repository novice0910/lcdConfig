#include "BtnPropertyShow.h"

BtnPropertyShow::BtnPropertyShow(QWidget *parent) :
    QWidget(parent)
{
    widgetInit();
    connectInit();
}

void BtnPropertyShow::widgetInit()
{
    QGroupBox *coordinate = new QGroupBox(this);
    coordinate->setObjectName(QString::fromUtf8("groupBox_3"));
    coordinate->setGeometry(QRect(6, 12, 193, 98));
    coordinate->setTitle(tr("坐标"));
    QWidget *gridLayoutWidget = new QWidget(this);
    gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
    gridLayoutWidget->setGeometry(QRect(11, 19, 171, 80));
    QGridLayout *gridLayout = new QGridLayout(gridLayoutWidget);
    gridLayout->setSpacing(6);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);
    QLabel *label = new QLabel(gridLayoutWidget);
    label->setObjectName(QString::fromUtf8("label"));
    label->setAlignment(Qt::AlignCenter);
    label->setText("x");
    gridLayout->addWidget(label, 0, 0, 1, 1);

    btn_x = new QSpinBox(gridLayoutWidget);
    btn_x->setObjectName(QString::fromUtf8("btn_x"));
    btn_x->setRange(0,MAX_X_SIZE);
    btn_x->setValue(0);
    gridLayout->addWidget(btn_x, 0, 1, 1, 1);

    btn_w = new QSpinBox(gridLayoutWidget);
    btn_w->setObjectName(QString::fromUtf8("btn_w"));
    btn_w->setRange(0,MAX_W_SIZE);
    btn_w->setValue(0);
    gridLayout->addWidget(btn_w, 1, 1, 1, 1);

    QLabel *label_3 = new QLabel(gridLayoutWidget);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setAlignment(Qt::AlignCenter);
    label_3->setText("w");
    gridLayout->addWidget(label_3, 1, 0, 1, 1);

    btn_y = new QSpinBox(gridLayoutWidget);
    btn_y->setObjectName(QString::fromUtf8("btn_y"));
    btn_y->setRange(0,MAX_Y_SIZE);
    btn_y->setValue(0);
    gridLayout->addWidget(btn_y, 0, 3, 1, 1);

    QLabel *label_2 = new QLabel(gridLayoutWidget);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setAlignment(Qt::AlignCenter);
    label_2->setText("y");
    gridLayout->addWidget(label_2, 0, 2, 1, 1);

    QLabel *label_4 = new QLabel(gridLayoutWidget);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setAlignment(Qt::AlignCenter);
    label_4->setText("h");
    gridLayout->addWidget(label_4, 1, 2, 1, 1);

    btn_h = new QSpinBox(gridLayoutWidget);
    btn_h->setObjectName(QString::fromUtf8("btn_h"));
    btn_h->setRange(0,MAX_H_SIZE);
    btn_h->setValue(0);
    gridLayout->addWidget(btn_h, 1, 3, 1, 1);

    QGroupBox *gBoxPageSwitch = new QGroupBox(this);
    gBoxPageSwitch->setObjectName(QString::fromUtf8("gBoxPageSwitch"));
    gBoxPageSwitch->setGeometry(QRect(17, 139, 178, 80));
    gBoxPageSwitch->setTitle(tr("页面切换"));
    QLabel *lab = new QLabel;
    lab->setText(tr("目标页面"));
    QHBoxLayout *hLayoutNextPage = new QHBoxLayout;
    gBoxPageSwitch->setLayout(hLayoutNextPage);
    hLayoutNextPage->addWidget(lab);
    sBoxNextPage = new QSpinBox;
    sBoxNextPage->setMinimum(-1);
    sBoxNextPage->setValue(-1);
    hLayoutNextPage->addWidget(sBoxNextPage);

    QGroupBox * gBoxkeyNum = new QGroupBox(this);
    gBoxkeyNum->setObjectName(QString::fromUtf8("gBoxkeyNum"));
    gBoxkeyNum->setGeometry(QRect(20, 233, 171, 80));
    gBoxkeyNum->setTitle(tr("键值(0x)"));
    QLabel *label_5 = new QLabel(gBoxkeyNum);
    label_5->setObjectName(QString::fromUtf8("keyNum"));
    label_5->setGeometry(QRect(15, 29, 21, 35));
    label_5->setAlignment(Qt::AlignCenter);
    label_5->setText(tr("0x"));
    lEditkeyNum = new QLineEdit(gBoxkeyNum);
    lEditkeyNum->setObjectName(QString::fromUtf8("lineEdit"));
    lEditkeyNum->setGeometry(QRect(50, 34, 69, 26));
    lEditkeyNum->setText("0000");

    QGroupBox * gBoxAddr = new QGroupBox(this);
    gBoxAddr->setObjectName(QString::fromUtf8("gBoxAddr"));
    gBoxAddr->setGeometry(QRect(10, 320, 197, 131));
    QLabel *labAddr = new QLabel(gBoxAddr);
    labAddr->setObjectName(QString::fromUtf8("labAddr"));
    labAddr->setGeometry(QRect(4, 7, 100, 23));
    labAddr->setAlignment(Qt::AlignCenter);
    labAddr->setText(tr("变量地址(0x)"));


    lEditAddr = new QLineEdit(gBoxAddr);
    lEditAddr->setObjectName(QString::fromUtf8("lineEdit_2"));
    lEditAddr->setGeometry(QRect(110, 6, 50, 30));
    lEditAddr->setText("0000");
    rBtninputByByte = new QRadioButton(gBoxAddr);
    rBtninputByByte->setObjectName(QString::fromUtf8("RBinputByByte"));
    rBtninputByByte->setGeometry(QRect(6, 42, 102, 31));
    rBtninputByByte->setText(tr("按字节写入"));
    rBtninputByBit = new QRadioButton(gBoxAddr);
    rBtninputByBit->setObjectName(QString::fromUtf8("RBinputByBit"));
    rBtninputByBit->setGeometry(QRect(0, 75, 76, 31));
    rBtninputByBit->setText(tr("位控制"));
    rBtninputByHighByte = new QRadioButton(gBoxAddr);
    rBtninputByHighByte->setObjectName(QString::fromUtf8("inputByHighByte"));
    rBtninputByHighByte->setGeometry(QRect(13, 100, 101, 31));
    rBtninputByHighByte->setText(tr("按高字节写入"));
    rBtninputByLowByte = new QRadioButton(gBoxAddr);
    rBtninputByLowByte->setObjectName(QString::fromUtf8("inputByLowByte"));
    rBtninputByLowByte->setGeometry(QRect(76, 64, 103, 31));
    rBtninputByLowByte->setText(tr("按低字节写入"));

    QGridLayout *gLayout = new QGridLayout;
    gBoxAddr->setLayout(gLayout);
    gLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gLayout->setContentsMargins(0, 0, 0, 0);
    gLayout->addWidget(labAddr,0,0,1,1);
    gLayout->addWidget(lEditAddr,0,1,1,1);

    btnGroup = new QButtonGroup;
    btnGroup->addButton(rBtninputByByte,0);
    btnGroup->addButton(rBtninputByBit,1);
    btnGroup->addButton(rBtninputByHighByte,2);
    btnGroup->addButton(rBtninputByLowByte,3);
    gLayout->addWidget(rBtninputByByte,1,0,1,1);
    gLayout->addWidget(rBtninputByBit,1,1,1,1);
    gLayout->addWidget(rBtninputByHighByte,2,0,1,2);
    gLayout->addWidget(rBtninputByLowByte,3,0,1,2);
    rBtninputByByte->setChecked(true);
}
void BtnPropertyShow::connectInit()
{
    connect(btn_x,SIGNAL(valueChanged(int)),this,SLOT(slotSpinBoxChanged(int)));
    connect(btn_y,SIGNAL(valueChanged(int)),this,SLOT(slotSpinBoxChanged(int)));
    connect(btn_w,SIGNAL(valueChanged(int)),this,SLOT(slotSpinBoxChanged(int)));
    connect(btn_h,SIGNAL(valueChanged(int)),this,SLOT(slotSpinBoxChanged(int)));
    connect(sBoxNextPage,SIGNAL(valueChanged(int)),this,SLOT(slotSpinBoxChanged(int)));
    connect(rBtninputByByte,SIGNAL(clicked()),this,SLOT(slotRBtnClicked()));
    connect(rBtninputByBit,SIGNAL(clicked()),this,SLOT(slotRBtnClicked()));
    connect(rBtninputByHighByte,SIGNAL(clicked()),this,SLOT(slotRBtnClicked()));
    connect(rBtninputByLowByte,SIGNAL(clicked()),this,SLOT(slotRBtnClicked()));
    connect(lEditAddr,SIGNAL(textChanged(QString)),this,SLOT(slotLineEditChanged()));
    connect(lEditkeyNum,SIGNAL(textChanged(QString)),this,SLOT(slotLineEditChanged()));
}

void BtnPropertyShow::getAndSendRectF()
{
    QRectF rect;
    rect.setX(btn_x->value());
    rect.setY(btn_y->value());
    rect.setHeight(btn_h->value());
    rect.setWidth(btn_w->value());

    emit signalSendBtnRectChanged(rect);
}

void BtnPropertyShow::getAndSendBtnInfo()
{
    BTN_INFO info;

    info.x = btn_x->value();
    info.y = btn_y->value();
    info.w = btn_w->value();
    info.h = btn_h->value();
    info.regesitData = sBoxNextPage->value();
    info.dataStartAddr = lEditAddr->text().toInt(0,16);
    info.dataData = lEditkeyNum->text().toInt(0,16);
    info.dataType = btnGroup->checkedId();

    emit signalSendBtnInfoToScene(info);
}

void BtnPropertyShow::slotGetBtnItemQRectF(QRectF rect)
{
    btn_x->setValue(rect.x());
    btn_y->setValue(rect.y());
    btn_h->setValue(rect.height());
    btn_w->setValue(rect.width());
}

void BtnPropertyShow::slotGetBtnInfoFromScene(BTN_INFO * btnInfo)
{
    btn_x->setValue(btnInfo->x);
    btn_y->setValue(btnInfo->y);
    btn_h->setValue(btnInfo->h);
    btn_w->setValue(btnInfo->w);
    lEditAddr->setText(QString("%1").arg(btnInfo->dataStartAddr,4,16,QLatin1Char('0')));
    lEditkeyNum->setText(QString("%1").arg(btnInfo->dataData,4,16,QLatin1Char('0')));
    sBoxNextPage->setValue(btnInfo->regesitData);
    switch (btnInfo->dataType) {
    case BY_BYTE:
        rBtninputByByte->setChecked(true);
        break;
    case BY_BIT:
        rBtninputByBit->setChecked(true);
        break;
    case BY_MSB:
        rBtninputByHighByte->setChecked(true);
        break;
    case BY_LSB:
        rBtninputByLowByte->setChecked(true);
        break;
    default:
        break;
    }
}


void BtnPropertyShow::slotSpinBoxChanged(int value)
{
    Q_UNUSED(value);
    getAndSendRectF();
    getAndSendBtnInfo();
}

void BtnPropertyShow::slotRBtnClicked()
{
    getAndSendBtnInfo();
}

void BtnPropertyShow::slotLineEditChanged()
{
    getAndSendBtnInfo();
}
