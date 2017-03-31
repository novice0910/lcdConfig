#ifndef COMSET_H
#define COMSET_H

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QLayout>
#include <QLabel>
#include <QSettings>
#include <QMessageBox>

class ComSet : public QDialog
{
    Q_OBJECT
public:
    explicit ComSet(QDialog *parent = 0);
    void setSavePath(QString path);
signals:

public slots:
private:
    QString m_savePath;
    QComboBox *cBoxBaud;
    QComboBox * cBoxPort;

private slots:
    void slotOnSaveClicked();
};

#endif // COMSET_H
