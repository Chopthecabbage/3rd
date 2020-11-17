#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFont font;
    font.setFamily(QString("돋움"));
    a.setFont(font);
    Widget w;
    w.setFixedSize(800,600);
    w.show();
    return a.exec();
}
