#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>

#include "orderinfo.h"
#include "todaysales.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void search_orderInfo(int order_num);    
signals:
    void send_orderNum(int order_num,QTcpSocket *socket);
    void send_socket(QTcpSocket *socket);

private slots:
    void on_order_searchBtn_clicked();
    void on_exitBtn_clicked();
    void on_settleBtn_clicked();
    void on_today_salesBtn_clicked();
    void Print_all_orderinfo();
private:
    Ui::Widget *ui;
    QTcpSocket _socket; // 메인소켓
    QTcpSocket order_socket; // 주문만 처리하는 소켓
    orderInfo *orderInfo_dialog;
    TodaySales *todaySales_dialog;
};
#endif // WIDGET_H
