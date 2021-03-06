﻿#include "dbhelper.h"
#include <QDebug>

DBHelper* DBHelper::instance = NULL;

DBHelper::DBHelper()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("shopcash");
    db.setPort(3306);
    db.setUserName("root");
    db.setPassword("3714231999");
}

void DBHelper::connectDatabase()
{
    bool ret = db.open();
    if(ret){
        qDebug() << "open db success!";
    }else{
        qDebug() << "open db failed!";
    }
}

void DBHelper::disconnectDatabase()
{
    db.close();
    db.removeDatabase("shopcash");
    delete instance;
    instance = NULL;
}

DBHelper* DBHelper::getInstance()
{
    if(instance == NULL){
        instance = new DBHelper();
        return instance;
    }else{
        return instance;
    }
}
