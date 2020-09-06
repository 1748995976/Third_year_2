#ifndef DBHELPER_H
#define DBHELPER_H
#include <QSqlDatabase>

//0：代表会员是永久有效的
//1：代表会员是有期限的
//2：代表会员已经失效

class DBHelper
{
public :
    static DBHelper *getInstance();
    void connectDatabase();
    void disconnectDatabase();
private:
    static DBHelper *instance;
    DBHelper();
    QSqlDatabase db;
};

#endif // DBHELPER_H
