/*****************************************************************************/
/*
* \file cilentwidget.h
* \author zxz
* \date 2022/10/15
* \version TINGSN V1
* \brief 建立一个用户聊天窗口类
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = 0);
    ~ClientWidget();
    void Connect(); // 连接商家和用户
    bool eventFilter(QObject *target, QEvent *event); // 按下回车发送信息事件
private slots:

    void on_pushButtonSend_clicked();

    void on_pushButtonClose_clicked();

    void on_pushButton_clicked();



private:
    Ui::ClientWidget *ui;
    QTcpSocket * tcpSocket; // 通信套接字

    QFile file;
    QString fileName;
    qint64  fileSize;
    qint64  recvSize;
    QByteArray inBlock;

    bool isStart;
    bool isImg;
};

#endif // CLIENTWIDGET_H
