#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

//    QFont font = a.font();
//    font.setPointSize(10);//字体大小
//    font.setFamily("Monospace");
//    a.setFont(font);

    w.show();

    return a.exec();
}
