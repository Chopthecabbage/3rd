#ifndef ORDERINFO_H
#define ORDERINFO_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class orderInfo;
}

class orderInfo : public QDialog
{
    Q_OBJECT

public:
    explicit orderInfo(QWidget *parent = nullptr);
    ~orderInfo();
    void set_orderInfo(int orderNum);
private slots:

    void on_order_closeBtn_clicked();

    void on_order_cancelBtn_clicked();

    void on_order_completeBtn_clicked();

public slots:
    void recv_orderNum(int orderNum,QTcpSocket *socket);
private:
    Ui::orderInfo *ui;
    QTcpSocket *_socket;
    int order_num;
};

#endif // ORDERINFO_H
