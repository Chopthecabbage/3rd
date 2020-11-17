#include "dialog.h"
#include "ui_dialog.h"
#include <QTcpSocket>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    setWindowTitle("Walk on eggshells.");
    socket = new QTcpSocket(this);
    socket->connectToHost("10.10.20.240",7878); // 연결...

    // 1번 TAB 바로 출력
    socket->waitForBytesWritten();
    socket->write((char*)&type, sizeof(int));

    socket->waitForReadyRead(1000);
    socket->read((char*)&item, sizeof(Item)*21); // 메뉴 받기

    for(int i=0; i<21; i++)
    {
        item[i].show();
    }

    tab = new QTabWidget(this);
    //QWidget *iceTAB = new QWidget;
    iceTAB = new QWidget;
    hotTAB = new QWidget;
    beverageTAB = new QWidget;
    smoothieTAB = new QWidget;
    tab->setTabShape(QTabWidget::Triangular);
    tab->addTab(iceTAB,"COFFEE(ICE)");
    tab->addTab(hotTAB,"COFFEE(HOT)");
    tab->addTab(beverageTAB,"BEVERAGE");
    tab->addTab(smoothieTAB,"SMOOTHIE");

    tab->setGeometry(30,30,600,500);
    int xpos_1=25;
    int xpos_2=30;
    // 0번 탭...

    QString iceSTR[6]={item[0].GETname(),item[1].GETname(),item[2].GETname(),item[3].GETname(),item[4].GETname(),item[5].GETname()};
    QString pixICE[6]={item[0].GETphoto(),item[1].GETphoto(),item[2].GETphoto(),item[3].GETphoto(),item[4].GETphoto(),item[5].GETphoto()};

    for(int i=0; i<6; i++)
    {
        if(i==3)
        {
            xpos_1=25;
            xpos_2=30;
        }
        if(i<3)
        {
            iceLABEL[i]=new QLabel(iceTAB);
            icePIX[i]=QPixmap(pixICE[i]);
            iceLABEL[i]->setPixmap(icePIX[i]);
            iceLABEL[i]->setGeometry(xpos_1,50,150,150);
            iceLABEL[i]->setScaledContents( true );
            iceLABEL[i]->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
            xpos_1 += 200;

            iceRADIO[i]=new QRadioButton(iceSTR[i],iceTAB);
            iceRADIO[i]->setGeometry(xpos_2,200,150,30);
            xpos_2 += 200;
        }
        else
        {
            iceLABEL[i]=new QLabel(iceTAB);
            icePIX[i]=QPixmap(pixICE[i]);
            iceLABEL[i]->setPixmap(icePIX[i]);
            iceLABEL[i]->setGeometry(xpos_1,250,150,150);
            iceLABEL[i]->setScaledContents( true );
            iceLABEL[i]->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
            xpos_1 += 200;

            iceRADIO[i]=new QRadioButton(iceSTR[i],iceTAB);
            iceRADIO[i]->setGeometry(xpos_2,400,150,30);
            xpos_2 += 200;
        }
    }
    // 1번 탭...
    QString hotSTR[4]={item[6].GETname(),item[7].GETname(),item[8].GETname(),item[9].GETname()};
    QString pixHOT[4]={item[6].GETphoto(),item[7].GETphoto(),item[8].GETphoto(),item[9].GETphoto()};

    xpos_1=25;
    xpos_2=30;
    for(int i=0; i<4; i++)
    {
       if(i==3)
       {
           xpos_1=25;
           xpos_2=30;
       }
       if(i<3)
       {
           hotLABEL[i]=new QLabel(hotTAB);
           hotPIX[i]=QPixmap(pixHOT[i]);
           hotLABEL[i]->setPixmap(hotPIX[i]);
           hotLABEL[i]->setGeometry(xpos_1,50,150,150);
           hotLABEL[i]->setScaledContents( true );
           hotLABEL[i]->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
           xpos_1 += 200;

           hotRADIO[i]=new QRadioButton(hotSTR[i],hotTAB);
           hotRADIO[i]->setGeometry(xpos_2,200,150,30);
           xpos_2 += 200;
       }
       else
       {
           hotLABEL[i]=new QLabel(hotTAB);
           hotPIX[i]=QPixmap(pixHOT[i]);
           hotLABEL[i]->setPixmap(hotPIX[i]);
           hotLABEL[i]->setGeometry(xpos_1,250,150,150);
           hotLABEL[i]->setScaledContents( true );
           hotLABEL[i]->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
           xpos_1 += 200;

           hotRADIO[i]=new QRadioButton(hotSTR[i],hotTAB);
           hotRADIO[i]->setGeometry(xpos_2,400,150,30);
           xpos_2 += 200;
       }
    }
    // 2번 탭...
    QString beverageSTR[5]={item[10].GETname(),item[11].GETname(),item[12].GETname(),item[13].GETname(),item[14].GETname()};
    QString pixBEVERAGE[5]={item[10].GETphoto(),item[11].GETphoto(),item[12].GETphoto(),item[13].GETphoto(),item[14].GETphoto()};

    xpos_1=25;
    xpos_2=30;
    for(int i=0; i<5; i++)
    {
       if(i==3)
       {
           xpos_1=25;
           xpos_2=30;
       }
       if(i<3)
       {
           beverageLABEL[i]=new QLabel(beverageTAB);
           beveragePIX[i]=QPixmap(pixBEVERAGE[i]);
           beverageLABEL[i]->setPixmap(beveragePIX[i]);
           beverageLABEL[i]->setGeometry(xpos_1,50,150,150);
           beverageLABEL[i]->setScaledContents( true );
           beverageLABEL[i]->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
           xpos_1 += 200;

           beverageRADIO[i]=new QRadioButton(beverageSTR[i],beverageTAB);
           beverageRADIO[i]->setGeometry(xpos_2,200,150,30);
           xpos_2 += 200;
       }
       else
       {
           beverageLABEL[i]=new QLabel(beverageTAB);
           beveragePIX[i]=QPixmap(pixBEVERAGE[i]);
           beverageLABEL[i]->setPixmap(beveragePIX[i]);
           beverageLABEL[i]->setGeometry(xpos_1,250,150,150);
           beverageLABEL[i]->setScaledContents( true );
           beverageLABEL[i]->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
           xpos_1 += 200;

           beverageRADIO[i]=new QRadioButton(beverageSTR[i],beverageTAB);
           beverageRADIO[i]->setGeometry(xpos_2,400,150,30);
           xpos_2 += 200;
       }
    }
    // 3번 탭...
    QString smoothieSTR[6]={item[15].GETname(),item[16].GETname(),item[17].GETname(),item[18].GETname(),item[19].GETname(),item[20].GETname()};
    QString pixSMOOTHIE[6]={item[15].GETphoto(),item[16].GETphoto(),item[17].GETphoto(),item[18].GETphoto(),item[19].GETphoto(),item[20].GETphoto()};

    xpos_1=25;
    xpos_2=30;
    for(int i=0; i<6; i++)
    {
       if(i==3)
       {
           xpos_1=25;
           xpos_2=30;
       }
       if(i<3)
       {
           smoothieLABEL[i]=new QLabel(smoothieTAB);
           smoothiePIX[i]=QPixmap(pixSMOOTHIE[i]);
           smoothieLABEL[i]->setPixmap(smoothiePIX[i]);
           smoothieLABEL[i]->setGeometry(xpos_1,50,150,150);
           smoothieLABEL[i]->setScaledContents( true );
           smoothieLABEL[i]->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
           xpos_1 += 200;

           smoothieRADIO[i]=new QRadioButton(smoothieSTR[i],smoothieTAB);
           smoothieRADIO[i]->setGeometry(xpos_2,200,150,30);
           xpos_2 += 200;
       }
       else
       {
           smoothieLABEL[i]=new QLabel(smoothieTAB);
           smoothiePIX[i]=QPixmap(pixSMOOTHIE[i]);
           smoothieLABEL[i]->setPixmap(smoothiePIX[i]);
           smoothieLABEL[i]->setGeometry(xpos_1,250,150,150);
           smoothieLABEL[i]->setScaledContents( true );
           smoothieLABEL[i]->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
           xpos_1 += 200;

           smoothieRADIO[i]=new QRadioButton(smoothieSTR[i],smoothieTAB);
           smoothieRADIO[i]->setGeometry(xpos_2,400,150,30);
           xpos_2 += 200;
       }
    }

    connect(tab, SIGNAL(currentChanged(int)),
            this, SLOT(currentTab(int)));
    // 그룹 박스...
    box_1 = new QGroupBox(this);
    box_1->setGeometry(650,50,80,60);
    box_1->setTitle("수량");
    // 스핀 박스...
    spin = new QSpinBox(box_1);
    spin->setMinimum(0);
    spin->setMaximum(9);
    spin->setGeometry(650,60,60,30);

    spin->setSuffix("          개");
    grid = new QGridLayout(box_1);

    grid->addWidget(spin);
    // 푸쉬 버튼...
    push_1 = new QPushButton(QString("선택"),this);
    push_1->setGeometry(650,100,100,100);
    // 사이드바...
    box_2 = new QGroupBox(this);
    box_2->setGeometry(650,50,120,120);
    box_2->setTitle("사이드바");
    //box_2->setStyleSheet("font-weight: bold;");
    // 수직 레이아웃...
    layout = new QVBoxLayout(box_2);
    layout->addWidget(box_1);
    layout->addWidget(push_1);
    // 장바구니 버튼...
    push_2 = new QPushButton(QString("장바구니 담기"),this);
    push_2->setGeometry(650,300,120,30);
    // 전체취소...
    push[0] = new QPushButton(QString("전체취소"),this);
    push[0]->setGeometry(650,340,120,30);
    // 처음으로...
    push[1] = new QPushButton(QString("처음으로"),this);
    push[1]->setGeometry(650,380,120,30);

    // 주문수량
    lbl[0] = new QLabel(this);
    lbl[0]->setGeometry(770,540,100,50);
    lbl[0]->setText("전체수량");
    lbl[0]->setStyleSheet("font-weight: bold; color: red");
    lbl[0]->setFont(QFont("맑은 고딕",15));

    lbl[1] = new QLabel(this);
    lbl[1]->setGeometry(770,500,100,50);
    lbl[1]->setText("");
    // 합계금액
    lbl[2] = new QLabel(this);
    lbl[2]->setGeometry(770,640,100,50);
    lbl[2]->setText("합계금액");
    lbl[2]->setStyleSheet("font-weight: bold; color: red");
    lbl[2]->setFont(QFont("맑은 고딕",15));

    lbl[3] = new QLabel(this);
    lbl[3]->setGeometry(770,600,100,50);
    lbl[3]->setText("");
    // 전송
    push[2] = new QPushButton(QString("결제진행"),this);
    push[2]->setGeometry(650,420,120,30);

    connect(push_1,SIGNAL(clicked()),this,SLOT(selection()));
    connect(push_2,SIGNAL(clicked()),this,SLOT(shopping()));
    connect(push[0],SIGNAL(clicked()),this,SLOT(revoke()));
    connect(push[1],SIGNAL(clicked()),this,SLOT(throwback()));
    connect(push[2],SIGNAL(clicked()),this,SLOT(forwarding()));
}

void Dialog::currentTab(int index)
{
    qDebug() << "index: " << index;
}
// 선택 함수
void Dialog::selection()
{
    bool choose=true;
    int point;
    // 장바구니 꽉 차 있을 경우
    if(orders.Cart_Tot_Cnt()==5)
        return;
    //
    if(tab->currentIndex()==0) // 아이스
    {
        if(spin->value()==0)
        {
            QMessageBox::critical(this,"critical","A slap on the wrist.");
            return;
        }
        if(iceRADIO[0]->isChecked())
        {
            if(excessive!=1)
            {
                instant.Set_Name_Price(item[0].GETname(),item[0].GETprice());
                instant.Set_Code_Category_Photo(item[0].GETcode(),item[0].GETcategory(),item[0].GETphoto());
                amount=spin->value();
                choose=false;
                point=0;
            }
            else
            {
                QMessageBox::information(this,"information","Wait in the wings.");
                qDebug() << "Wait in the wings";
                return;
            }
        }
        else if(iceRADIO[1]->isChecked())
        {
            if(excessive!=1)
            {
                instant.Set_Name_Price(item[1].GETname(),item[1].GETprice());
                instant.Set_Code_Category_Photo(item[1].GETcode(),item[1].GETcategory(),item[1].GETphoto());
                amount=spin->value();
                choose=false;
                point=1;
            }
            else
            {
                QMessageBox::information(this,"information","Wait in the wings.");
                qDebug() << "Wait in the wings";
                return;
            }
        }
        else if(iceRADIO[2]->isChecked())
        {
            if(excessive!=1)
            {
                instant.Set_Name_Price(item[2].GETname(),item[2].GETprice());
                instant.Set_Code_Category_Photo(item[2].GETcode(),item[2].GETcategory(),item[2].GETphoto());
                amount=spin->value();
                choose=false;
                point=2;
            }
            else
            {
                QMessageBox::information(this,"information","Wait in the wings.");
                qDebug() << "Wait in the wings";
                return;
            }
        }
        else if(iceRADIO[3]->isChecked())
        {
            if(excessive!=1)
            {
                instant.Set_Name_Price(item[3].GETname(),item[3].GETprice());
                instant.Set_Code_Category_Photo(item[3].GETcode(),item[3].GETcategory(),item[3].GETphoto());
                amount=spin->value();
                choose=false;
                point=3;
            }
            else
            {
                QMessageBox::information(this,"information","Wait in the wings.");
                qDebug() << "Wait in the wings";
                return;
            }
        }
        else if(iceRADIO[4]->isChecked())
        {
            if(excessive!=1)
            {
                instant.Set_Name_Price(item[4].GETname(),item[4].GETprice());
                instant.Set_Code_Category_Photo(item[4].GETcode(),item[4].GETcategory(),item[4].GETphoto());
                amount=spin->value();
                choose=false;
                point=4;
            }
            else
            {
                QMessageBox::information(this,"information","Wait in the wings.");
                qDebug() << "Wait in the wings";
                return;
            }
        }
        else if(iceRADIO[5]->isChecked())
        {
            if(excessive!=1)
            {
                instant.Set_Name_Price(item[5].GETname(),item[5].GETprice());
                instant.Set_Code_Category_Photo(item[5].GETcode(),item[5].GETcategory(),item[5].GETphoto());
                amount=spin->value();
                choose=false;
                point=5;
            }
            else
            {
                QMessageBox::information(this,"information","Wait in the wings.");
                qDebug() << "Wait in the wings";
                return;
            }
        }
        else
            return;
    }
    if(tab->currentIndex()==1) // 핫
    {
        if(spin->value()==0)
        {
            QMessageBox::critical(this,"critical","A slap on the wrist.");
            return;
        }
        if(hotRADIO[0]->isChecked())
        {
            if(excessive!=1)
            {
                instant.Set_Name_Price(item[6].GETname(),item[6].GETprice());
                instant.Set_Code_Category_Photo(item[6].GETcode(),item[6].GETcategory(),item[6].GETphoto());
                amount=spin->value();
                choose=false;
                point=6;
            }
            else
            {
                QMessageBox::information(this,"information","Wait in the wings.");
                qDebug() << "Wait in the wings";
                return;
            }
        }
        else if(hotRADIO[1]->isChecked())
        {
            if(excessive!=1)
            {
                instant.Set_Name_Price(item[7].GETname(),item[7].GETprice());
                instant.Set_Code_Category_Photo(item[7].GETcode(),item[7].GETcategory(),item[7].GETphoto());
                amount=spin->value();
                choose=false;
                point=7;
            }
            else
            {
                QMessageBox::information(this,"information","Wait in the wings.");
                qDebug() << "Wait in the wings";
                return;
            }
        }
        else if(hotRADIO[2]->isChecked())
        {
            if(excessive!=1)
            {
                instant.Set_Name_Price(item[8].GETname(),item[8].GETprice());
                instant.Set_Code_Category_Photo(item[8].GETcode(),item[8].GETcategory(),item[8].GETphoto());
                amount=spin->value();
                choose=false;
                point=8;
            }
            else
            {
                QMessageBox::information(this,"information","Wait in the wings.");
                qDebug() << "Wait in the wings";
                return;
            }
        }
        else if(hotRADIO[3]->isChecked())
        {
            if(excessive!=1)
            {
                instant.Set_Name_Price(item[9].GETname(),item[9].GETprice());
                instant.Set_Code_Category_Photo(item[9].GETcode(),item[9].GETcategory(),item[9].GETphoto());
                amount=spin->value();
                choose=false;
                point=9;
            }
            else
            {
                QMessageBox::information(this,"information","Wait in the wings.");
                qDebug() << "Wait in the wings";
                return;
            }
        }
        else
            return;
    }
    if(tab->currentIndex()==2) // 음료
    {
        if(spin->value()==0)
        {
            QMessageBox::critical(this,"critical","A slap on the wrist.");
            return;
        }
        if(beverageRADIO[0]->isChecked())
        {
            if(excessive!=1)
            {
                instant.Set_Name_Price(item[10].GETname(),item[10].GETprice());
                instant.Set_Code_Category_Photo(item[10].GETcode(),item[10].GETcategory(),item[10].GETphoto());
                amount=spin->value();
                choose=false;
                point=10;
            }
            else
            {
                QMessageBox::information(this,"information","Wait in the wings.");
                qDebug() << "Wait in the wings";
                return;
            }
        }
        else if(beverageRADIO[1]->isChecked())
        {
            if(excessive!=1)
            {
                instant.Set_Name_Price(item[11].GETname(),item[11].GETprice());
                instant.Set_Code_Category_Photo(item[11].GETcode(),item[11].GETcategory(),item[11].GETphoto());
                amount=spin->value();
                choose=false;
                point=11;
            }
            else
            {
                QMessageBox::information(this,"information","Wait in the wings.");
                qDebug() << "Wait in the wings";
                return;
            }
        }
        else if(beverageRADIO[2]->isChecked())
        {
            if(excessive!=1)
            {
                instant.Set_Name_Price(item[12].GETname(),item[12].GETprice());
                instant.Set_Code_Category_Photo(item[12].GETcode(),item[12].GETcategory(),item[12].GETphoto());
                amount=spin->value();
                choose=false;
                point=12;
            }
            else
            {
                QMessageBox::information(this,"information","Wait in the wings.");
                qDebug() << "Wait in the wings";
                return;
            }
        }
        else if(beverageRADIO[3]->isChecked())
        {
            if(excessive!=1)
            {
                instant.Set_Name_Price(item[13].GETname(),item[13].GETprice());
                instant.Set_Code_Category_Photo(item[13].GETcode(),item[13].GETcategory(),item[13].GETphoto());
                amount=spin->value();
                choose=false;
                point=13;
            }
            else
            {
                QMessageBox::information(this,"information","Wait in the wings.");
                qDebug() << "Wait in the wings";
                return;
            }
        }
        else if(beverageRADIO[4]->isChecked())
        {
            if(excessive!=1)
            {
                instant.Set_Name_Price(item[14].GETname(),item[14].GETprice());
                instant.Set_Code_Category_Photo(item[14].GETcode(),item[14].GETcategory(),item[14].GETphoto());
                amount=spin->value();
                choose=false;
                point=14;
            }
            else
            {
                QMessageBox::information(this,"information","Wait in the wings.");
                qDebug() << "Wait in the wings";
                return;
            }
        }
        else
            return;
    }
    if(tab->currentIndex()==3) // 스무디
    {
        if(spin->value()==0)
        {
            QMessageBox::critical(this,"critical","A slap on the wrist.");
            return;
        }
        if(smoothieRADIO[0]->isChecked())
        {
            if(excessive!=1)
            {
                instant.Set_Name_Price(item[15].GETname(),item[15].GETprice());
                instant.Set_Code_Category_Photo(item[15].GETcode(),item[15].GETcategory(),item[15].GETphoto());
                amount=spin->value();
                choose=false;
                point=15;
            }
            else
            {
                QMessageBox::information(this,"information","Wait in the wings.");
                qDebug() << "Wait in the wings";
                return;
            }
        }
        else if(smoothieRADIO[1]->isChecked())
        {
            if(excessive!=1)
            {
                instant.Set_Name_Price(item[16].GETname(),item[16].GETprice());
                instant.Set_Code_Category_Photo(item[16].GETcode(),item[16].GETcategory(),item[16].GETphoto());
                amount=spin->value();
                choose=false;
                point=16;
            }
            else
            {
                QMessageBox::information(this,"information","Wait in the wings.");
                qDebug() << "Wait in the wings";
                return;
            }
        }
        else if(smoothieRADIO[2]->isChecked())
        {
            if(excessive!=1)
            {
                instant.Set_Name_Price(item[17].GETname(),item[17].GETprice());
                instant.Set_Code_Category_Photo(item[17].GETcode(),item[17].GETcategory(),item[17].GETphoto());
                amount=spin->value();
                choose=false;
                point=17;
            }
            else
            {
                QMessageBox::information(this,"information","Wait in the wings.");
                qDebug() << "Wait in the wings";
                return;
            }
        }
        else if(smoothieRADIO[3]->isChecked())
        {
            if(excessive!=1)
            {
                instant.Set_Name_Price(item[18].GETname(),item[18].GETprice());
                instant.Set_Code_Category_Photo(item[18].GETcode(),item[18].GETcategory(),item[18].GETphoto());
                amount=spin->value();
                choose=false;
                point=18;
            }
            else
            {
                QMessageBox::information(this,"information","Wait in the wings.");
                qDebug() << "Wait in the wings";
                return;
            }
        }
        else if(smoothieRADIO[4]->isChecked())
        {
            if(excessive!=1)
            {
                instant.Set_Name_Price(item[19].GETname(),item[19].GETprice());
                instant.Set_Code_Category_Photo(item[19].GETcode(),item[19].GETcategory(),item[19].GETphoto());
                amount=spin->value();
                choose=false;
                point=19;
            }
            else
            {
                QMessageBox::information(this,"information","Wait in the wings.");
                qDebug() << "Wait in the wings";
                return;
            }
        }
        else if(smoothieRADIO[5]->isChecked())
        {
            if(excessive!=1)
            {
                instant.Set_Name_Price(item[20].GETname(),item[20].GETprice());
                instant.Set_Code_Category_Photo(item[20].GETcode(),item[20].GETcategory(),item[20].GETphoto());
                amount=spin->value();
                choose=false;
                point=20;
            }
            else
            {
                QMessageBox::information(this,"information","Wait in the wings.");
                qDebug() << "Wait in the wings";
                return;
            }
        }
        else
            return;
    }
    // 같은 품목 처리...
    if(orders.Cart_Tot_Cnt()>0)
    {
        for(int i=0; i<orders.Cart_Tot_Cnt(); i++)
        {
            if(!strcmp(item[point].GETname(),orders.Compare_Item_Name(i)))
            {
                qDebug() << "중복";
                QMessageBox::warning(this,"warning","More haste, less speed.");
                return;
            }
        }
    }
    //
    if(spin->value()!=0)
        QMessageBox::about(this,"information","Don't whistle until you are out of the wood.");
    // 선택
    if(choose==false)
    {
        line+=1;
        if(excessive!=1)
        {
            fill = new QLabel(this);
            fill->installEventFilter(this);
            fill->setGeometry(650, 200, 150, 100);
            fill->show();
            fill->setText(QString("%1\n%2\n%3%4%5%6%7").arg("선택 목록").arg(item[point].GETname()).arg(item[point].GETprice()).arg("원 ").arg("x ").arg(spin->value()).arg("개"));
            fill->setWordWrap(true);
            excessive=1;
        }
        else
        {
            QMessageBox::critical(this,"critical","Wait in the wings");
            return;
        }
    }
}

bool Dialog::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == fill && event->type()==QMouseEvent::MouseButtonPress)
    {
        fill->clear();
        line-=1;
        excessive=0;
    }
    return QWidget::eventFilter(watched, event);
}

// 장바구니 함수
void Dialog::shopping()
{
    if(orders.Cart_Tot_Cnt()==5)
        return;
    if(orders.Cart_Tot_Cnt()+1==line)
    {
        fill->clear();
        //qDebug() << instant.GETcode() << instant.GETcategory() << instant.GETphoto() << orders.Cart_Tot_Cnt();
        //orders.Set_Code_Category_Photo(instant.GETcode(),instant.GETcategory(),instant.GETphoto(),orders.Cart_Tot_Cnt());
        orders.Add_Item(instant.GETname(),instant.GETprice(),amount);
        orders.Set_Code_Category_Photo(instant.GETcode(),instant.GETcategory(),instant.GETphoto(),orders.Cart_Tot_Cnt()-1);
        //
        full[begin] = new QLabel(this);
        full[begin]->setGeometry(position, 525, 150, 100);
        full[begin]->show();
        full[begin]->setText(QString("%1%2\n%3\n%4%5%6%7%8").arg(begin+1).arg("번 목록").arg(orders.Cart_Item_Name(begin)).arg(orders.Cart_Item_Price(begin)).arg("원 ").arg("x ").arg(orders.Cart_Item_Amount(begin)).arg("개"));
        full[begin]->setWordWrap(true);
        //
        int match;
        for(int i=0; i<21; i++)
        {
            if(!strcmp(orders.Compare_Item_Name(begin),item[i].GETname()))
            {
                match=i;
            }
        }
        for(int i=0; i<orders.Cart_Tot_Cnt(); i++)
        {
            orders.show(i);
        }

        pix=QPixmap(item[match].GETphoto());
        field[begin] = new QLabel(this);
        field[begin]->show();
        field[begin]->setPixmap(pix.scaled(100,150, Qt::KeepAspectRatio));
        field[begin]->setGeometry(position, 600, 150, 100);
        //
        position += 150;
        excessive=0;
        begin++;
        // 전체수량
        lbl[1]->setText(QString("%1%2").arg(orders.Cart_Tot_Cnt()).arg("개"));
        lbl[1]->setStyleSheet("font-weight: bold; color: black");
        lbl[1]->setFont(QFont("맑은 고딕",25));
        // 합계금액
        int total=0;
        for(int i=0; i<orders.Cart_Tot_Cnt(); i++)
        {
            total+=orders.Cart_Tot_Price(i);
        }
        lbl[3]->setText(QString("%1%2").arg(total).arg("원"));
        lbl[3]->setStyleSheet("font-weight: bold; color: black");
        lbl[3]->setFont(QFont("맑은 고딕",15));

        spin->setValue(0);
    }
}
// 전체취소
void Dialog::revoke()
{
    if(orders.Cart_Tot_Cnt()>0)
    {
        qDebug()<< "전체취소";
        for(int i=0; i<orders.Cart_Tot_Cnt(); i++)
        {
            full[i]->clear();
            field[i]->clear();
            qDebug()<< i <<"번 삭제";
        }
        // 초기화...
        orders=resurrection;
        line=0;
        excessive=0;
        begin=0;
        position=30;
        lbl[1]->setText("");
        lbl[3]->setText("");

        spin->setValue(0);
        fill->clear();

        qDebug()<< orders.Cart_Tot_Cnt();
        for(int i=0; i<orders.Cart_Tot_Cnt(); i++)
        {
            orders.show(i);
        }
    }
}
// 처음
void Dialog::throwback()
{
    /*
    socket->disconnectFromHost();
    if (socket->state() == QAbstractSocket::UnconnectedState
        || socket->waitForDisconnected(1000)) {
            qDebug("Disconnected!");
    }
    */
    this->close();
}
// 결제
void Dialog::forwarding()
{
    if(orders.Cart_Tot_Cnt()>0)
    {
        p_dialog = new PayDialog(this);
        p_dialog->setFixedSize(450,200);

        QPalette pal = palette();

        // set black background
        /*
        pal.setColor(QPalette::Background, Qt::black);
        p_dialog->setAutoFillBackground(true);
        p_dialog->setPalette(pal);
        */
        qDebug() <<"초기 결제수단: " << orders.Get_Payment_Info();
        connect(this,SIGNAL(sendCLASS(Orders)),p_dialog,SLOT(recvCLASS(Orders)));
        emit sendCLASS(orders);
        p_dialog->exec();
        qDebug() <<"반환된 결제수단: " << orders.Get_Payment_Info();

        if(decision==0)
        {
           socket->waitForBytesWritten();
           socket->write((char*)&type, sizeof(int));

           socket->waitForBytesWritten();
           socket->write((char*)&orders, sizeof(Orders));
           qDebug() <<"다이얼로그에서 전송";
           this->close();
        }
        else
            decision=0;
    }
}

void Dialog::closeEvent (QCloseEvent *event)
{

    socket->disconnectFromHost();
    if (socket->state() == QAbstractSocket::UnconnectedState
        || socket->waitForDisconnected(1000)) {
            qDebug("Disconnected!");
    }
    event->accept();

    /*
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Walk on eggshells.",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        socket->disconnectFromHost();
        if (socket->state() == QAbstractSocket::UnconnectedState
            || socket->waitForDisconnected(1000)) {
                qDebug("Disconnected!");
        }
        event->accept();
    }
    */
}

void Dialog::recvINT(int decision)
{
    this->decision=decision;
}

void Dialog::recvOR(Orders orders)
{
    this->orders=orders;
}

Dialog::~Dialog()
{
    qDebug() <<"종료";
    delete ui;
}
