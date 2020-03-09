#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColor>
#include <QPixmap>
#include <QPainter>
#include <mutex>
#include "pack.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    packfun packfuneg;
    QList<float> yList_cpu;
    QList<float> yList_mem;
    std::mutex m1;
    std::mutex m2;
    string tmpos_type;
    string tmpos_rele;

public slots:
    void output_cpuinfo(QString s);
public slots:
    void output_hostinfo(QString s);
public slots:
    void output_systeminfo(QString s);
public slots:
    void output_processinfo(QString s);
private slots:
    void on_pushButton_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
private slots:
    void onTimeout();
    void onTimeout1();

    void on_pushButton_5_clicked();

public:
    void add_cpupoint(float usage);
    void update_cpuview();
    void add_mempoint(float usage);
    void update_memview();
    void thread_cpu(Ui::MainWindow *ui);
    void thread_mem(Ui::MainWindow *ui);
//解决线程改变控件值时崩溃的问题,使用信号槽解决问题
signals:
    void setcpuvalue_(int value);
signals:
    void setmemvalue_(int value);
signals:
    void settimevalue_(QString value);
public slots:
    void setcpuvalue(int value);
public slots:
    void setmemvalue(int value);
public slots:
    void settimevalue(QString  value);

};

#endif // MAINWINDOW_H
