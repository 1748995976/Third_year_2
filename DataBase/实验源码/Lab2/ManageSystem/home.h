#ifndef HOME_H
#define HOME_H

#include <QDate>
#include <QMainWindow>

namespace Ui {
class Home;
}

class Home : public QMainWindow
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr);
    ~Home();

private:
    Ui::Home *ui;
    QString jobid;
    QString vipid = "";
    double money = 0;
    double discount = 1;
    double money_this = 0;
    int state = 3;
    QDate exp;
    int canrenew = 500;

public slots:
     void onuserLogin(const QString &username,const QString &passwd);
signals:
     void userLogout();
private slots:
     void on_exit_Button_clicked();
     void on_ok_vipid_button_clicked();
     void on_notok_vipid_button_clicked();
     void on_wantbut_button_clicked();
     void on_finish_button_clicked();
     void on_becomevip_button_clicked();
};

#endif // HOME_H
