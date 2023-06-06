/*****************************************************************************/
/*
* \file person.h
* \author zxz
* \date 2022/10/06
* \version TINGSN V1
* \brief 建立一个顾客类
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#ifndef PERSON_H
#define PERSON_H
#include "abstract.h"

class Person :virtual public Abstract
{

public:
    Person();
    Person(int x,int y,int siteNeed);
    ~Person();
    void  setX(int x);
    void  setY(int y);
    int   getX();
    int   getY();
    void  setSite(int siteNeed);
    int   getSite();
private:
    int m_px;
    int m_py;
    int m_siteNeed;

};
#endif // PERSON_H
