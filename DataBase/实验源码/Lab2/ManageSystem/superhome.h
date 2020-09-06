#ifndef SUPERHOME_H
#define SUPERHOME_H

#include <QMainWindow>

namespace Ui {
class superhome;
}

class superhome : public QMainWindow
{
    Q_OBJECT

public:
    explicit superhome(QWidget *parent = nullptr);
    ~superhome();

private:
    Ui::superhome *ui;
    QString superid;
public slots:
     void onsuperLogin(const QString &username,const QString &passwd);
signals:
     void superLogout();
private slots:
     void on_pushButton_clicked();
     void on_search_1_clicked();
     void on_search_3_clicked();
     void on_pushButton_17_clicked();
     void on_search_5_clicked();
     void on_serach_2_clicked();
     void on_search_4_clicked();
     void on_pushButton_18_clicked();
     void on_search_6_clicked();
     void on_pushButton_2_clicked();
     void on_pushButton_3_clicked();
     void on_pushButton_4_clicked();
     void on_pushButton_5_clicked();
     void on_pushButton_7_clicked();
     void on_pushButton_8_clicked();
     void on_pushButton_9_clicked();
     void on_pushButton_11_clicked();
     void on_pushButton_12_clicked();
     void on_pushButton_13_clicked();
     void on_pushButton_14_clicked();
     void on_pushButton_16_clicked();
};

#endif // SUPERHOME_H
