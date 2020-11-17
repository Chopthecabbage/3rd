#ifndef PAYDIALOG_H
#define PAYDIALOG_H

#include <QDialog>
#include <QRadioButton>
#include <QGroupBox>
#include <QPushButton>
#include <QBoxLayout>
#include <QString>

#include "orders.h"

namespace Ui {
class PayDialog;
}
//
class QTcpSocket;

class PayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PayDialog(QWidget *parent = nullptr);
    ~PayDialog();

private:
    Ui::PayDialog *ui;
    Orders temp;

    QRadioButton *payRADIO_1[2];
    QPushButton *payRADIO_2[2];
    QGroupBox *box;
    QHBoxLayout *hlayout;

    int decision;
    //
    QTcpSocket *socket;
private slots:
    void recvCLASS(Orders orders);
    void sign();
    void withdraw();

signals:
    void sendINT(int decision);
    void sendOR(Orders temp);
};

#endif // PAYDIALOG_H
