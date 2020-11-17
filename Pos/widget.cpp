#include "widget.h"
#include "ui_widget.h"
#include "signalinfo.h"
#include "totalorderinfo.h"

#include <QDebug>
#include <QHostAddress>
#include <QMessageBox>

#define PORT 7878

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , _socket(nullptr)
{
    ui->setupUi(this);   
    QStringList tableHeader;
    tableHeader << "날짜" << "주문번호" << "대표메뉴" << "품목수" << "주문총액" << "결제수단";
    // 테이블뷰 칼럼개수를 정하다.
    ui->order_table->setColumnCount(6);
    // 칼럼명을 적는다.
    ui->order_table->setHorizontalHeaderLabels(tableHeader);
    // 칼럼간격을 설정하다.
    ui->order_table->setColumnWidth(0,80);
    ui->order_table->setColumnWidth(1,60);
    ui->order_table->setColumnWidth(2,110);
    ui->order_table->setColumnWidth(3,50);
    ui->order_table->setColumnWidth(4,60);
    ui->order_table->setColumnWidth(4,70);

    //==================[ 오더 소켓 ]=====================================
    int type = 3;
    order_socket.connectToHost(QHostAddress("10.10.20.240"), PORT);
    connect(&order_socket,SIGNAL(readyRead()), this, SLOT(Print_all_orderinfo()));
    order_socket.write((char*)&type, sizeof(int));
    //===================================================================

    //==================[ 메인 소켓 ]=====================================
    _socket.connectToHost(QHostAddress("10.10.20.240"), PORT);
    type = 2;
    _socket.write((char*)&type, sizeof(int));
    //===================================================================

}

Widget::~Widget()
{
    delete ui;
}

// 주문번호가 존재하는지 확인한다.
void Widget::search_orderInfo(int order_num)
{
    QMessageBox msgBox;
    QByteArray recv_msg ;
    SignalInfo info ;

    // 시그널 정보를 설정하다.
    info.set_signal(1);
    info.set_order_num(order_num);

    // 주문번호 존재유무 및 주문처리상태를 확인한다.
    _socket.write((char*)(&info),sizeof(info));

    // _socket.waitForBytesWritten(1000);
    _socket.waitForReadyRead(2000);

    // 확인결과를 읽는다.
    recv_msg = _socket.readAll();

    // 확인결과에 따른 처리를 한다.

    if(recv_msg == "0" || recv_msg == "2")
    {
        QMessageBox::information(this,"Warning","이미 처리된 주문입니다.");
    }
    else if(recv_msg == "1")
    {
        msgBox.setText("주문상세정보를 보시겠습니까?");
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Ok);
        if(msgBox.exec() == QMessageBox::Ok)
        {
            // 새 다이얼로그창에 조회한 주문번호를 전달한다.
            orderInfo_dialog = new orderInfo(this);
            connect(this,SIGNAL(send_orderNum(int,QTcpSocket*)),orderInfo_dialog,SLOT(recv_orderNum(int,QTcpSocket*)));
            emit send_orderNum(order_num,&_socket);
            orderInfo_dialog->exec();
        }
    }
    else if(recv_msg == "-1")
    {
        QMessageBox::information(this,"Warning","존재하지 않는 주문입니다.");
    }
}

void Widget::Print_all_orderinfo()
{
    TotalOrderInfo *tot_order_info = nullptr;
    int print_cnt;
    // 모든 주문건 조회시그널을 전달하다.

    order_socket.waitForReadyRead(2000);

    // 출력할 총주문개수를 받는다.
    order_socket.read((char*)&print_cnt,sizeof(int));

    qDebug() << "print_cnt :" << print_cnt ;

    // 주문메뉴개수만큼 동적할당하다.
    if(tot_order_info != nullptr)
    {
        delete [] tot_order_info;
    }
    tot_order_info = new TotalOrderInfo[print_cnt];

    // 응답받은 주문정보(클래스배열)를 서버로부터 받다.
    order_socket.waitForReadyRead(2000);
    order_socket.read((char*)(tot_order_info),print_cnt*sizeof(TotalOrderInfo));

    // 테이블뷰를 비우다
    ui->order_table->setRowCount(0);

    // 총 주문정보를 출력한다.
    for(int i=0; i<print_cnt; i++)
    {
        ui->order_table->insertRow(ui->order_table->rowCount());
        int index = ui->order_table->rowCount() - 1;
        ui->order_table->setItem(index,0,new QTableWidgetItem(tot_order_info[i].get_order_date()));
        ui->order_table->setItem(index,1,new QTableWidgetItem(QString::number(tot_order_info[i].get_order_num())));
        ui->order_table->setItem(index,2,new QTableWidgetItem(tot_order_info[i].get_menu_name()));
        ui->order_table->setItem(index,3,new QTableWidgetItem(QString::number(tot_order_info[i].get_amount())));
        ui->order_table->setItem(index,4,new QTableWidgetItem(QString::number(tot_order_info[i].get_tot_order_price())));
        int payment = tot_order_info[i].get_payment();
        if(payment == 2)
            ui->order_table->setItem(index,5,new QTableWidgetItem("현금"));
        else
            ui->order_table->setItem(index,5,new QTableWidgetItem("카드"));
        index++;
    }
}

void Widget::on_order_searchBtn_clicked()
{
    SignalInfo info;
    int order_num = ui->order_numEdit->text().toInt();

    // 주문정보 조회요청
    search_orderInfo(order_num);

    // 택스트 지우기
    ui->order_numEdit->clear();

    // 전체 주문들을 테이블뷰에 갱신하다.
    info.set_signal(5);
    _socket.write((char*)(&info),sizeof(info));
}

void Widget::on_exitBtn_clicked()
{
    this->close();
}

void Widget::on_settleBtn_clicked()
{
    // 남은주문이 있으면 정산하면 안됨
    QMessageBox::information(this,"Sucess","정산완료!");
    SignalInfo info ;
    info.set_signal(5);
    _socket.write((char*)(&info),sizeof(info));
}

void Widget::on_today_salesBtn_clicked()
{
    QMessageBox msgBox;

    // 다이얼로그 창 띄우기
    msgBox.setText("당일 매출정보를 보시겠습니까?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    if(msgBox.exec() == QMessageBox::Ok)
    {
        // 새 다이얼로그창에 소켓정보를 전달한다.
        todaySales_dialog = new TodaySales(this);
        connect(this,SIGNAL(send_socket(QTcpSocket*)),todaySales_dialog,SLOT(recv_socket(QTcpSocket*)));
        emit send_socket(&_socket);
        todaySales_dialog->exec();
    }
    // 매장전체주문목록 출력을 갱신하다.
    SignalInfo info ;
    info.set_signal(5);
    _socket.write((char*)(&info),sizeof(info));
}

