/*****************************************************************************/
/*
* \file clientwidget.cpp
* \author zxz
* \date 2022/10/24
* \version TINGSN V1
* \brief 建立用户聊天窗口，实现与商家对话的连接
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#include "clientwidget.h"
#include "ui_clientwidget.h"
#include "const.h"
#include <QHostAddress>
#include <QDebug>
#include <QKeyEvent>
#include <QIcon>
#include <QMessageBox>
#include <QString>
#include <QImage>
#include <QImageReader>
#include <QBuffer>


ClientWidget::ClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWidget)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("://ziyuan/yh.webp")); // 设置图标

    tcpSocket =NULL;
    isStart =true; // 判断是否开始发送
    isImg = false; // 判断是不是图片
    tcpSocket = new QTcpSocket(this); // 创建通信套接字对象
    move(CLIENT_X,CLIENT_Y);
    setWindowTitle("用户");
    // 成功连接后触发connected信号，接受该信号进行处理
    connect(tcpSocket,&QTcpSocket::connected,
            [=]()

    {
        ui->textEditRead->setText("成功和商家建立连接"); // 显示连接成功信息

    }
    );
    // 服务器发送信息后会触发readyRead，接收并对信息进行处理（文件或文字）
    connect(tcpSocket,&QTcpSocket::readyRead,
            [=]()
    {

         QByteArray buf = tcpSocket->readAll();
         if(QString(buf).contains("##",Qt::CaseSensitive) || isImg == true) // 如果是图片文件则进行图片显示处理
         {
         if(isStart == true)
         {
             isStart = false;
             isImg = true;
             fileName = QString(buf).section("##",0,0); // 将文件头信息（文件名称和文件大小）断开并分别接收
             fileSize = QString(buf).section("##",1,1).toInt();
             recvSize = ZERO; // 记录以结束的文件大小
             file.setFileName(fileName); // 装载文件名称

             bool isOk = file.open(QIODevice::WriteOnly); // 以只读方式打卡文件
             if(isOk == false)
             {
                 qDebug()<<"打开出错";
             }

         }
         else{
               qint64 len = file.write(buf); // 读取buf内容
               recvSize += len; // 累加大小
               inBlock  +=  buf; // 累加内容
               if(recvSize == fileSize) // 如果文件读完则进行处理
               {
                   // 用png方式打开文件，并显示到指定界面中
                   QBuffer buffer(&inBlock);
                   buffer.open(QIODevice::ReadOnly);
                   QImageReader reader(&buffer,"png");
                   QImage img = reader.read();
                   img = img.scaled(ui->label->size(),Qt::IgnoreAspectRatio);
                   ui->label->setPixmap(QPixmap::fromImage(img));
                   isImg = false;
                   file.close(); // 关闭文件
               }
         }
         }
         else
         {
             ui->textEditRead->append(buf); // 如果是文字则直接在读取区显示
         }

    }
    );
    ui->textEditWrite->installEventFilter(this);

}

ClientWidget::~ClientWidget()
{
    delete ui;
}
// 连接函数
void ClientWidget::Connect()
{
    //获取服务器ip和端口
    QString s_po ="1";
    QString s_ip = "127.0.0.1";
    qint16 s_port = s_po.toInt();

    tcpSocket->connectToHost(QHostAddress(s_ip),s_port); // 主动和服务器建立连接用本地IP和客户端端口（仅用于测试）

}
/*
void ClientWidget::on_pushButtonConnect_clicked()
{
    //获取服务器ip和端口
    QString ip =ui->lineEditIp->text();
    qint16 port = ui->lineEditPort->text().toInt();

    tcpSocket->connectToHost(QHostAddress(ip),port);
}
*/
// 获取编辑器内容
void ClientWidget::on_pushButtonSend_clicked()
{
    QString s_str ="用户:"+ ui->textEditWrite->toPlainText();
    tcpSocket->write(s_str.toUtf8().data()); // 将内容写入通信套接字，并触发readyRead信号
    ui->textEditRead->append(s_str); // 在读取区显示内容
    ui->textEditWrite->clear(); // 清空输入信息

}
/*
void ClientWidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
    {
        on_pushButtonSend_clicked();
    }
}*/
bool ClientWidget::eventFilter(QObject *target, QEvent *event)
 {
     if(target == ui->textEditWrite)
     {
         if(event->type() == QEvent::KeyPress)//回车键
         {
              QKeyEvent *k = static_cast<QKeyEvent *>(event);
              if(k->key() == Qt::Key_Return || k->key() == Qt::Key_Enter )
              {
                  on_pushButtonSend_clicked();
                  return true;
              }
         }
     }
     return QWidget::eventFilter(target,event);
 }

void ClientWidget::on_pushButtonClose_clicked()
{

    tcpSocket->disconnectFromHost();
    tcpSocket->close();
}

void ClientWidget::on_pushButton_clicked()
{
    close();
}

