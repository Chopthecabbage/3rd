#include "orderinfo.h"
#include "ui_orderinfo.h"
#include "signalinfo.h"
#include "totalorderinfo.h"

#include <QDebug>
#include <QHostAddress>

orderInfo::orderInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::orderInfo)
{
    ui->setupUi(this);

    _socket.connectToHost(QHostAddress("10.10.20.240"),8001);

    QStringList tableHeader;
    tableHeader << "번호" << "메뉴명" << "가격" << "수량" << "주문금액";
    // 테이블뷰 칼럼개수를 정하다.
    ui->order_tableview->setColumnCount(5);
    // 칼럼명을 적는다.
    ui->order_tableview->setHorizontalHeaderLabels(tableHeader);
    // 칼럼간격을 설정하다.
    ui->order_tableview->setColumnWidth(0,50);
    ui->order_tableview->setColumnWidth(1,125);
    ui->order_tableview->setColumnWidth(2,90);
    ui->order_tableview->setColumnWidth(3,80);
    ui->order_tableview->setColumnWidth(4,100);
}

orderInfo::~orderInfo()
{
    delete ui;
}

void orderInfo::on_pushButton_clicked()
{

}

void orderInfo::on_pushButton_2_clicked()
{

}

void orderInfo::on_pushButton_3_clicked()
{

}

void orderInfo::set_orderInfo(int orderNum)
{
    SignalInfo info ;
    TotalOrderInfo tot_order_info ;
    int cnt ;

    info.set_signal(2);
    info.set_order_num(orderNum);

    _socket.waitForBytesWritten(1000);

    // 주문정보를 서버에 요청하다.
    _socket.write((char*)(&info),sizeof(info));

    _socket.waitForReadyRead(3000);
    _socket.read((char*)&cnt,sizeof(int));
    qDebug() << "cnt :" << cnt;
    //tot_order_info `= new TotalOrderInfo[cnt];

    _socket.waitForReadyRead(2000);

    // 응답받은 주문정보(클래스배열)를 테이블뷰에 출력하다.
    _socket.read((char*)(&tot_order_info),sizeof(TotalOrderInfo));

    qDebug() << "size class :" << sizeof(TotalOrderInfo);
    qDebug() << "size class2 :" << sizeof(tot_order_info);

    qDebug() << "name :" << tot_order_info.get_menu_name();
    qDebug() << "amount :" <<tot_order_info.get_amount();
    qDebug() << "price :" <<tot_order_info.get_menu_price();
    qDebug() << "tot :" << tot_order_info.get_tot_menu_price();

    //qDebug() << "menu name :" <<tot_order_info.get_menu_name();
//    for(int i=0; i<tot_order_info[0].get_print_cnt(); i++)
//    {
//        qDebug() << i+1 << "번" ;
//        qDebug() << tot_order_info[i].get_menu_name() ;
//        qDebug() << tot_order_info[i].get_menu_price() ;
//        qDebug() << tot_order_info[i].get_amount();
//        qDebug() << tot_order_info[i].get_tot_menu_price();
//    }
    //delete [] tot_order_info;
}

void orderInfo::recv_orderNum(int orderNum)
{
    set_orderInfo(orderNum);
}
