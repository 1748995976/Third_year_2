#ifndef PACK_H
#define PACK_H

#include <QObject>
#include <string>

using std::string;

struct cpu_use
{
    long user = 0,nice = 0,system = 0,idle = 0,iowait = 0,irq = 0,softirq = 0,steal = 0,guest = 0,guest_nice = 0;
};

struct mem_use
{
    long memtotal = 0,memfree = 0,buffers = 0,cached = 0;
};

class packfun:public QObject
{
    Q_OBJECT
public:
    packfun();
    ~packfun();
    void read_cpuinfo(void);
    void read_hostname(void);
    string read_uptime(void);
    string read_ostype(void);
    string read_osrelease(void);
    int read_processinfo(void);
    string read_assignpid(string number);
    double read_cpu_use(void);
    double read_mem_use(void);

signals: //信号
    void value_send(QString value);//cpuinfo
signals: //信号
    void value_send_1(QString value);//host
signals: //信号
    void value_send_2(QString value);//uptime and system
signals: //信号
    void value_send_3(QString value);//processinfo
private:
    cpu_use cpuusge;
private:
    mem_use memusge;
};

#endif // PACK_H
