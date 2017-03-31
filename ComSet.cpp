#include "ComSet.h"
#include <QDebug>
ComSet::ComSet(QDialog *parent) : QDialog(parent)
{
    this->setWindowTitle(tr("系统配置"));

    cBoxBaud = new QComboBox(this);
    QStringList listBaud;
    listBaud << "1200" << "2400" << "4800"<< "9600"
             << "19200" << "38400"<< "57600" << "115200";
    cBoxBaud->addItems(listBaud);

    cBoxPort = new QComboBox(this);
    QStringList listPort;
    listPort << "ttyS1" <<"ttyS2" <<"ttyS3" <<"ttyS4";
    cBoxPort->addItems(listPort);

    QPushButton * btnSave = new QPushButton(tr("保存"));
    connect(btnSave,SIGNAL(clicked()),this,SLOT(slotOnSaveClicked()));
    QPushButton * btnCancel = new QPushButton(tr("取消"));
    connect(btnCancel,SIGNAL(clicked()),this,SLOT(close()));

    QGridLayout *gridLayout = new QGridLayout(this);
    gridLayout->addWidget(new QLabel(tr("端口号")),0,0,1,1);
    gridLayout->addWidget(cBoxPort,0,1,1,1);
    gridLayout->addWidget(new QLabel(tr("波特率")),1,0,1,1);
    gridLayout->addWidget(cBoxBaud,1,1,1,1);
    gridLayout->addWidget(btnCancel,2,0,1,1);
    gridLayout->addWidget(btnSave,2,1,1,1);
    this->setLayout(gridLayout);
}

void ComSet::setSavePath(QString path)
{
    m_savePath = path;
    QSettings *conf = new QSettings(path,QSettings::IniFormat);
    QString port = conf->value("serial/dev").toString();
    QString baud = conf->value("serial/baud").toString();
    cBoxPort->setCurrentText(port);
    cBoxBaud->setCurrentText(baud);
    delete conf;
}

void ComSet::slotOnSaveClicked()
{
    QSettings *conf =new QSettings(m_savePath,QSettings::IniFormat);

    conf->setValue("serial/dev",cBoxPort->currentText());
    conf->setValue("serial/baud",cBoxBaud->currentText());
    delete conf;
    close();

}
