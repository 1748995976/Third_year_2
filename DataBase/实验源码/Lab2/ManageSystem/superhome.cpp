#include "superhome.h"
#include "ui_superhome.h"
#include "dbhelper.h"

#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlQueryModel>

superhome::superhome(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::superhome)
{
    ui->setupUi(this);
}

superhome::~superhome()
{
    delete ui;
}

void superhome::onsuperLogin(const QString &username,const QString &passwd){
    superid = username;
}

void superhome::on_pushButton_clicked()
{
    DBHelper *helper = DBHelper::getInstance();
    helper->disconnectDatabase();
    emit superLogout();
}

void superhome::on_search_1_clicked()
{
    if(ui->search_id->text().isEmpty()){
        QMessageBox::critical(this,"警告","收银员ID/会员ID不允许为空");
        return;
    }

    QString tmp1 = ui->search_id->text();
    QString tmp2 = ui->search_date->text();
    QSqlQuery query;
    //准备SQL语句
    query.prepare("select * from chargerecord where jobid = :jobid and cdate = :cdate");
    query.bindValue(":jobid",tmp1);
    query.bindValue(":cdate",tmp2);
    bool ret = query.exec();

     int size = query.size();
     if(size == 0){
         QMessageBox::critical(this,"提示","查询无果");
         return;
     }
    if(ret){
        QSqlQueryModel* model = new QSqlQueryModel();
        model->setQuery(query);
        ui->tavleview_1->setModel(model);
        ui->tavleview_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
}

void superhome::on_search_3_clicked()
{
    QString tmp2 = ui->search_date->text();
    QSqlQuery query;
    //准备SQL语句
    query.prepare("select * from chargerecord where cdate = :cdate");
    query.bindValue(":cdate",tmp2);
    bool ret = query.exec();

     int size = query.size();
     if(size == 0){
         QMessageBox::critical(this,"提示","查询无果");
         return;
     }
    if(ret){
        QSqlQueryModel* model = new QSqlQueryModel();
        model->setQuery(query);
        ui->tavleview_1->setModel(model);
        ui->tavleview_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
}

void superhome::on_pushButton_17_clicked()
{
    if(ui->search_id->text().isEmpty()){
        QMessageBox::critical(this,"警告","收银员ID/会员ID不允许为空");
        return;
    }

    QString tmp1 = ui->search_id->text();
    QSqlQuery query;
    //准备SQL语句
    query.prepare("select * from chargerecord where jobid = :jobid");
    query.bindValue(":jobid",tmp1);
    bool ret = query.exec();

     int size = query.size();
     if(size == 0){
         QMessageBox::critical(this,"提示","查询无果");
         return;
     }
    if(ret){
        QSqlQueryModel* model = new QSqlQueryModel();
        model->setQuery(query);
        ui->tavleview_1->setModel(model);
        ui->tavleview_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
}

void superhome::on_search_5_clicked()
{
    QString tmp1 = ui->search_id->text();
    QSqlQuery query;
    //准备SQL语句
    query.prepare("select * from chargerecord");
    bool ret = query.exec();

     int size = query.size();
     if(size == 0){
         QMessageBox::critical(this,"提示","查询无果");
         return;
     }
    if(ret){
        QSqlQueryModel* model = new QSqlQueryModel();
        model->setQuery(query);
        ui->tavleview_1->setModel(model);
        ui->tavleview_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
}

void superhome::on_serach_2_clicked()
{
    if(ui->search_id->text().isEmpty()){
        QMessageBox::critical(this,"警告","收银员ID/会员ID不允许为空");
        return;
    }

    QString tmp1 = ui->search_id->text();
    QString tmp2 = ui->search_date->text();
    QSqlQuery query;
    //准备SQL语句
    query.prepare("select * from expenserecord where vipid = :vipid and edate = :edate");
    query.bindValue(":vipid",tmp1);
    query.bindValue(":edate",tmp2);
    bool ret = query.exec();

     int size = query.size();
     if(size == 0){
         QMessageBox::critical(this,"提示","查询无果");
         return;
     }
    if(ret){
        QSqlQueryModel* model = new QSqlQueryModel();
        model->setQuery(query);
        ui->tavleview_1->setModel(model);
        ui->tavleview_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
}

void superhome::on_search_4_clicked()
{
    QString tmp2 = ui->search_date->text();
    QSqlQuery query;
    //准备SQL语句
    query.prepare("select * from expenserecord where edate = :edate");
    query.bindValue(":edate",tmp2);
    bool ret = query.exec();

     int size = query.size();
     if(size == 0){
         QMessageBox::critical(this,"提示","查询无果");
         return;
     }
    if(ret){
        QSqlQueryModel* model = new QSqlQueryModel();
        model->setQuery(query);
        ui->tavleview_1->setModel(model);
        ui->tavleview_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
}

void superhome::on_pushButton_18_clicked()
{
    if(ui->search_id->text().isEmpty()){
        QMessageBox::critical(this,"警告","收银员ID/会员ID不允许为空");
        return;
    }

    QString tmp1 = ui->search_id->text();
    QSqlQuery query;
    //准备SQL语句
    query.prepare("select * from expenserecord where vipid = :vipid");
    query.bindValue(":vipid",tmp1);
    bool ret = query.exec();

     int size = query.size();
     if(size == 0){
         QMessageBox::critical(this,"提示","查询无果");
         return;
     }
    if(ret){
        QSqlQueryModel* model = new QSqlQueryModel();
        model->setQuery(query);
        ui->tavleview_1->setModel(model);
        ui->tavleview_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
}

void superhome::on_search_6_clicked()
{
    QSqlQuery query;
    //准备SQL语句
    query.prepare("select * from expenserecord");
    bool ret = query.exec();

     int size = query.size();
     if(size == 0){
         QMessageBox::critical(this,"提示","查询无果");
         return;
     }
    if(ret){
        QSqlQueryModel* model = new QSqlQueryModel();
        model->setQuery(query);
        ui->tavleview_1->setModel(model);
        ui->tavleview_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
}

void superhome::on_pushButton_2_clicked()
{
    if(ui->lineEdit_2->text().isEmpty()){
        QSqlQuery query;
        //准备SQL语句
        query.prepare("select * from goods");
        bool ret = query.exec();

         int size = query.size();
         if(size == 0){
             QMessageBox::critical(this,"提示","查询无果");
             return;
         }
        if(ret){
            QSqlQueryModel* model = new QSqlQueryModel();
            model->setQuery(query);
            ui->tableView->setModel(model);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
        return;
    }else{
        QString tmp1 = ui->lineEdit_2->text();
        QSqlQuery query;
        //准备SQL语句
        query.prepare("select * from goods where productcode = :productcode");
        query.bindValue(":productcode",tmp1);
        bool ret = query.exec();

        int size = query.size();
        if(size == 0){
            QMessageBox::critical(this,"提示","查询无果");
            return;
        }
        if(ret){
            QSqlQueryModel* model = new QSqlQueryModel();
            model->setQuery(query);
            ui->tableView->setModel(model);
            ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
    }
}

void superhome::on_pushButton_3_clicked()
{
    if(ui->lineEdit_2->text().isEmpty() || ui->lineEdit_3->text().isEmpty() || ui->lineEdit_4->text().isEmpty() || ui->lineEdit_5->text().isEmpty()){
        QMessageBox::critical(this,"警告","商品所有信息不允许为空");
        return;
    }

    QString tmp1 = ui->lineEdit_2->text();
    QString tmp2 = ui->lineEdit_3->text();
    QString tmp3 = ui->lineEdit_4->text();
    QString tmp4 = ui->lineEdit_5->text();
    QSqlQuery query;
    //准备SQL语句
    query.prepare("select * from goods where productcode = :productcode");
    query.bindValue(":productcode",tmp1);
    query.exec();

     int size = query.size();
     if(size == 0){
         QMessageBox::critical(this,"警告","货品不存在");
         return;
     }
     query.clear();
     query.prepare("update goods set remainingnumber = :a,price = :b,ganme = :c where productcode = :d");
     query.bindValue(":a",tmp2);
     query.bindValue(":b",tmp3);
     query.bindValue(":c",tmp4);
     query.bindValue(":d",tmp1);
     int ret = query.exec();
     if(ret){
         QMessageBox::critical(this,"提示","操作成功");
         return;
     }else{
         QMessageBox::critical(this,"提示","操作失败");
         return;
     }
}

void superhome::on_pushButton_4_clicked()
{
    if(ui->lineEdit_2->text().isEmpty() || ui->lineEdit_3->text().isEmpty() || ui->lineEdit_4->text().isEmpty() || ui->lineEdit_5->text().isEmpty()){
        QMessageBox::critical(this,"警告","商品所有信息不允许为空");
        return;
    }

    QString tmp1 = ui->lineEdit_2->text();
    QString tmp2 = ui->lineEdit_3->text();
    QString tmp3 = ui->lineEdit_4->text();
    QString tmp4 = ui->lineEdit_5->text();
    QSqlQuery query;
    //准备SQL语句
    query.prepare("select * from goods where productcode = :productcode");
    query.bindValue(":productcode",tmp1);
    query.exec();

     int size = query.size();
     if(size != 0){
         QMessageBox::critical(this,"警告","货品号不允许重复");
         return;
     }
     query.clear();
     query.prepare("insert into goods (productcode,remainingnumber,price,ganme) values (:a,:b,:c,:d)");
     query.bindValue(":a",tmp1);
     query.bindValue(":b",tmp2);
     query.bindValue(":c",tmp3);
     query.bindValue(":d",tmp4);
     int ret = query.exec();
     if(ret){
         QMessageBox::critical(this,"提示","操作成功");
         return;
     }else{
         QMessageBox::critical(this,"提示","操作失败");
         return;
     }
}

void superhome::on_pushButton_5_clicked()
{
    if(ui->lineEdit_2->text().isEmpty()){
        QMessageBox::critical(this,"警告","货品号不允许为空");
        return;
    }

    QString tmp1 = ui->lineEdit_2->text();
    QSqlQuery query;
    //准备SQL语句
    query.prepare("select * from goods where productcode = :productcode");
    query.bindValue(":productcode",tmp1);
    query.exec();

     int size = query.size();
     if(size == 0){
         QMessageBox::critical(this,"警告","货品不存在");
         return;
     }
     query.clear();
     query.prepare("delete from goods where productcode = :a");
     query.bindValue(":a",tmp1);
     int ret = query.exec();
     if(ret){
         QMessageBox::critical(this,"提示","操作成功");
         return;
     }else{
         QMessageBox::critical(this,"提示","操作失败");
         return;
     }
}

void superhome::on_pushButton_7_clicked()
{
    if(ui->lineEdit->text().isEmpty()){
        QSqlQuery query;
        //准备SQL语句
        query.prepare("select * from employee");
        bool ret = query.exec();

         int size = query.size();
         if(size == 0){
             QMessageBox::critical(this,"提示","查询无果");
             return;
         }
        if(ret){
            QSqlQueryModel* model = new QSqlQueryModel();
            model->setQuery(query);
            ui->tableView_2->setModel(model);
            ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
        return;
    }else{
        QString tmp1 = ui->lineEdit->text();
        QSqlQuery query;
        //准备SQL语句
        query.prepare("select * from employee where jobid = :jobid");
        query.bindValue(":jobid",tmp1);
        bool ret = query.exec();

        int size = query.size();
        if(size == 0){
            QMessageBox::critical(this,"提示","查询无果");
            return;
        }
        if(ret){
            QSqlQueryModel* model = new QSqlQueryModel();
            model->setQuery(query);
            ui->tableView_2->setModel(model);
            ui->tableView_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
    }
}

void superhome::on_pushButton_8_clicked()
{
    if(ui->lineEdit->text().isEmpty() || ui->lineEdit_6->text().isEmpty() || ui->lineEdit_7->text().isEmpty() || ui->lineEdit_8->text().isEmpty()){
        QMessageBox::critical(this,"警告","收银员所有信息不允许为空");
        return;
    }

    QString tmp1 = ui->lineEdit->text();
    QString tmp2 = ui->lineEdit_6->text();
    QString tmp3 = ui->lineEdit_7->text();
    QString tmp4 = ui->lineEdit_8->text();
    QSqlQuery query;
    //准备SQL语句
    query.prepare("select * from employee where jobid = :jobid");
    query.bindValue(":jobid",tmp1);
    query.exec();

     int size = query.size();
     if(size == 0){
         QMessageBox::critical(this,"警告","收银员不存在");
         return;
     }
     query.clear();
     query.prepare("update employee set ename = :a,phone = :b,passwd = :c where jobid = :d");
     query.bindValue(":a",tmp2);
     query.bindValue(":b",tmp3);
     query.bindValue(":c",tmp4);
     query.bindValue(":d",tmp1);
     int ret = query.exec();
     if(ret){
         QMessageBox::critical(this,"提示","操作成功");
         return;
     }else{
         QMessageBox::critical(this,"提示","操作失败");
         return;
     }
}

void superhome::on_pushButton_9_clicked()
{
    if(ui->lineEdit->text().isEmpty() || ui->lineEdit_6->text().isEmpty() || ui->lineEdit_7->text().isEmpty() || ui->lineEdit_8->text().isEmpty()){
        QMessageBox::critical(this,"警告","收银员所有信息不允许为空");
        return;
    }

    QString tmp1 = ui->lineEdit->text();
    QString tmp2 = ui->lineEdit_6->text();
    QString tmp3 = ui->lineEdit_7->text();
    QString tmp4 = ui->lineEdit_8->text();
    QSqlQuery query;
    //准备SQL语句
    query.prepare("select * from employee where jobid = :jobid");
    query.bindValue(":jobid",tmp1);
    query.exec();

     int size = query.size();
     if(size != 0){
         QMessageBox::critical(this,"警告","收银员ID号不允许重复");
         return;
     }
     query.clear();
     query.prepare("insert into employee (jobid,ename,phone ,passwd) values(:a,:b,:c,:d)");
     query.bindValue(":a",tmp1);
     query.bindValue(":b",tmp2);
     query.bindValue(":c",tmp3);
     query.bindValue(":d",tmp4);
     int ret = query.exec();
     if(ret){
         QMessageBox::critical(this,"提示","操作成功");
         return;
     }else{
         QMessageBox::critical(this,"提示","操作失败");
         return;
     }
}

void superhome::on_pushButton_11_clicked()
{
    QString tmp1 = ui->lineEdit->text();
    QSqlQuery query;
    //准备SQL语句
    query.prepare("select * from employee where jobid = :jobid");
    query.bindValue(":jobid",tmp1);
    query.exec();

     int size = query.size();
     if(size == 0){
         QMessageBox::critical(this,"警告","收银员ID号不存在");
         return;
     }
     query.clear();
     query.prepare("delete from employee where jobid = :a");
     query.bindValue(":a",tmp1);
     int ret = query.exec();
     if(ret){
         QMessageBox::critical(this,"提示","操作成功");
         return;
     }else{
         QMessageBox::critical(this,"提示","操作失败");
         return;
     }
}

void superhome::on_pushButton_12_clicked()
{
    if(ui->lineEdit_9->text().isEmpty()){
        QSqlQuery query;
        //准备SQL语句
        query.prepare("select * from vip");
        bool ret = query.exec();

         int size = query.size();
         if(size == 0){
             QMessageBox::critical(this,"提示","查询无果");
             return;
         }
        if(ret){
            QSqlQueryModel* model = new QSqlQueryModel();
            model->setQuery(query);
            ui->tableView_3->setModel(model);
            ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
        return;
    }else{
        QString tmp1 = ui->lineEdit_9->text();
        QSqlQuery query;
        //准备SQL语句
        query.prepare("select * from vip where vipid = :vipid");
        query.bindValue(":vipid",tmp1);
        bool ret = query.exec();

        int size = query.size();
        if(size == 0){
            QMessageBox::critical(this,"提示","查询无果");
            return;
        }
        if(ret){
            QSqlQueryModel* model = new QSqlQueryModel();
            model->setQuery(query);
            ui->tableView_3->setModel(model);
            ui->tableView_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        }
    }
}

void superhome::on_pushButton_13_clicked()
{
    if(ui->lineEdit_9->text().isEmpty() || ui->lineEdit_10->text().isEmpty() || ui->lineEdit_11->text().isEmpty()){
        QMessageBox::critical(this,"警告","会员所有信息不允许为空");
        return;
    }

    QString tmp1 = ui->lineEdit_9->text();
    QString tmp2 = ui->lineEdit_10->text();
    QString tmp3 = ui->lineEdit_11->text();
    QString tmp4 = ui->dateEdit->text();
    QString tmp5 = ui->dateEdit_2->text();
    QSqlQuery query;
    //准备SQL语句
    query.prepare("select * from vip where vipid = :vipid");
    query.bindValue(":vipid",tmp1);
    query.exec();

     int size = query.size();
     if(size == 0){
         QMessageBox::critical(this,"警告","会员不存在");
         return;
     }
     query.clear();
     if(tmp3.toInt() != 0 && tmp3.toInt() != 1 && tmp3.toInt() != 2){
         QMessageBox::critical(this,"警告","会员状态不合法");
         return;
     }else if(tmp3.toInt() == 0){
        query.prepare("update vip set expense = :a,state = :b where vipid = :d");
        query.bindValue(":a",tmp2);
        query.bindValue(":b",tmp3);
        query.bindValue(":d",tmp1);
     }else{
         query.prepare("update vip set expense = :a,state = :b,pd = :c,exp = :d where vipid = :e");
         query.bindValue(":a",tmp2);
         query.bindValue(":b",tmp3);
         query.bindValue(":c",tmp4);
         query.bindValue(":d",tmp5);
         query.bindValue(":e",tmp1);
     }
     int ret = query.exec();
     if(ret){
         QMessageBox::critical(this,"提示","操作成功");
         return;
     }else{
         QMessageBox::critical(this,"提示","操作失败");
         return;
     }
}

void superhome::on_pushButton_14_clicked()
{
    if(ui->lineEdit_9->text().isEmpty() || ui->lineEdit_10->text().isEmpty() || ui->lineEdit_11->text().isEmpty()){
        QMessageBox::critical(this,"警告","会员所有信息不允许为空");
        return;
    }

    QString tmp1 = ui->lineEdit_9->text();
    QString tmp2 = ui->lineEdit_10->text();
    QString tmp3 = ui->lineEdit_11->text();
    QString tmp4 = ui->dateEdit->text();
    QString tmp5 = ui->dateEdit_2->text();
    QSqlQuery query;
    //准备SQL语句
    query.prepare("select * from vip where vipid = :vipid");
    query.bindValue(":vipid",tmp1);
    query.exec();

     int size = query.size();
     if(size != 0){
         QMessageBox::critical(this,"警告","会员不允许重复");
         return;
     }
     query.clear();
     if(tmp3.toInt() != 0 && tmp3.toInt() != 1 && tmp3.toInt() != 2){
         QMessageBox::critical(this,"警告","会员状态不合法");
         return;
     }else if(tmp3.toInt() == 0){
        query.prepare("insert into vip (vipid,expense,state,pd) values(:a,:b,:c,:d)");
        query.bindValue(":a",tmp1);
        query.bindValue(":b",tmp2);
        query.bindValue(":c",tmp3);
        query.bindValue(":d",tmp4);
     }else{
         query.prepare("insert into vip (vipid,expense,state,pd,exp) values(:a,:b,:c,:d,:e)");
         query.bindValue(":a",tmp1);
         query.bindValue(":b",tmp2);
         query.bindValue(":c",tmp3);
         query.bindValue(":d",tmp4);
         query.bindValue(":e",tmp5);
     }
     int ret = query.exec();
     if(ret){
         QMessageBox::critical(this,"提示","操作成功");
         return;
     }else{
         QMessageBox::critical(this,"提示","操作失败");
         return;
     }
}

void superhome::on_pushButton_16_clicked()
{
    if(ui->lineEdit_9->text().isEmpty()){
        QMessageBox::critical(this,"警告","会员号不允许为空");
        return;
    }

    QString tmp1 = ui->lineEdit_9->text();
    QSqlQuery query;
    //准备SQL语句
    query.prepare("select * from vip where vipid = :vipid");
    query.bindValue(":vipid",tmp1);
    query.exec();

     int size = query.size();
     if(size == 0){
         QMessageBox::critical(this,"警告","会员不存在");
         return;
     }
     query.clear();
     query.prepare("delete from vip where vipid = :a");
     query.bindValue(":a",tmp1);
     int ret = query.exec();
     if(ret){
         QMessageBox::critical(this,"提示","操作成功");
         return;
     }else{
         QMessageBox::critical(this,"提示","操作失败");
         return;
     }
}
