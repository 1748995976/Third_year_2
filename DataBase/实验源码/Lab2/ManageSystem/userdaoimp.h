#ifndef USERDAOIMP_H
#define USERDAOIMP_H
#include "dbhelper.h"
#include "userdao.h"
#include <QSqlQuery>

class UserDaoImp:public UserDao
{
public:
    UserDaoImp();
    QSqlQuery selectUserById(QString jobid) override;
    QSqlQuery selectSuperById(QString superid) override;
};

#endif // USERDAOIMP_H
