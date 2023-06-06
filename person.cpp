/*****************************************************************************/
/*
* \file person.cpp
* \author zxz
* \date 2022/10/06
* \version TINGSN V1
* \brief 实现顾客的方法
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#include "person.h"

Person::Person()
{
   m_px = 0;
}

Person::Person(int x,int y,int siteNeed)
{
    m_px = x;
    m_py = y;
    m_siteNeed = siteNeed;
}

Person::~Person()
{

}

void Person::setX(int x)
{
    m_px = x;
}

void Person::setY(int y)
{
    m_py = y;
}

int  Person::getX()
{
    return m_px;
}

int  Person::getY()
{
    return m_py;
}

void  Person::setSite(int siteNeed)
{
    m_siteNeed = siteNeed;
}
int   Person::getSite()
{
    return m_siteNeed;
}
