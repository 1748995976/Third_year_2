#include "userdaoimp.h"
#include "ui_mainwindow.h"

UserDaoImp::UserDaoImp()
{

}
//根据收银员id在数据库中查询
QSqlQuery UserDaoImp::selectUserById(QString jobid)
{
    DBHelper *helper = DBHelper::getInstance();
    QSqlQuery query;
    helper->connectDatabase();

    //准备SQL语句
    query.prepare("select * from employee where jobid = :jobid");
    query.bindValue(":jobid",jobid);

    query.exec();
    helper->disconnectDatabase();

    return query;
}

QSqlQuery UserDaoImp::selectSuperById(QString superid){
    DBHelper *helper = DBHelper::getInstance();
    QSqlQuery query;
    helper->connectDatabase();

    //准备SQL语句
    query.prepare("select * from super where superid = :superid");
    query.bindValue(":superid",superid);

    query.exec();
    helper->disconnectDatabase();

    return query;
}
