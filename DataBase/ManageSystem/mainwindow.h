#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "home.h"
#include "superhome.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void userLogin(const QString &username,const QString &passwd);

    void superLogin(const QString &username,const QString &passwd);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void onuserLogout();

    void onsuperLogout();


private:
    Ui::MainWindow *ui;
    Home* home;
    superhome *super_home;
};
#endif // MAINWINDOW_H
