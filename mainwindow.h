#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <pcap.h>
#include <mythread.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QString device_name;
    ~MainWindow();

private slots:
    void on_Button1_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    pcap_if_t* DeviceList;
    pcap_if_t* List1;
    bpf_program bf;
    char* errbuf;
    char* errbuf1;
    pcap_t* handle;
    pcap_pkthdr* header;
};

#endif // MAINWINDOW_H
