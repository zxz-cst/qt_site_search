/*****************************************************************************/
/*
* \file chuangkou.h
* \author zxz
* \date 2022/10/06
* \version TINGSN V1
* \brief 建立一个食堂窗口类
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#ifndef CHUANGKOU_H
#define CHUANGKOU_H
#include <QString>
#include <QImage>

class ChuangKou
{
public:
    ChuangKou();
    ~ChuangKou();
    void setX(int x);
    void setY(int y);
    void setWait(int wait);
    void setName(QString name);
    int getX();
    int getY();
    int getWait();
    QString getname();
    void painter(QPainter * p);
    QString m_allname[10] ={"特色快餐","土耳其烤肉饭","兰州拉面","老妈拌饭","陕西风味","麻辣香锅","风味砂锅","河南烩面","鸭血粉丝汤","牛肉粉"};
    bool operator <=(const ChuangKou &c) //<=运算符重载
    {
        if(this->m_wait <= c.m_wait)
            return true;
        else
            return false;
    }
    bool operator >=(const ChuangKou &c) //>=运算符重载
    {
        if(this->m_wait >= c.m_wait)
            return true;
        else
            return false;
    }

private:
    int m_cx;
    int m_cy;
    int m_wait;
    static int m_defx,m_defy;
    static int m_chaungkou;
    QString m_name;    
    QImage m_Img ;
};

#endif // CHUANGKOU_H
