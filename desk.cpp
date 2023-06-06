/*****************************************************************************/
/*
* \file desk.cpp
* \author zxz
* \date 2022/10/06
* \version TINGSN V1
* \brief 实现桌子中的方法
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#include "desk.h"
#include "const.h"
#include <QPainter>
int Desk::m_defx = 0;
int Desk::m_defy = 0;
int Desk::m_desk = 0;
Desk::Desk()
{
    m_Img = QImage("://ziyuan/desk4.png");
    m_dx = m_defx; // 用静态成员初始化
    m_dy = m_defy;
    m_desk++; //记录构造桌子总数


}


Desk::Desk(int x,int y,int personnum)
{
    m_dx = x;
    m_dy = y;
    m_personnum = personnum;
    m_desk++;

}

Desk::~Desk()
{
    m_desk--;
}

void Desk::setPersonnum(int personnum)
{
    m_personnum = personnum;
}

void Desk::setX(int x)
{
    m_dx = x;
}

void Desk::setY(int y)
{
    m_dy= y;
}

void Desk::setDistant(double distant)
{
    m_distant  = distant;
}

double Desk::getDistant()
{
    return m_distant;
}

int  Desk::getPersonnum()
{
    return m_personnum;
}

int  Desk::getX()
{
    return m_dx;
}

int  Desk::getY()
{
    return m_dy;
}


void Desk::painter(QPainter * p) // 画出桌子图片
{
    p->drawImage(QRect(m_dx,m_dy,DESK_IMAGEX,DESK_IMAGEY),m_Img);
}
