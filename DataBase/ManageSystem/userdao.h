#ifndef USERDAO_H
#define USERDAO_H
#include <QSqlQuery>

class UserDao
{
public:
    UserDao();
    //虚函数，定义接口
    virtual QSqlQuery selectUserById(QString jobid) = 0;
    virtual QSqlQuery selectSuperById(QString superid) = 0;
    virtual ~UserDao();
};

#endif // USERDAO_H
