#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dbhelper.h"
#include "userdaoimp.h"
#include "home.h"
#include <iostream>
#include <QSqlQuery>
#include <QtDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->passwd->setEchoMode(QLineEdit::Password);
    home = new Home();
    home->hide();
    connect(this,SIGNAL(userLogin(const QString&,const QString&)),home,SLOT(onuserLogin(const QString &,const QString &)));
    connect(home,SIGNAL(userLogout()),this,SLOT(onuserLogout()));
    super_home = new superhome();
    super_home->hide();
    connect(this,SIGNAL(superLogin(const QString&,const QString&)),super_home,SLOT(onsuperLogin(const QString &,const QString &)));
    connect(super_home,SIGNAL(superLogout()),this,SLOT(onsuperLogout()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if(ui->username->text().isEmpty()){
        QMessageBox::critical(this,"警告","用户名不允许为空");
        return;
    }
    if(ui->passwd->text().isEmpty()){
        QMessageBox::critical(this,"警告","密码不允许为空");
        return;
    }
    QString username = ui->username->text();
    QString passwd = ui->passwd->text();

    UserDaoImp *udi = new UserDaoImp();
    QSqlQuery query = udi->selectSuperById(username);

     int size = query.size();
     if(size == 0){
         QMessageBox::critical(this,"警告","用户不存在");
         return;
     }
     QString password;
     while(query.next()){
         password = query.value(3).toString();
         qDebug() << password;
     }

     if(passwd != password){
         QMessageBox::critical(this,"警告","密码错误");
         return;
     }
     ui->passwd->clear();
     this->hide();
     super_home->show();

     DBHelper *helper = DBHelper::getInstance();
     helper->connectDatabase();
     emit superLogin(username,passwd);
}

void MainWindow::on_pushButton_2_clicked()
{
   if(ui->username->text().isEmpty()){
       QMessageBox::critical(this,"警告","用户名不允许为空");
       return;
   }
   if(ui->passwd->text().isEmpty()){
       QMessageBox::critical(this,"警告","密码不允许为空");
       return;
   }
   QString username = ui->username->text();
   QString passwd = ui->passwd->text();

   UserDaoImp *udi = new UserDaoImp();
   QSqlQuery query = udi->selectUserById(username);

    int size = query.size();
    if(size == 0){
        QMessageBox::critical(this,"警告","用户不存在");
        return;
    }
    QString password;
    while(query.next()){
        password = query.value(3).toString();
        qDebug() << password;
    }

    if(passwd != password){
        QMessageBox::critical(this,"警告","密码错误");
        return;
    }
    ui->passwd->clear();
    this->hide();
    home->show();

    DBHelper *helper = DBHelper::getInstance();
    helper->connectDatabase();
    emit userLogin(username,passwd);
}

void MainWindow::onuserLogout(){
    home->hide();
    this->show();
}

void MainWindow::onsuperLogout(){
    super_home->hide();
    this->show();
}
