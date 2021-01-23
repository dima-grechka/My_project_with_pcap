#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    errbuf=new char[PCAP_ERRBUF_SIZE];
    if(pcap_findalldevs(&DeviceList,errbuf)==-1)
    {
        QMessageBox::warning(this,"ОШИБКА!","Устройства для осущесвления сниффинга не найдены!");
        exit(1);
    }

    pcap_if_t* List=DeviceList;
    while (List)
    {
        QString item;
        item=QString(List->description)+"  ["+QString(List->name)+"]";
        ui->listWidget->addItem(item);
        List=List->next;
    }
    pcap_freealldevs(List);
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_Button1_clicked()
{
   ui->listWidget_2->clear();
   errbuf1=new char[PCAP_ERRBUF_SIZE];
   device_name=ui->listWidget->item(ui->listWidget->currentRow())->text();
   ui->label2->setText(device_name);
   List1=DeviceList;
   int c=ui->listWidget->currentRow();
   for (int i = 0; i < c; ++i) {
       List1=List1->next;
   }
   handle=pcap_open_live(List1->name,65536,true,1000,errbuf1);
   if (handle==NULL)
   {
       QMessageBox::warning(this,"ОШИБКА!",errbuf1);
   }
   else {
      ui->listWidget_2->addItem("Устройство для сниффинга успешно открыто!");
   }


   if (pcap_datalink(handle)==DLT_EN10MB)
       ui->listWidget_2->addItem("Устройство работает на канальном уровне: Ethernet");

   bpf_u_int32 netmask;

   netmask=((struct sockaddr_in *)(List1->addresses->netmask))->sin_addr.S_un.S_addr;
   //netmask=0xffffff;

   if (pcap_compile(handle,&bf,"ip and tcp",1,netmask)>=0)
       ui->listWidget_2->addItem("Пакетный фильтр скомпилирован успешно!");

   if (pcap_setfilter(handle,&bf)==0)
       ui->listWidget_2->addItem("Пакетный фильтр успешно связан с захватом пакетов!");

}


void MainWindow::on_pushButton_clicked()
{
   int count=0;

   while (int k=pcap_next_ex(handle,&header,NULL)>=0 && count<5)
   {
    if (k==1)
    {
        ui->listWidget_3->addItem(QString::number(header->len));
        count++;
       continue;
    }
    if (k==0)
        ui->listWidget_3->addItem("0");
   }


}

