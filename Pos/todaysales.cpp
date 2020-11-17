#include "todaysales.h"
#include "ui_todaysales.h"
#include "signalinfo.h"
#include "totalorderinfo.h"

TodaySales::TodaySales(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TodaySales)
{
    ui->setupUi(this);

    QStringList tableHeader;
    tableHeader << "주문번호" << "대표메뉴명" << "품목수" << "주문총액" << "결제수단" <<"주문결과";
    // 테이블뷰 칼럼개수를 정하다.
    ui->t_sales_info_table->setColumnCount(6);
    // 칼럼명을 적는다.
    ui->t_sales_info_table->setHorizontalHeaderLabels(tableHeader);
    // 칼럼간격을 설정하다.
    ui->t_sales_info_table->setColumnWidth(0,60);
    ui->t_sales_info_table->setColumnWidth(1,125);
    ui->t_sales_info_table->setColumnWidth(2,60);
    ui->t_sales_info_table->setColumnWidth(3,80);
    ui->t_sales_info_table->setColumnWidth(4,70);
    ui->t_sales_info_table->setColumnWidth(5,70);
}

TodaySales::~TodaySales()
{
    delete ui;
}

void TodaySales::Print_Today_SalesInfo()
{
    SignalInfo info ;

    int tot_order_cnt = 0 ; // 총 주문건수
    int tot_sales_cnt = 0; // 총 판매건수
    int tot_cancel_sales_cnt =0 ; // 총 취소건수

    int tot_sales = 0; // 총 매출
    int tot_cs_sales = 0; // 총 현금매출
    int tot_cd_sales = 0; // 총 카드매출

    int print_cnt ;

    TotalOrderInfo *tot_order_info = nullptr;

    info.set_signal(6);

    _socket->waitForBytesWritten(1000);

    // 당일매출정보를 서버에 요청하다.
    _socket->write((char*)(&info),sizeof(info));

    _socket->waitForReadyRead(2000);
    // 출력할 매출정보 개수를 받는다.
    _socket->read((char*)&print_cnt,sizeof(int));

    tot_order_cnt = print_cnt;

    qDebug() << "print_cnt :" << tot_order_cnt ;

    // 매출정보 개수만큼 동적할당하다.
    if(tot_order_info != nullptr)
    {
        delete [] tot_order_info;
    }

    tot_order_info = new TotalOrderInfo[tot_order_cnt];

    _socket->waitForReadyRead(2000);

    // 응답받은 주문정보(클래스배열)를 서버로부터 받다.
    _socket->read((char*)(tot_order_info),print_cnt*sizeof(TotalOrderInfo));

    // 주문메뉴정보를 테이블뷰에 출력한다.
    // Row 를 추가한다.
    for(int i=0; i<print_cnt; i++)
    {
        ui->t_sales_info_table->insertRow(ui->t_sales_info_table->rowCount());
        int index = ui->t_sales_info_table->rowCount() - 1;
        ui->t_sales_info_table->setItem(index,0,new QTableWidgetItem(QString::number(tot_order_info[i].get_order_num()))); // 주문번호
        ui->t_sales_info_table->setItem(index,1,new QTableWidgetItem(tot_order_info[i].get_menu_name())); // 대표메뉴
        ui->t_sales_info_table->setItem(index,2,new QTableWidgetItem(QString::number(tot_order_info[i].get_amount()))); // 품목수
        int tot_order_price = tot_order_info[i].get_tot_order_price();
        ui->t_sales_info_table->setItem(index,3,new QTableWidgetItem(QString::number(tot_order_price))); // 주문 총금액

        // 주문처리상태를 확인한다. --> 처리상태가 처리면 결제수단입력, 결제수단에 맞는 금액더하기 , 총매출금액 더하기
        int status = tot_order_info[i].get_status();
        int payment = tot_order_info[i].get_payment();
        // 주문처리상태에 따른 결제수단 및 매출액계산
        if(status == 0)
        {
            ui->t_sales_info_table->setItem(index,5,new QTableWidgetItem("처리완료"));
            // 결제수단
            if(payment == 2)
            {
                // 카드
                ui->t_sales_info_table->setItem(index,4,new QTableWidgetItem("카드"));
                tot_cd_sales+=tot_order_price; // 카드매출

            }
            else if(payment == 1)
            {
                // 현금
                ui->t_sales_info_table->setItem(index,4,new QTableWidgetItem("현금"));
                tot_cs_sales+=tot_order_price; // 현금매출
            }
            tot_sales+=tot_order_price; // 총매출
            tot_sales_cnt++; // 판매건수
        }

        else if(status == 2)
        {
            // 주문처리상태
            ui->t_sales_info_table->setItem(index,5,new QTableWidgetItem("취소완료"));
            // 결제수단
            ui->t_sales_info_table->setItem(index,4,new QTableWidgetItem("없음"));
            tot_cancel_sales_cnt++; // 취소건수
        }

        else
        {
            ui->t_sales_info_table->setItem(index,5,new QTableWidgetItem("처리중"));
            if(payment==1)
            {
                ui->t_sales_info_table->setItem(index,4,new QTableWidgetItem("카드"));
            }
            else if(payment==2)
            {
                ui->t_sales_info_table->setItem(index,4,new QTableWidgetItem("현금"));
            }
        }

        index++;
    }

    // 주문건수,결제수단별 매출을 등록하다.
    ui->tot_order_cnt_label->setText(QString::number(tot_order_cnt));
    ui->t_sales_cnt_label->setText(QString::number(tot_sales_cnt));
    ui->t_cancel_cnt_label->setText(QString::number(tot_cancel_sales_cnt));

    ui->t_tot_sales_label->setText(QString::number(tot_sales));
    ui->t_card_sales_label->setText(QString::number(tot_cs_sales));
    ui->t_cash_sales_label->setText(QString::number(tot_cd_sales));

    ui->not_sales_label->setText(QString::number(tot_order_cnt-tot_sales_cnt-tot_cancel_sales_cnt));

    delete [] tot_order_info;
}

void TodaySales::recv_socket(QTcpSocket *socket)
{
    _socket = socket;
    // 당일매출정보를 보여주다.
    Print_Today_SalesInfo();
}

void TodaySales::on_checkBtn_clicked()
{
    this->close();
}
