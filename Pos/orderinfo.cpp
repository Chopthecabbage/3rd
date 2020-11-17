#include "orderinfo.h"
#include "ui_orderinfo.h"
#include "signalinfo.h"
#include "totalorderinfo.h"

#include <QDebug>
#include <QHostAddress>
#include <QMessageBox>


orderInfo::orderInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::orderInfo)
{
    ui->setupUi(this);

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



void orderInfo::set_orderInfo(int orderNum)
{
    SignalInfo info ;

    int tot_order_price = 0;
    int cnt ;
    TotalOrderInfo *tot_order_info = nullptr;

    info.set_signal(2);
    info.set_order_num(orderNum);

    this->order_num = orderNum;

    _socket->waitForBytesWritten(1000);

    // 주문정보를 서버에 요청하다.
    _socket->write((char*)(&info),sizeof(info));

    _socket->waitForReadyRead(2000);
    // 출력할 주문정보 개수를 받는다.
    _socket->read((char*)&cnt,sizeof(int));
    // 주문메뉴개수만큼 동적할당하다.

    if(tot_order_info != nullptr)
    {
        delete [] tot_order_info;
    }

    tot_order_info = new TotalOrderInfo[cnt];

    _socket->waitForReadyRead(2000);

    // 응답받은 주문정보(클래스배열)를 서버로부터 받다.
    _socket->read((char*)(tot_order_info),cnt*sizeof(TotalOrderInfo));

    // 주문메뉴정보를 테이블뷰에 출력한다.
    // Row 를 추가한다.
    for(int i=0; i<cnt; i++)
    {
        ui->order_tableview->insertRow(ui->order_tableview->rowCount());
        int index = ui->order_tableview->rowCount() - 1;
        ui->order_tableview->setItem(index,0,new QTableWidgetItem(QString::number(i+1)));
        ui->order_tableview->setItem(index,1,new QTableWidgetItem(tot_order_info[i].get_menu_name()));
        ui->order_tableview->setItem(index,2,new QTableWidgetItem(QString::number(tot_order_info[i].get_menu_price())));
        ui->order_tableview->setItem(index,3,new QTableWidgetItem(QString::number(tot_order_info[i].get_amount())));
        ui->order_tableview->setItem(index,4,new QTableWidgetItem(QString::number(tot_order_info[i].get_tot_menu_price())));
        tot_order_price += tot_order_info[i].get_tot_menu_price();
        index++;
    }

    // 총주문금액을 표시한다.
    ui->tot_price_label->setText(QString::number(tot_order_price));
}

void orderInfo::recv_orderNum(int orderNum,QTcpSocket *socket)
{
    _socket = socket;
    set_orderInfo(orderNum);
}

// 닫기
void orderInfo::on_order_closeBtn_clicked()
{
    this->close();
}

// 주문취소
void orderInfo::on_order_cancelBtn_clicked()
{
    QMessageBox msgBox;
    int result;
    int signal ;
    signal = 4;
    // 해당 주문건취소 시그널을 보낸다.
    _socket->write((char*)(&signal),sizeof(int));
    _socket->waitForBytesWritten(1000);
    // 취소할 주문번호를 전달한다.
    _socket->write((char*)(&order_num),sizeof(int));
    _socket->waitForReadyRead(2000);
    // 처리 결과를 확인한다.
    _socket->read((char*)(&result),sizeof(int));

    if(result == 0) // 취소성공
    {
        QMessageBox::information(this,"Sucess!","취소처리 되었습니다!");
    }
    else if(result != 0) // 취소실패
    {
        QMessageBox::information(this,"Warning!","취소실패 하였습니다!");
    }
    this->close();
}


// 주문처리
void orderInfo::on_order_completeBtn_clicked()
{
    QMessageBox msgBox;
    int result;
    int signal ;
    signal = 3;
    // 해당 주문건취소 시그널을 보낸다.
    _socket->write((char*)(&signal),sizeof(int));
    _socket->waitForBytesWritten(1000);
    // 취소할 주문번호를 전달한다.
    _socket->write((char*)(&order_num),sizeof(int));
    _socket->waitForReadyRead(2000);
    // 처리 결과를 확인한다.
    _socket->read((char*)(&result),sizeof(int));

    if(result == 0) // 취소성공
    {
        QMessageBox::information(this,"Sucess!","처리 되었습니다!");
    }
    else if(result != 0) // 취소실패
    {
        QMessageBox::information(this,"Warning!","처리실패 하였습니다!");
    }
    this->close();
}
