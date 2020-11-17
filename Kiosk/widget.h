#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMenuBar>
#include <QAction>
#include <QShortcut>
#include <QLabel>
//
#include <QTimer>
//#include <QGroupBox>
//#include <QBoxLayout>

#include "dialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    //void changeEvent(QEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    Ui::Widget *ui;
    Dialog *dialog;

    QMenuBar *menuBar;
    QMenu *menu;
    QAction *act[2];

    QTimer *timer;
    QLabel *label_date_time;

    //QGroupBox *box;
    //QGridLayout *arr;

    QLabel *lbl;
    QPixmap home;

private slots:
    void portal();
    void trigerMenu(QAction *act);
    void myfunction();
};
#endif // WIDGET_H
