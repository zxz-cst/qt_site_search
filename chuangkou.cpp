/*****************************************************************************/
/*
* \file chuangkou.cpp
* \author zxz
* \date 2022/10/15
* \version TINGSN V1
* \brief 实现窗口的功能与赋值
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#include "chuangkou.h"
#include "const.h"
#include <QPainter>
int ChuangKou::m_defx = 0;
int ChuangKou::m_defy = 0;
int ChuangKou::m_chaungkou = 0;
ChuangKou::ChuangKou()
{
    m_Img = QImage("://ziyuan/rs.png");
    m_cx = m_defx; // 用静态成员初始化
    m_cy = m_defy;
    m_chaungkou++; // 构造窗口总数
}

ChuangKou::~ChuangKou()
{

}

void ChuangKou::setX(int x)
{
    m_cx = x;
}

void ChuangKou::setY(int y)
{
    m_cy = y;
}

int ChuangKou::getX()
{
    return m_cx;
}

int ChuangKou::getY()
{
    return m_cy;
}

QString ChuangKou::getname()
{
    return m_name;
}


void ChuangKou::setWait(int wait)
{
    this->m_wait = wait;
}

int ChuangKou::getWait()
{
    return m_wait;
}

void ChuangKou::setName(QString name)
{
    this->m_name = name;
}
void ChuangKou::painter(QPainter * p) // 画窗口的图片
{
    p->drawImage(QRect(m_cx,ZERO,CHUANGKOU_IMAGEX,CHUANGKOU_IMAGEY),m_Img);
}
