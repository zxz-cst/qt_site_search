/*****************************************************************************/
/*
* \file desk.h
* \author zxz
* \date 2022/10/06
* \version TINGSN V1
* \brief 建立一个桌子类
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#ifndef DESK_H  // 防止头文件被重复引用
#define DESK_H
#include <QImage>
#include <QPainter>
#include "abstract.h"

class Desk :virtual public Abstract
{
public:
    Desk();
    Desk(int x,int y,int personnum);
    ~Desk();
    void setPersonnum(int personnum);
    void setX(int x);
    void setY(int y);
    void setDistant(double distant);
    double getDistant();
    int  getPersonnum();
    int  getX();
    int  getY();
    void painter(QPainter * p);
    bool operator <=(const Desk &c) // <=运算符重载
    {
        if(this->m_personnum <= c.m_personnum)
            return true;
        else
            return false;
    }
    bool operator >=(const Desk &c) // >=运算符重载
    {
        if(this->m_personnum >= c.m_personnum)
            return true;
        else
            return false;
    }



private:
    int m_personnum;
    int m_dx;
    int m_dy;
    double m_distant;
    static int m_defx,m_defy;
    static int m_desk;
    QImage m_Img ;
};

#endif // DESK_H
