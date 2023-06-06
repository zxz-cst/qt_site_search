/*****************************************************************************/
/*
* \file canteenwidget.cpp
* \author zxz
* \date 2022/10/18
* \version TINGSN V1
* \brief 建立商家聊天窗口，实现与用户的连接
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#include "canteenwidget.h"
#include "ui_canteenwidget.h"
#include "const.h"
#include <QKeyEvent>
#include <QIcon>
#include <QFileDialog>
#include <QString>
#include <QDebug>
#include <QFileInfo>

CanteenWidget::CanteenWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CanteenWidget)
{
    setWindowIcon(QIcon("://ziyuan/sj.webp"));
    ui->setupUi(this);
    tcpServer = NULL;
    tcpSocket = NULL;
    tcpServer = new QTcpServer(this); // 创建监听套接字对象
    tcpServer->listen(QHostAddress::Any,1); // 设置监听套接字 绑定当前网卡的所有IP，端口设为1（客户端用来找）

    move(CANTEEN_X,CANTEEN_Y); // 将窗口移动到指定位置
    setWindowTitle("商家");

    // 两个按钮都不能按，为发送文件做准备
    ui->buttonFile->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    // 客户端连接时会服务段发送一个newConnection的信号，检测到该信号后开始处理
    connect(tcpServer,&QTcpServer::newConnection,
            [=]()
           {
           tcpSocket = tcpServer->nextPendingConnection(); // 取出建立好连接的套接字
           QString ip =tcpSocket->peerAddress().toString(); // 获取客户端IP
           qint16 port = tcpSocket->peerPort(); // 获取客户端端口
           QString temp = QString("与用户:[%1:%2]:连接成功").arg(ip).arg(port); // 拼接字符串显示连接成功
           ui->textEditRead->setText(temp); // 在文本区显示

           // 成功连接后可以选择文件
           ui->buttonFile->setEnabled(true);
           // 接受客户端的信息。在对方发信息后会触发readyRead
           connect(tcpSocket,&QTcpSocket::readyRead,

                   [=]()
           {
                   QByteArray array = tcpSocket->readAll(); // 将套接字中内容全部取出
                   ui->textEditRead->append(array); // 在读取区显示
           }
                   );
            }

            );
    ui->textEditWrite->installEventFilter(this);
    connect(&timer,&QTimer::timeout,
            [=]()
    {
            timer.stop();
            sendDate();
    }
            );

}

CanteenWidget::~CanteenWidget()
{
    delete ui;
}

void CanteenWidget::on_buttonSend_clicked()
{
    //获取编辑区内容
    if(tcpSocket == NULL) // 无客户连接不需要读取
    {
        return;
    }
    QString str ="商家:"+ ui->textEditWrite->toPlainText(); // 获取编辑器输入的内容
    tcpSocket->write(str.toUtf8().data()); // 向套接字中写入该内容，给客户端发送数据
    ui->textEditRead->append(str); // 在读取区显示发送的内容
    ui->textEditWrite->clear(); // 发送后把输入区清空

}

bool CanteenWidget::eventFilter(QObject *target, QEvent *event)
 {
     if(target == ui->textEditWrite)
     {
         if(event->type() == QEvent::KeyPress)//回车键
         {
              QKeyEvent *k = static_cast<QKeyEvent *>(event);
              if(k->key() == Qt::Key_Return || k->key() == Qt::Key_Enter )
              {
                  on_buttonSend_clicked();
                  return true;
              }
         }
     }
     return QWidget::eventFilter(target,event);
 }

void CanteenWidget::on_buttonClose_clicked()
{
    if(tcpSocket == NULL)
    {
        return;
    }
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    delete tcpSocket;
    tcpSocket = NULL;
}

void CanteenWidget::on_pushButton_clicked()
{
    close();
}

// 选择文件按钮
void CanteenWidget::on_buttonFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this,"open","../");
    // 如果选择文件路径有效
    if(filePath.isEmpty() == false)
    {
        fileName.clear();
        fileSize = ZERO;

        // 获取文件信息
        QFileInfo info(filePath);
        fileName = info.fileName(); // 记录文件名称
        fileSize = info.size(); // 记录文件大小
        sendSize = ZERO; // 记录以发送文件大小

        // 只读方式打开文件
        file.setFileName(filePath);
        // 打开文件
        bool isOK = file.open(QIODevice::ReadOnly);
        if(isOK == false)
        {
            qDebug()<<"只读打开方式失败";
        }
        // 提示打开路径
        ui->textEditRead->append(filePath); // 显示打开路径
        ui->buttonFile->setEnabled(false);
        ui->pushButton_3->setEnabled(true);
    }
    else {
       qDebug()<<"选择文件路径出错";
    }
}

void CanteenWidget::on_pushButton_3_clicked()
{
    // 先发送文件头信息，文件名称和文件大小
    QString head = QString("%1##%2").arg(fileName).arg(fileSize);
    qint64 len = tcpSocket->write(head.toUtf8()); // 通过通信套接字发送
    if(len > 0) // 每20ms发送一次防止粘包
    {
        timer.start(TIME);
    }
    else // 发送完毕关闭文件
    {
        qDebug()<<"头部信息发送出错";
        file.close();
        ui->buttonFile->setEnabled(true);
        ui->pushButton_3->setEnabled(false);
    }

}

void CanteenWidget::sendDate()
{
    qint64 len = ZERO;
    do{
        char buf[4*1024] = {0}; // 每次发送4kb
        len = ZERO;
        len = file.read(buf,sizeof(buf)); // 读取文件内容到len
        len = tcpSocket->write(buf,len); // 通过通信套接字发送
        sendSize += len; // 记录已发送大小

    }while (len > ZERO) ; // 到文件内容为零则停止发送

    if(sendSize == fileSize) // 文件发送结束后显示发送完毕并关闭文件
    {
        ui->textEditRead->append("文件发送完毕");
        file.close();
        ui->buttonFile->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
    }
}
