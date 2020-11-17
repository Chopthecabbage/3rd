#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QPixmap>
#include <QPushButton>
//
#include <QDateTime>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    QPixmap bg(":/third/example/cafe.jpg");
    bg = bg.scaled(800,600, Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bg);
    this->setPalette(palette);

    //QPalette p(palette());
    //p.setBrush(QPalette::Background, bg);

    //setAutoFillBackground(true);
    //setPalette(p);

    ui->setupUi(this);
    setWindowTitle("Self Service Station");
    //QPixmap pix("/Users/iotpc/Desktop/TCP/POS/coffee.jpg");
    //QPixmap pix("/Users/Ah-/Desktop/TCP/POS/coffee.jpg);
    //QPixmap pix(":/third/example/cafe.jpg");
    //ui->picture->setPixmap(pix);
    //ui->picture->setPixmap(pix.scaled(800,600, Qt::KeepAspectRatio));

    QString btn_str[2]={"먹고가기","포장하기"};
    QPushButton *btn[2];

    int xpos = 250;
    for(int i=0; i<2; i++)
    {
        btn[i] = new QPushButton(btn_str[i],this);
        btn[i]->setGeometry(xpos, 500, 100, 50);
        xpos += 100;
    }
    connect(btn[0], SIGNAL(clicked()), this, SLOT(portal()));
    connect(btn[1], SIGNAL(clicked()), this, SLOT(portal()));
    //
    menuBar = new QMenuBar(this);
    menu = new QMenu("et cetera");

    act[0] = new QAction("점검",this);
    //act[0]->setStatusTip("Not available.");
    act[0]->setIcon(QIcon(":/third/example/fix.png"));

    act[1] = new QAction("도움말",this);
    act[1]->setShortcut(Qt::CTRL | Qt::Key_H);

    menu->addAction(act[0]);
    menu->addAction(act[1]);
    //menu->addSeparator();
    menuBar->addMenu(menu);
    menuBar->setGeometry(0,0,800,20);
    //menuBar->setStyleSheet("background-color: white");
    connect(menu, SIGNAL(triggered(QAction*)), this,
                        SLOT(trigerMenu(QAction*)));
    // 시계
    label_date_time = new QLabel(this);
    label_date_time->setGeometry(575, 25, 215, 40);
    label_date_time->setStyleSheet("font-weight: bold; color: black; background-color: white");
    label_date_time->setFont(QFont("맑은 고딕",30));

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(myfunction()));
    timer->start(1000);
    /*
    box = new QGroupBox(this);
    box->setGeometry(500,50,250,100);
    box->setTitle("시계");
    box->setStyleSheet("font-weight: bold; border: none; color: black");
    box->setFont(QFont("맑은 고딕",20));

    arr = new QGridLayout(box);
    arr->addWidget(label_date_time);
    */
    // 종료 단축키...
    QAction *cls = new QAction(this);
    cls->setShortcut(Qt::Key_Q | Qt::CTRL);

    connect(cls, SIGNAL(triggered()), this, SLOT(close()));
    this->addAction(cls);

    lbl = new QLabel(this);
    lbl->setGeometry(500,5,90,90);
    lbl->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    lbl->setOpenExternalLinks(true);
    lbl->setTextFormat(Qt::RichText);
    lbl->setText("<a href=\"http://www.megacoffee.me\"> <img src=:/third/example/dot.png> </img></a>");
}

void Widget::myfunction()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");

    label_date_time->setText(time_text);
}

void Widget::portal()
{
    dialog = new Dialog(this);
    dialog->setFixedSize(900,750);
    this->hide();
    dialog->exec();
    this->show();
}

void Widget::trigerMenu(QAction *act)
{
    if(act->text()=="점검")
        this->close();
    else
    {
        QMessageBox::information( this,
                       "도움말",
                       "Unit 210, be ambitious" );
    }
}

void Widget::closeEvent (QCloseEvent *event)
{
    QMessageBox::StandardButton resBtn = QMessageBox::question( this, "Walk on eggshells.",
                                                                tr("Are you sure?\n"),
                                                                QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes,
                                                                QMessageBox::Yes);
    if (resBtn != QMessageBox::Yes) {
        event->ignore();
    } else {
        event->accept();
    }
}

/*
void Widget::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::WindowStateChange)
    {
        if (isMinimized() == true)
            setWindowFlags(windowFlags() | Qt::Tool);
        else
            setWindowFlags(windowFlags() & ~Qt::Tool);
    }
}
*/

Widget::~Widget()
{
    delete ui;
}

