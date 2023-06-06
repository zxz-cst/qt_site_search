/*****************************************************************************/
/*
* \file canteenwidget.h
* \author zxz
* \date 2022/10/15
* \version TINGSN V1
* \brief 建立一个商家聊天窗口类
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#ifndef CANTEENWIDGET_H
#define CANTEENWIDGET_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QFile>
#include <QTimer>

namespace Ui {
class CanteenWidget;
}

class CanteenWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CanteenWidget(QWidget *parent = 0);
    ~CanteenWidget();
    void sendDate(); // 发送数据函数
    bool eventFilter(QObject *target, QEvent *event); // 按下回车发送文本区文字事件

private slots:
    void on_buttonSend_clicked(); // 发送信息按钮

    void on_buttonClose_clicked(); // 断开连接按钮

    void on_pushButton_clicked(); // 关闭聊天窗口按钮

    void on_buttonFile_clicked(); // 选择文件按钮

    void on_pushButton_3_clicked(); // 发送文件按钮



private:
    Ui::CanteenWidget *ui;
    QTcpServer * tcpServer;  // 监听套接字
    QTcpSocket * tcpSocket;  // 通信套接字
    QFile file;              // 文件
    QString fileName;        // 文件名称
    qint64  fileSize;        // 文件大小
    qint64  sendSize;        // 已发送文件大小

    QTimer timer;            // 计时器每隔20ms发送一次
};

#endif // CANTEENWIDGET_H
