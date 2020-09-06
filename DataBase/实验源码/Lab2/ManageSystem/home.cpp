#include "home.h"
#include "ui_home.h"
#include "userdaoimp.h"
#include <QDebug>
#include <QMessageBox>

Home::Home(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);
    ui->ok_vipid_button->setEnabled(true);
    ui->notok_vipid_button->setEnabled(false);
    ui->finish_button->setEnabled(false);
}

Home::~Home()
{
    delete ui;
}

void Home::onuserLogin(const QString &username,const QString &passwd){
    jobid = username;
    qDebug() << jobid;
    QSqlQuery query;
    query.prepare("select ename from employee where jobid = :a");
    query.bindValue(":a",jobid);
    query.exec();
    while(query.next()){
        ui->lineEdit_3->setText(jobid);
        ui->lineEdit_4->setText(query.value(0).toString());
        qDebug()<< "jobid:" << jobid;
        qDebug() << "name:" << query.value(0).toString();
    }
}


void Home::on_exit_Button_clicked()
{
    DBHelper *helper = DBHelper::getInstance();
    helper->disconnectDatabase();
    emit userLogout();
}

void Home::on_ok_vipid_button_clicked()
{
    if(ui->vipid->text().isEmpty()){
        QMessageBox::critical(this,"警告","会员号不允许为空");
        return;
    }

    QString tmp = ui->vipid->text();
    QSqlQuery query;
    //准备SQL语句
    query.prepare("select * from vip where vipid = :vipid");
    query.bindValue(":vipid",tmp);
    query.exec();

     int size = query.size();
     if(size == 0){
         QMessageBox::critical(this,"警告","会员不存在");
         return;
     }
     query.next();
     if(query.value(2).toInt() == 2){
         QMessageBox::critical(this,"警告","会员卡无效");
         return;
     }
     //这里应该将数据库中的状态进行更新,在这里先省略一下，日后来写
     if(query.value(2).toInt() == 1){
         if(QDate::currentDate() > query.value(4).toDate()){
             QString mess = "会员卡无效，有效日期至"+query.value(4).toString();
             QMessageBox::critical(this,"警告",mess);
             query.clear();
             query.prepare("update vip set state = :a where vipid = :b");
             query.bindValue(":a",2);
             query.bindValue(":b",tmp);
             query.exec();
             return;
         }
     }
     vipid = tmp;
     money = query.value(1).toDouble();
     discount = 0.9;
     state = query.value(2).toInt();
     exp = query.value(4).toDate();
     money_this = 0;
     ui->ok_vipid_button->setEnabled(false);
     ui->notok_vipid_button->setEnabled(true);
}

void Home::on_notok_vipid_button_clicked()
{
    vipid = "";
    ui->vipid->clear();
    discount = 1;
    state = 3;
    money_this = 0;
    ui->ok_vipid_button->setEnabled(true);
    ui->notok_vipid_button->setEnabled(false);
}

//购买按钮的功能
void Home::on_wantbut_button_clicked()
{
    if(ui->goodid->text().isEmpty()){
        QMessageBox::critical(this,"警告","商品货号不允许为空");
        return;
    }
    if(ui->goodnumber->text().isEmpty()){
        QMessageBox::critical(this,"警告","商品数量不允许为空");
        return;
    }

    QString tmp = ui->goodid->text();
    QSqlQuery query;
    //准备SQL语句
    query.prepare("select * from goods where productcode = :productcode");
    query.bindValue(":productcode",tmp);
    query.exec();

     int size = query.size();
     if(size == 0){
         QMessageBox::critical(this,"警告","商品不存在");
         return;
     }

     tmp = ui->goodnumber->text();
     QString remainingnumber;
     if(query.size() != 0 ){
         query.next();
         remainingnumber = query.value(1).toString();
     }
     if(remainingnumber.toInt() < tmp.toInt()){
         QString mess = "商品数量不足，最大可获得商品数量为"+remainingnumber;
         QMessageBox::critical(this,"警告",mess);
         return;
     }
     //消费金额以及折扣后消费金额的显示
     double current_money = query.value(2).toDouble() * tmp.toInt();
    money_this += current_money;
    ui->money_edit->setText(QString::number(money_this, 10, 2));
    ui->moneydiscount_edit->setText(QString::number(money_this*discount,10,2));
    //对数据库中剩余的商品库存进行更改
    query.clear();
    query.prepare("update goods set remainingnumber = remainingnumber - :a where productcode = :b");
    query.bindValue(":a",tmp.toInt());
    query.bindValue(":b",ui->goodid->text());
    query.exec();
    //增加新的expense记录
    query.clear();
    if(vipid != ""){
        query.prepare("insert into expenserecord (vipid,edate,monetary,goodid,goodnumber) values (:a,:b,:c,:d,:e)");
        query.bindValue(":a",vipid);
        query.bindValue(":b",QDate::currentDate());
        query.bindValue(":c",current_money*discount);
        query.bindValue(":d",ui->goodid->text());
        query.bindValue(":e",tmp.toInt());
        query.exec();
    }else{
        query.prepare("insert into expenserecord (edate,monetary,goodid,goodnumber) values (:b,:c,:d,:e)");
        query.bindValue(":b",QDate::currentDate());
        query.bindValue(":c",current_money*discount);
        query.bindValue(":d",ui->goodid->text());
        query.bindValue(":e",tmp.toInt());
        query.exec();
    }
    //vip中消费金额记录
    if(vipid != ""){
        query.clear();
        query.prepare("update vip set expense = :a where vipid = :b");
        query.bindValue(":a",money+money_this);
        query.bindValue(":b",vipid);
        query.exec();
    }
    ui->finish_button->setEnabled(true);
}

//清算按钮的功能
void Home::on_finish_button_clicked()
{
    QSqlQuery query;
    double current_money = ui->money_edit->text().toDouble();
    //charge记录
    if(vipid != ""){
        query.prepare("insert into chargerecord (jobid,cdate,chargeamount,vipid) values (:a,:b,:c,:d)");
        query.bindValue(":a",jobid);
        query.bindValue(":b",QDate::currentDate());
        query.bindValue(":c",current_money*discount);
        query.bindValue(":d",vipid);
        query.exec();
    }else{
        query.prepare("insert into chargerecord (jobid,cdate,chargeamount) values (:a,:b,:c)");
        query.bindValue(":a",jobid);
        query.bindValue(":b",QDate::currentDate());
        query.bindValue(":c",current_money*discount);
        query.exec();
    }
    qDebug() << "vip:" << vipid;
    qDebug() << "state:" << state;
    //根据exp上一年到exp期间消费的金额是否满足要求更新卡的有效日期
    if(vipid != "" && state == 1){
        QDate exp_last = exp.addYears(-1);
        exp_last = exp_last.addDays(1);
        query.clear();
        query.prepare("select sum(monetary) from expenserecord where vipid = :a and edate >= :b and edate <= :c");
        query.bindValue(":a",vipid);
        query.bindValue(":b",exp_last);
        query.bindValue(":c",exp);
        query.exec();
        query.next();
        qDebug() << "消费总额!";
        qDebug() << query.value(1).toInt();
        if(query.value(0).toInt() >= canrenew){
            exp = exp.addYears(1);
            query.clear();
            query.prepare("update vip set exp = :a where vipid = :b");
            query.bindValue(":a",exp);
            query.bindValue(":b",vipid);
            query.exec();
        }
    }//并且根据本次的消费金额来决定是否送卡
    else if(vipid == ""){
        if(current_money >= 1000){
            QMessageBox message(QMessageBox::Warning,"提示","是否送卡",QMessageBox::Yes|QMessageBox::No,NULL);
            if (message.exec()==QMessageBox::Yes)
            {
                query.clear();
                query.prepare("select * from vip order by vipid DESC limit 1");
                query.exec();
                int last_vipid = 0;
                if(query.size() !=0){
                    query.next();
                    last_vipid = query.value(0).toInt();
                }
                last_vipid++;
                query.clear();
                query.prepare("insert into vip (vipid,expense,state,pd,exp) values (:a,:b,:c,:d,:e)");
                query.bindValue(":a",last_vipid);
                query.bindValue(":b",0);
                query.bindValue(":c",1);
                query.bindValue(":d",QDate::currentDate());
                query.bindValue(":e",QDate::currentDate().addYears(1));
                query.exec();
                QString mess = "卡号为"+QString::number(last_vipid);
                QMessageBox::critical(this,"办卡成功",mess);
            }
             else
             {
             }
        }
    }
    //后续处理工作
    vipid = "";
    ui->vipid->clear();
    money = 0;
    discount = 1;
    state = 3;
    money_this = 0;
    ui->money_edit->clear();
    ui->moneydiscount_edit->clear();
    ui->finish_button->setEnabled(false);
    ui->goodid->clear();
    ui->goodnumber->clear();
    ui->ok_vipid_button->setEnabled(true);
    ui->notok_vipid_button->setEnabled(false);
}

//办卡
void Home::on_becomevip_button_clicked()
{
    QSqlQuery query;
    query.prepare("select * from vip order by vipid DESC limit 1");
    query.exec();
    int last_vipid = 0;
    if(query.size() !=0){
        query.next();
        last_vipid = query.value(0).toString().toInt();
    }
    last_vipid++;
    query.clear();
    query.prepare("insert into vip (vipid,expense,state,pd) values (:a,:b,:c,:d)");
    query.bindValue(":a",last_vipid);
    query.bindValue(":b",0);
    query.bindValue(":c",0);
    query.bindValue(":d",QDate::currentDate());
    query.exec();
    QString mess = "卡号为"+QString::number(last_vipid);
    QMessageBox::critical(this,"办卡成功",mess);
}

//设置管理员界面，查看每一次收费的流水记录或者按照日期为单位的收取记录，进行商品信息的修改
//有点弱智的是，会员必须先说卡号才能进行优惠
