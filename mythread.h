#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QThread>
#include "pcap.h"

class MyThread : public QThread
{
    Q_OBJECT
public:
    MyThread();
    void run();
};

#endif // MYTHREAD_H
