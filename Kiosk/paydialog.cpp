#include "paydialog.h"
#include "ui_paydialog.h"

PayDialog::PayDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PayDialog)
{
    //QPixmap bg("/Users/iotpc/Desktop/TCP/POS/PHOTO/pay.png");
    //QPixmap bg("/Users/Ah-/Desktop/TCP/POS/PHOTO/pay.png");
    QPixmap bg(":/third/example/pay.png");
    QPalette p(palette());
    p.setBrush(QPalette::Background, bg);

    setAutoFillBackground(true);
    setPalette(p);

    ui->setupUi(this);
    setWindowTitle("You can’t have your cake and eat it too.");
    //
    box = new QGroupBox("결제수단",this);
    box->setGeometry(25,25,200,80);
    box->setStyleSheet("background-color: white; border: none; font-weight: bold");
    box->setFont(QFont("맑은 고딕",14));

    QString paySTR_1[2] = {"현금","카드"};
    int xpos=50;
    for(int i=0; i<2; i++)
    {
        payRADIO_1[i] = new QRadioButton(paySTR_1[i],this);
        payRADIO_1[i]->setGeometry(xpos,50,150,30);
        payRADIO_1[i]->setFont(QFont("맑은 고딕",10));
        xpos+=100;
    }
    payRADIO_1[0]->setStyleSheet("color: green; font-weight: normal");
    payRADIO_1[1]->setStyleSheet("color: blue; font-weight: normal");
    QString paySTR_2[2] = {"결제","뒤로"};
    int ypos=120;
    for(int i=0; i<2; i++)
    {
        payRADIO_2[i] = new QPushButton(paySTR_2[i],this);
        payRADIO_2[i]->setGeometry(280,ypos,100,30);
        payRADIO_2[i]->setFont(QFont("맑은 고딕",10));
        ypos+=30;
    }

    hlayout = new QHBoxLayout(box);
    hlayout->addWidget(payRADIO_1[0]);
    hlayout->addWidget(payRADIO_1[1]);

    connect(payRADIO_2[0],SIGNAL(clicked()),this,SLOT(sign()));
    connect(payRADIO_2[1],SIGNAL(clicked()),this,SLOT(withdraw()));
}

void PayDialog::recvCLASS(Orders orders)
{
    temp=orders;
    qDebug() << "복사된 값";
    for(int i=0; i<temp.Cart_Tot_Cnt(); i++)
    {
        temp.show(i);
    }
}

void PayDialog::sign()
{
    if(payRADIO_1[0]->isChecked()) // 현금
    {
        temp.Set_Payment_Info(1);
        connect(this,SIGNAL(sendOR(Orders)),this->parent(),SLOT(recvOR(Orders)));
        emit sendOR(temp);
        qDebug() <<"현금 전송";
        this->close();
    }
    else if(payRADIO_1[1]->isChecked())
    {
        temp.Set_Payment_Info(2);
        connect(this,SIGNAL(sendOR(Orders)),this->parent(),SLOT(recvOR(Orders)));
        emit sendOR(temp);
        qDebug() <<"카드 전송";
        this->close();
    }
    else
    {
        qDebug() << "결제수단";
        return;
    }
}

void PayDialog::withdraw()
{
    decision=1;
    connect(this,SIGNAL(sendINT(int)),this->parent(),SLOT(recvINT(int)));
    emit sendINT(decision);
    this->close();
}

PayDialog::~PayDialog()
{
    delete ui;
}
