#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <QProcess>
#include <QString>
#include <QColor>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <thread>
#include <mutex>
#include <time.h>
#include <QMessageBox>

using std::cout;
using std::endl;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    connect(&packfuneg,&packfun::value_send,this,&MainWindow::output_cpuinfo);
    connect(&packfuneg,&packfun::value_send_1,this,&MainWindow::output_hostinfo);
    connect(&packfuneg,&packfun::value_send_2,this,&MainWindow::output_systeminfo);
    connect(&packfuneg,&packfun::value_send_3,this,&MainWindow::output_processinfo);
    connect(this,&MainWindow::setcpuvalue_,this,&MainWindow::setcpuvalue);
    connect(this,&MainWindow::setmemvalue_,this,&MainWindow::setmemvalue);
    connect(this,&MainWindow::settimevalue_,this,&MainWindow::settimevalue);
    ui->setupUi(this);
    onTimeout();
    ui->listWidget->setFont(QFont("Monospace",10));
    packfuneg.read_cpuinfo();
    packfuneg.read_hostname();
    tmpos_type = packfuneg.read_ostype();
    tmpos_rele = packfuneg.read_osrelease();
    packfuneg.read_uptime();
    packfuneg.read_processinfo();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->start(1000);
    QTimer *timer1 = new QTimer(this);
    connect(timer1, SIGNAL(timeout()), this, SLOT(onTimeout1()));
    timer1->start(1000);

    //    ui->progressBar->setValue((int)packfuneg.read_cpu_use());
    //    add_cpupoint((float)packfuneg.read_cpu_use());
    //    update_cpuview();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::output_cpuinfo(QString s)
{
    ui->textBrowser_3->append(s);
}

void MainWindow::output_hostinfo(QString s)
{
    ui->textBrowser->append(s);
}

void MainWindow::output_systeminfo(QString s)
{
    ui->textBrowser_2->append(s);
}

void MainWindow::output_processinfo(QString s)
{
    ui->listWidget->addItem(s);
}


void MainWindow::on_pushButton_clicked()
{
    //重置并且刷新
    ui->listWidget->clear();
    packfuneg.read_processinfo();


    QString name = ui->plainTextEdit_2->toPlainText();
    QString pid = ui->plainTextEdit->toPlainText();
    if(!name.length()&&!pid.length())//no name,no pid
        return;
    else if(name.length()&&!pid.length()){//have name,no pid
        //        char nameinfo[25];//存储完整名字,有问题
        //        sprintf(nameinfo,"(%-20s)",name.toStdString().c_str());//转化为完整名称
        //        QList<QListWidgetItem *> list = ui->listWidget->findItems(QString::fromStdString(string(nameinfo)),Qt::MatchContains);
        QList<QListWidgetItem *> list = ui->listWidget->findItems(name,Qt::MatchContains);
        if(list.length() == 0){
            ui->plainTextEdit->setPlainText("Not found!");
            ui->plainTextEdit_2->setPlainText("Not found!");
        }else{
            for(int i = 0;i < list.length();i++)
            {
                list[i]->setTextColor(Qt::red);
                list[i]->setBackgroundColor(Qt::yellow);
            }
            //        int row = ui->listWidget->row(list[0]);
            //        QListWidgetItem  *item= ui->listWidget->takeItem(row);
            //        delete item;
            int row = ui->listWidget->row(list[0]);
            ui->listWidget->setCurrentRow(row);
        }
    }else//have pid
    {
        QString allname = QString::fromStdString(packfuneg.read_assignpid(pid.toStdString()));
        if(allname == "")
        {
            ui->plainTextEdit->setPlainText("Not found!");
            ui->plainTextEdit_2->setPlainText("Not found!");
            return;
        }
        QList<QListWidgetItem *> list = ui->listWidget->findItems(allname,Qt::MatchExactly);//避免特殊情况readdir读取不到某些隐藏目录
        if(list.length() == 0){
            ui->plainTextEdit->setPlainText("Not found!");
            ui->plainTextEdit_2->setPlainText("Not found!");
        }else{
            for(int i = 0;i < list.length();i++)
            {
                list[i]->setTextColor(Qt::red);
                list[i]->setBackgroundColor(Qt::yellow);
            }
            //        int row = ui->listWidget->row(list[0]);
            //        QListWidgetItem  *item= ui->listWidget->takeItem(row);
            //        delete item;
            int row = ui->listWidget->row(list[0]);
            ui->listWidget->setCurrentRow(row);
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    //重置并且刷新
    ui->listWidget->clear();
    packfuneg.read_processinfo();
    ui->plainTextEdit_2->clear();
    ui->plainTextEdit->clear();
}

void MainWindow::on_pushButton_2_clicked()
{
    QString pid = ui->plainTextEdit->toPlainText();
    if(pid.length() == 0){
        ui->plainTextEdit->setPlainText("Please enter pid!");
        ui->plainTextEdit_2->setPlainText("Please enter pid!");
        return;
    }
    string tmp = packfuneg.read_assignpid(pid.toStdString());
    if(tmp == "")
    {
        ui->plainTextEdit->setPlainText("Not find process!");
        ui->plainTextEdit_2->setPlainText("Not find process!");
        return;
    }
    QList<QListWidgetItem *> list = ui->listWidget->findItems(QString::fromStdString(tmp),Qt::MatchExactly);
    if(list.length() == 0){//避免特殊情况readdir读取不到某些隐藏目录
        ui->plainTextEdit->setPlainText("Not found!");
        ui->plainTextEdit_2->setPlainText("Not found!");
        return;
    }
    else
    {
        cout << pid.toInt() << endl;
        cout << tmp << endl;
        if(!kill(pid.toInt(),SIGTERM)){
            ui->plainTextEdit->setPlainText("Kill success!");
            ui->plainTextEdit_2->setPlainText("Kill success!");
            ui->listWidget->clear();
            packfuneg.read_processinfo();
        }
        else{
            ui->plainTextEdit->setPlainText("Kill failed!");
            ui->plainTextEdit_2->setPlainText("Kill failed!");
        }
    }
}

void MainWindow::on_pushButton_4_clicked()//启动一个新进程
{
    QProcess *pro = new QProcess;
    QString tmp = ui->lineEdit->text();
    pro->start(tmp);
}

void MainWindow::add_cpupoint(float usage)//更新CPU使用率列表
{
    int i;
    int size =  yList_cpu.size();
    if(size > 120)
        yList_cpu.pop_front();
    if(size == 0)
    {
        for(i = 0;i < 119;i++)
        {
            yList_cpu.push_back(0);
        }
    }
    if(size >= 1)
    {
        yList_cpu.push_back(usage);
    }
}

void MainWindow::update_cpuview()//绘制CPU使用率曲线图
{
    int count = 0;
    QPixmap pix1(600,160);
    QPainter painter1(&pix1);
    pix1.fill(Qt::yellow);
    QPen pen1;
    pen1.setColor(Qt::green);
    painter1.setPen(pen1);
    for(int i =1;i < 4;i++)
    {
        painter1.drawLine(0,i*40,600,i*40);
    }
    QPen pen_1;
    pen_1.setColor(Qt::blue);
    pen_1.setWidth(2);
    painter1.setPen(pen_1);
    while(count <(yList_cpu.size() - 1))
    {
        painter1.drawLine(5*count,160-1.6*(yList_cpu.value(count)),5*(count + 1),160 -1.6*yList_cpu.value(count + 1));
        count++;
    }
    ui->label_14->setPixmap(pix1);
}

void MainWindow::add_mempoint(float usage)//更新MEM使用率列表
{
    int i;
    int size =  yList_mem.size();
    if(size > 120)
        yList_mem.pop_front();
    if(size == 0)
    {
        for(i = 0;i < 119;i++)
        {
            yList_mem.push_back(0);
        }
    }
    if(size >= 1)
    {
        yList_mem.push_back(usage);
    }
}

void MainWindow::update_memview()//绘制MEM使用率曲线图
{
    int count = 0;
    QPixmap pix2(600,160);
    QPainter painter2(&pix2);
    pix2.fill(Qt::black);
    QPen pen2;
    pen2.setColor(Qt::lightGray);
    painter2.setPen(pen2);
    for(int i =1;i < 4;i++)
    {
        painter2.drawLine(0,i*40,600,i*40);
    }
    QPen pen_2;
    pen_2.setColor(Qt::white);
    pen_2.setWidth(2);
    painter2.setPen(pen_2);
    while(count <(yList_mem.size() - 1))
    {
        painter2.drawLine(5*count,160-1.6*(yList_mem.value(count)),5*(count + 1),160 -1.6*yList_mem.value(count + 1));
        count++;
    }
    ui->label_15->setPixmap(pix2);
}
void MainWindow::thread_cpu(Ui::MainWindow *ui)
{
    m1.lock();
    double usage = packfuneg.read_cpu_use();//更新CPU信息显示
    emit setcpuvalue_((int)usage);
    add_cpupoint((float)usage);
    update_cpuview();
    m1.unlock();
}

void MainWindow::thread_mem(Ui::MainWindow *ui)
{
    m2.lock();
    double usage = packfuneg.read_mem_use();//更新MEM信息显示
    emit setmemvalue_((int)usage);
    add_mempoint((float)usage);
    update_memview();
    m2.unlock();
}

void MainWindow::onTimeout()//定时更新使用率曲线图
{
    std::thread t1(&MainWindow::thread_cpu, this,ui);
    t1.detach();
    std::thread t2(&MainWindow::thread_mem, this,ui);
    t2.detach();
}

void MainWindow::onTimeout1()//定时更新当前时间和系统运行时间
{
    QString timenow;
    ui->textBrowser_2->clear();
    ui->textBrowser_2->append(QString::fromStdString(tmpos_type));
    ui->textBrowser_2->append(QString::fromStdString(tmpos_rele));
    timenow = QString::fromStdString(packfuneg.read_uptime());
    emit settimevalue_(timenow);
}

void MainWindow::setcpuvalue(int value)
{
    ui->progressBar->setValue(value);
}

void MainWindow::setmemvalue(int value)
{
    ui->progressBar_2->setValue(value);
}

void MainWindow::settimevalue(QString value)
{
    ui->textBrowser_4->clear();
    ui->textBrowser_4->append(value);
}

void MainWindow::on_pushButton_5_clicked()
{
    QMessageBox message(QMessageBox::Warning,"Warning","Really to shut down?",QMessageBox::Yes|QMessageBox::No,NULL);
    if (message.exec()==QMessageBox::Yes)
    {
        QApplication::exit();
        //    system("shutdown -h now");
    }
    else
    {

    }

}
