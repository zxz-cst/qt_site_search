/*****************************************************************************/
/*
* \file thread.h
* \author zxz
* \date 2022/10/22
* \version TINGSN V1
* \brief 建立一个线程，将复杂的计算放到改线程中
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#ifndef THREAD_H
#define THREAD_H

#include <QThread>
#include "desk.h"
#include <QMutex>

class Thread : public QThread
{
    Q_OBJECT
public:
    explicit Thread(QObject *parent = nullptr);
    double dis(int x0,int y0,int x1,int y1); // 计算距离
    void quickSortSite(int left,int right,Desk * d); // 根据座位数将desk排序
    void quickSortDistant(int left,int right,Desk * d); // 根据距离用户的距离将desk排序
    int   searchBy(Desk * a, int n, int x); // 用二分法查找座位数满足要求的desk下标
    void takeDistant(Desk * d); // 计算desk到用户的距离
    void recvData(Desk * d,int x,int y,int site); // 接受主线程的数据
protected:
    void run();
signals:
    void sendResult(bool find,int x,int y,int personnumber); // 发送处理好的数据的信号

public slots:

private:
    Desk * m_d;
    int m_x;
    int m_y;
    int m_site;
    QMutex m_mutex;

};

#endif // THREAD_H
