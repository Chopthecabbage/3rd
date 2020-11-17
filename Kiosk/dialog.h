#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QWidget>
#include <QTabWidget>
#include <QRadioButton>
#include <QPixmap>
#include <QLabel>
#include <QGroupBox>
#include <QSpinBox>
#include <QBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include <QMouseEvent>
#include <QCloseEvent>

#include "item.h"
#include "orders.h"
#include "paydialog.h"

namespace Ui {
class Dialog;
}

class QTcpSocket; // 소켓...

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    bool eventFilter(QObject *watched, QEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    Ui::Dialog *ui;
    QTcpSocket *socket; // 나의 소켓
    Item item[21];
    Orders orders;
    Orders resurrection;
    int type=1;

    QTabWidget *tab;
    QWidget *iceTAB;
    QWidget *hotTAB;
    QWidget *beverageTAB;
    QWidget *smoothieTAB;

    QRadioButton *iceRADIO[6];
    QLabel *iceLABEL[6];
    QPixmap icePIX[6];

    QRadioButton *hotRADIO[4];
    QLabel *hotLABEL[4];
    QPixmap hotPIX[4];

    QRadioButton *beverageRADIO[5];
    QLabel *beverageLABEL[5];
    QPixmap beveragePIX[5];

    QRadioButton *smoothieRADIO[6];
    QLabel *smoothieLABEL[6];
    QPixmap smoothiePIX[6];

    QGroupBox *box_1;
    QGroupBox *box_2;
    QSpinBox *spin;
    QPushButton *push_1;
    QPushButton *push_2;

    QGridLayout *grid;
    QVBoxLayout *layout;

    QLabel *fill;
    QLabel *full[5];
    QLabel *field[5];

    int excessive=0;
    int begin=0;
    int position=30;

    QPixmap pix;

    Item instant;
    int amount;
    int line=0;

    QLabel  *lbl[4];
    QPushButton *push[3];

    PayDialog *p_dialog;
    int decision=0;

private slots:
    void currentTab(int index);
    void selection();
    void shopping();
    void revoke();
    void throwback();
    void forwarding();
    void recvINT(int decision);
    void recvOR(Orders orders);

signals:
    void sendCLASS(Orders orders);

};

#endif // DIALOG_H
