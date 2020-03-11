#include "pack.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

using std::string;
using std::ifstream;
using std::ios;
using std::cout;
using std::endl;
using std::to_string;

packfun::packfun()
{

}

packfun::~packfun(){

}



void packfun::read_cpuinfo(void){
    string filename = "/proc/cpuinfo";
    ifstream infile(filename);
    string line;
    if(!infile){
        cout << "No cpuinfo file!" << endl;
    }else{
        cout << "Read cpuinfo!" << endl;
        int count = 0;
        while (std::getline(infile,line)) {
            if (!line.size())
                continue;
            if(line.find("processor") != line.npos)
                count++;
            if(count != 1)
                continue;
            if(line.find("vendor_id") != line.npos
                    || line.find("cpu family") != line.npos
                    || line.find("model name") != line.npos
                    || line.find("cpu MHz") != line.npos
                    || line.find("cache size") != line.npos)
            {
                string::size_type position;
                if((position = line.find(9,0)) != line.npos)
                    line[position] = ' ';
                cout << line << endl;
                emit value_send(QString::fromStdString(line));
            }
        }
        cout << "Read cpuinfo finished!" << endl;
    }
    infile.close();
}

void packfun::read_hostname(void)
{
    string filename = "/proc/sys/kernel/hostname";
    ifstream infile(filename);
    string line;
    if(!infile){
        cout << "No hostinfo file!" << endl;
    }else{
        cout << "Read hostinfo!" << endl;
        while (std::getline(infile,line)) {
            if (!line.size())
                continue;
            string::size_type position;
            if((position = line.find(9,0)) != line.npos)
                line[position] = ' ';
            cout << line << endl;
            emit value_send_1(QString::fromStdString(line));
        }
        cout << "Read hostinfo finished!" << endl;
    }
    infile.close();
}

string packfun::read_uptime(void)
{
    string filename = "/proc/uptime";
    string timenow;
    ifstream infile(filename);
    if(!infile){
        cout << "No uptimeinfo file!" << endl;
        return "";
    }else{
        int count = 0;
        string line;
        if (infile >> count) {
            time_t tmp_time;
            struct tm *tmp;
            //获取当前时间
            tmp_time = time(NULL);
            tmp = localtime(&tmp_time);
            timenow = to_string(1900+tmp->tm_year) + "-"
                    + to_string(1+tmp->tm_mon) + "-"
                    + to_string(tmp->tm_mday) + " "
                    + to_string(tmp->tm_hour) + ":"
                    + to_string(tmp->tm_min) + ":"
                    + to_string(tmp->tm_sec);
            //求启动时间
            tmp_time -= count;
            tmp =  localtime(&tmp_time);
            line = "系统启动时间: "
                    + to_string(1900+tmp->tm_year) + "-"
                    + to_string(1+tmp->tm_mon) + "-"
                    + to_string(tmp->tm_mday) + " "
                    + to_string(tmp->tm_hour) + ":"
                    + to_string(tmp->tm_min) + ":"
                    + to_string(tmp->tm_sec);
            emit value_send_2(QString::fromStdString(line));
            line = "系统运行时间: "
                    + to_string(count/3600) + " h "
                    + to_string((count%3600)/60) + " min "
                    + to_string(count%60) + " s ";
            emit value_send_2(QString::fromStdString(line));
        }
        infile.close();
    }
    return timenow;
}

string packfun::read_ostype(void)
{
    string filename = "/proc/sys/kernel/ostype";
    ifstream infile(filename);
    string line;
    string allline = "";
    if(!infile){
        cout << "No ostypeinfo file!" << endl;
    }else{
        cout << "Read ostypeinfo!" << endl;
        while (std::getline(infile,line)) {
            if (!line.size())
                continue;
            string::size_type position;
            if((position = line.find(9,0)) != line.npos)
                line[position] = ' ';
            line = "系统类型: " + line;
            if(allline != "")
                allline = allline + "\n" + line;
            else
                allline += line;
            emit value_send_2(QString::fromStdString(line));
        }
        cout << "Read ostypeinfo finished!" << endl;
        infile.close();
    }
    return allline;
}

string packfun::read_osrelease(void)
{
    string filename = "/proc/sys/kernel/osrelease";
    ifstream infile(filename);
    string line;
    string allline = "";
    if(!infile){
        cout << "No osreleaseinfo file!" << endl;
    }else{
        cout << "Read osreleaseinfo!" << endl;
        while (std::getline(infile,line)) {
            if (!line.size())
                continue;
            string::size_type position;
            if((position = line.find(9,0)) != line.npos)
                line[position] = ' ';
            line = "系统版本: " + line;
            if(allline != "")
                allline = allline + "\n" + line;
            else
                allline += line;
            emit value_send_2(QString::fromStdString(line));
        }
        cout << "Read osreleaseinfo finished!" << endl;
        infile.close();
    }
    return allline;
}

int packfun::read_processinfo(void)
{
    //打开目录
    DIR *dir;
    int fd;
    struct dirent *ptr;
    char filename[256];
    char info[1024];
    string line;

    string process_status;
    char pid[10];
    char ppid[10];
    char process_name[50];
    char memo_size[20];
    char noneed[20];
    char allinfo[100];
    char status;
    int nice;
    int priority;
    long int utime, stime, cutime, cstime;
    long int page;

    if (!(dir = opendir("/proc")))
        return 0;

    //读取目录
    while (ptr = readdir(dir))//某些隐藏目录无法读取
    {//循环读取出所有的进程文件
        if (ptr->d_name[0] > '0' && ptr->d_name[0] <= '9')
        {
            // 生成文件名
            sprintf(filename, "/proc/%s/stat", ptr->d_name);
            fd = open(filename, O_RDONLY); //只读打开
            read(fd, info, sizeof(info));
            close(fd);
            sscanf(info, "%s %s %c %s %s %s %s %s %s %s %s %s %s %ld %ld %ld %ld %d %d %s %s %s %s %ld",
                   pid, process_name, &status, ppid, noneed, noneed, noneed, noneed, noneed, noneed,
                   noneed, noneed, noneed, &utime, &stime, &cutime, &cstime, &priority,
                   &nice, noneed, noneed, noneed, noneed, &page);
            if (status == 'S')
                process_status = "sleep";
            else if (status == 'R')
                process_status = "running";
            else if (status == 'T')
                process_status = "stoped";
            else if (status == 'D')
                process_status = "noninterrupt";
            else if (status == 'Z')
                process_status = "deadlock";
            else if (status == 'X')
                process_status = "dead";
            else
                process_status = "unknown";
            sprintf(memo_size, "%.2fM", (float)(page * getpagesize() / 1024.0 / 1024.0));

            sprintf(allinfo,"%-6s%-20s%-9s%-13s%-7d%-8s",pid,process_name,ppid,process_status.c_str(),priority,memo_size);

            line = (string)allinfo;
            emit value_send_3(QString::fromStdString(line));
            //            sprintf(allinfo,"pid: %s\n"
            //                            "processname: %s\n"
            //                            "ppid: %s\n"
            //                            "processstatus: %s\n"
            //                            "priority: %d\n"
            //                            "memosize: %s\n",pid,process_name,ppid,process_status.c_str(),priority,memo_size);
            //            cout << allinfo << endl;
        }
    }
    return 1;
}

string packfun::read_assignpid(string number)
{
    string filename = "/proc/" + number + "/stat";
    int fd = open(filename.c_str(), O_RDONLY); //只读打开
    string line;

    char info[1024];
    string process_status;
    char pid[10];
    char ppid[10];
    char process_name[50];
    char memo_size[20];
    char noneed[20];
    char allinfo[100];
    char status;
    int nice;
    int priority;
    long int utime, stime, cutime, cstime;
    long int page;

    if(fd == -1){
        cout << "No assignprocess file!" << endl;
        return "";
    }else{
        read(fd, info, sizeof(info));
        close(fd);
        sscanf(info, "%s %s %c %s %s %s %s %s %s %s %s %s %s %ld %ld %ld %ld %d %d %s %s %s %s %ld",
               pid, process_name, &status, ppid, noneed, noneed, noneed, noneed, noneed, noneed,
               noneed, noneed, noneed, &utime, &stime, &cutime, &cstime, &priority,
               &nice, noneed, noneed, noneed, noneed, &page);
        if (status == 'S')
            process_status = "sleep";
        else if (status == 'R')
            process_status = "running";
        else if (status == 'T')
            process_status = "stoped";
        else if (status == 'D')
            process_status = "noninterrupt";
        else if (status == 'Z')
            process_status = "deadlock";
        else if (status == 'X')
            process_status = "dead";
        else
            process_status = "unknown";
        sprintf(memo_size, "%.2fM", (float)(page * getpagesize() / 1024.0 / 1024.0));
        sprintf(allinfo,"%-6s%-20s%-9s%-13s%-7d",pid,process_name,ppid,process_status.c_str(),priority);
        line = (string)allinfo;
        cout << line << endl;
        return line;
    }
}

double packfun::read_cpu_use(void)
{
    string filename = "/proc/stat";
    char info[1024];
    char noneed[10];
    int fd = open(filename.c_str(), O_RDONLY); //只读打开
    read(fd, info, sizeof(info));
    close(fd);
    sscanf(info,"%s%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld",noneed,
           &cpuusge.user,&cpuusge.nice,&cpuusge.system,
           &cpuusge.idle,&cpuusge.iowait,&cpuusge.irq,
           &cpuusge.softirq,&cpuusge.steal,&cpuusge.guest,
           &cpuusge.guest_nice);
    long alltime_1 = cpuusge.user+cpuusge.nice+cpuusge.system+cpuusge.idle+cpuusge.iowait+cpuusge.irq+cpuusge.softirq;
    long idle_1 = cpuusge.idle;
    sleep(1);//第二次采样
    fd = open(filename.c_str(), O_RDONLY); //只读打开
    read(fd, info, sizeof(info));
    close(fd);
    sscanf(info,"%s%ld %ld %ld %ld %ld %ld %ld %ld %ld %ld",noneed,
           &cpuusge.user,&cpuusge.nice,&cpuusge.system,
           &cpuusge.idle,&cpuusge.iowait,&cpuusge.irq,
           &cpuusge.softirq,&cpuusge.steal,&cpuusge.guest,
           &cpuusge.guest_nice);
    long alltime_2 = cpuusge.user+cpuusge.nice+cpuusge.system+cpuusge.idle+cpuusge.iowait+cpuusge.irq+cpuusge.softirq;
    long idle_2 = cpuusge.idle;
    long alltime_sub = alltime_1 - alltime_2;
    long idle_sub = idle_1 - idle_2;
    double usage = ((double)(alltime_sub - idle_sub))/((double)alltime_sub);
    usage *= 100;
    return usage;
}

double packfun::read_mem_use(void)
{
    string filename = "/proc/meminfo";
    char info[1024];
    char noneed[10];
    int fd = open(filename.c_str(), O_RDONLY); //只读打开
    read(fd, info, sizeof(info));
    close(fd);
    sscanf(info,"%s %ld %s %s %ld %s %s %ld %s %s %ld %s %s %ld %s",
           noneed,&memusge.memtotal,noneed,
           noneed,&memusge.memfree,noneed,
           noneed,noneed,noneed,
           noneed,&memusge.buffers,noneed,
           noneed,&memusge.cached,noneed);
    double usage = (double)(memusge.memtotal-memusge.memfree-memusge.buffers-memusge.cached)/(double)memusge.memtotal;
    usage *= 100;
    return usage;
}

