/*****************************************************************************/
/*
* \file thread.cpp
* \author zxz
* \date 2022/10/22
* \version TINGSN V1
* \brief 实现线程内的计算，返回最后计算的结果
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#include "thread.h"
#include "const.h"
#include "template.h"

Thread::Thread(QObject *parent) : QThread(parent)
{

}


void Thread::recvData(Desk * d,int x,int y,int site)
{
    m_d = d;
    m_x = x;
    m_y = y;
    m_site = site;
}

void Thread::run()
{
    m_mutex.lock(); // 线程锁，防止互斥
    takeDistant(m_d); // 计算用户和每一个桌子的距离
    quickSortSite(0,DESK_NUMBER - 1,m_d); // 按座位排序
    // 找到需要座位个数的桌子
    int s_index1 =searchBy(m_d,DESK_NUMBER,1);
    int s_index2 =searchBy(m_d,DESK_NUMBER,2);
    int s_index3 =searchBy(m_d,DESK_NUMBER,3);
    int s_index4 =searchBy(m_d,DESK_NUMBER,4);
    switch (m_site) {
    case 1:
        quickSortDistant(0,s_index4 - 1,m_d); // 找到离用户最近的桌子
        if(m_d[MIN_INDEX].getPersonnum() <= 3)
        emit sendResult(true,(m_d[MIN_INDEX].getY() - CHUANGKOU_IMAGEY - DESK_IMAGEY)/CHUANGKOU_IMAGEY + 1,(m_d[MIN_INDEX].getX() - DESK_IMAGEX)/CHUANGKOU_IMAGEX + 1,m_d[MIN_INDEX].getPersonnum());
        else
        emit sendResult(false,0,0,0);
        m_d[MIN_INDEX].setPersonnum(m_d[MIN_INDEX].getPersonnum() + m_site); // 找到座位后该桌子人数加用户需要座位的个数，其他用户查找时不会在找同一座位
        break;
    case 2:
        quickSortDistant(0,s_index3 - 1,m_d);
        if(m_d[MIN_INDEX].getPersonnum() <= 2)
        emit sendResult(true,(m_d[MIN_INDEX].getY() - CHUANGKOU_IMAGEY - DESK_IMAGEY)/CHUANGKOU_IMAGEY + 1,(m_d[MIN_INDEX].getX() - DESK_IMAGEX)/CHUANGKOU_IMAGEX + 1,m_d[MIN_INDEX].getPersonnum());
        else
        emit sendResult(false,0,0,0);
        m_d[MIN_INDEX].setPersonnum(m_d[MIN_INDEX].getPersonnum() + m_site); // 找到座位后该桌子人数加用户需要座位的个数，其他用户查找时不会在找同一座位
        break;
    case 3:
        quickSortDistant(0,s_index2 - 1,m_d);
        if(m_d[MIN_INDEX].getPersonnum() <= 1)
        emit sendResult(true,(m_d[MIN_INDEX].getY() - CHUANGKOU_IMAGEY - DESK_IMAGEY)/CHUANGKOU_IMAGEY + 1,(m_d[MIN_INDEX].getX() - DESK_IMAGEX)/CHUANGKOU_IMAGEX + 1,m_d[MIN_INDEX].getPersonnum());
        else
        emit sendResult(false,0,0,0);
        m_d[MIN_INDEX].setPersonnum(m_d[MIN_INDEX].getPersonnum() + m_site); // 找到座位后该桌子人数加用户需要座位的个数，其他用户查找时不会在找同一座位
        break;
    case 4:
        quickSortDistant(0,s_index1 - 1,m_d);
        if(m_d[MIN_INDEX].getPersonnum() == 0)
        emit sendResult(true,(m_d[MIN_INDEX].getY() - CHUANGKOU_IMAGEY - DESK_IMAGEY)/CHUANGKOU_IMAGEY + 1,(m_d[MIN_INDEX].getX() - DESK_IMAGEX)/CHUANGKOU_IMAGEX + 1,m_d[MIN_INDEX].getPersonnum());
        else
        emit sendResult(false,0,0,0);
        m_d[MIN_INDEX].setPersonnum(m_d[MIN_INDEX].getPersonnum() + m_site); // 找到座位后该桌子人数加用户需要座位的个数，其他用户查找时不会在找同一座位
        break;
    default:
        break;
    }
    m_mutex.unlock(); // 解锁
}


double Thread::dis(int x0,int y0,int x1,int y1)
{
    return sqrt((x0 - x1)*(x0 - x1)+(y0 - y1)*(y0 - y1));
}


void Thread::quickSortSite(int left,int right,Desk * d)
{
    if(left > right)
        return;
    int i = left;
    int j = right;
    Template t;
    Desk tmp = d[left];
    while(i != j)
    {
        while(d[j] >= tmp && i < j)
            j--;
        while(d[i] <= tmp && i < j)
            i++;
        if(i < j)
        {
            t.swap(d[i],d[j]);
        }
    }
    t.swap(d[left],d[i]);
    quickSortSite(left,i - ONE,d);
    quickSortSite(i + ONE,right,d);
    return;
}


int   Thread::searchBy(Desk * a, int n, int x)
{
        int low = 0;
        int high = n - 1;
        int binary = (low + high) / 2;
        int t_biao = n;
        while (low <= high)
        {
            if (x < a[binary].getPersonnum())
                high = binary - 1;
            if(x > a[binary].getPersonnum())
                low = binary + 1;
            if (x == a[binary].getPersonnum())
            {
                if (t_biao > binary)
                    t_biao = binary;
                high = binary - 1;
            }
            binary = (low + high) / 2;
        }


        if (t_biao != n)
            return t_biao;
        else
            return -1;
}

void Thread::takeDistant(Desk * d)
{
    for(int i = 0;i < DESK_NUMBER ;i++)
    {
        d[i].setDistant(dis(m_x,m_y,m_d[i].getX(),m_d[i].getY()));
    }
}

void Thread::quickSortDistant(int left,int right,Desk * d)
{
    if(left > right)
        return;
    int i = left;
    int j = right;
    Template t;
    double tmp = d[left].getDistant();
    while(i != j)
    {
        while(d[j].getDistant() >= tmp && i < j)
            j--;
        while(d[i].getDistant() <= tmp && i < j)
            i++;
        if(i < j)
        {
            t.swap(d[i],d[j]);
        }
    }

    t.swap(d[left],d[i]);
    quickSortDistant(left,i - ONE,d);
    quickSortDistant(i + ONE,right,d);
    return;
}
