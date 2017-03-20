#include "BtnPropertyShow.h"

BtnPropertyShow::BtnPropertyShow(QWidget *parent) :
    QWidget(parent)
{
    widgetInit();
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
//    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
    gridLayout->setContentsMargins(0, 0, 0, 0);
    QLabel *label = new QLabel(gridLayoutWidget);
    label->setObjectName(QString::fromUtf8("label"));
    label->setAlignment(Qt::AlignCenter);
    label->setText("x");
    gridLayout->addWidget(label, 0, 0, 1, 1);

    btn_x = new QSpinBox(gridLayoutWidget);
    btn_x->setObjectName(QString::fromUtf8("btn_x"));
    btn_x->setMaximum(800);
    gridLayout->addWidget(btn_x, 0, 1, 1, 1);

    btn_w = new QSpinBox(gridLayoutWidget);
    btn_w->setObjectName(QString::fromUtf8("btn_w"));
    btn_w->setMaximum(800);
    gridLayout->addWidget(btn_w, 1, 1, 1, 1);

    QLabel *label_3 = new QLabel(gridLayoutWidget);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setAlignment(Qt::AlignCenter);
    label_3->setText("w");
    gridLayout->addWidget(label_3, 1, 0, 1, 1);

    btn_y = new QSpinBox(gridLayoutWidget);
    btn_y->setObjectName(QString::fromUtf8("btn_y"));
    btn_y->setMaximum(480);
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
    btn_h->setMaximum(480);
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
    label_5->raise();
    lEditkeyNum->raise();

    QGroupBox * gBoxAddr = new QGroupBox(this);
    gBoxAddr->setObjectName(QString::fromUtf8("gBoxAddr"));
    gBoxAddr->setGeometry(QRect(10, 320, 197, 131));
    QLabel *labAddr = new QLabel(gBoxAddr);
    labAddr->setObjectName(QString::fromUtf8("labAddr"));
    labAddr->setGeometry(QRect(4, 7, 100, 23));
    labAddr->setAlignment(Qt::AlignCenter);
    labAddr->setText(tr("变量地址(0x)"));


    QLineEdit *lEditAddr = new QLineEdit(gBoxAddr);
    lEditAddr->setObjectName(QString::fromUtf8("lineEdit_2"));
    lEditAddr->setGeometry(QRect(110, 6, 50, 30));
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
    gLayout->addWidget(rBtninputByByte,1,0,1,1);
    gLayout->addWidget(rBtninputByBit,1,1,1,1);
    gLayout->addWidget(rBtninputByHighByte,2,0,1,2);
    gLayout->addWidget(rBtninputByLowByte,3,0,1,2);
}
