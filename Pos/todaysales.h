#ifndef TODAYSALES_H
#define TODAYSALES_H

#include <QDialog>
#include <QTcpSocket>

namespace Ui {
class TodaySales;
}

class TodaySales : public QDialog
{
    Q_OBJECT

public:
    explicit TodaySales(QWidget *parent = nullptr);
    ~TodaySales();
    void Print_Today_SalesInfo();
public slots:
    void recv_socket(QTcpSocket *socket);
private slots:
    void on_checkBtn_clicked();

private:
    Ui::TodaySales *ui;
    QTcpSocket *_socket;
};

#endif // TODAYSALES_H
