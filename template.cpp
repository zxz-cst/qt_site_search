/*****************************************************************************/
/*
* \file template.cpp
* \author zxz
* \date 2022/10/22
* \version TINGSN V1
* \brief 实现交换模板。建立函数模板交换指定两个类的对象
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#include "template.h"
#include "chuangkou.h"
#include "desk.h"

Template::Template()
{
  // 建立两个函数模板
  ChuangKou a;
  ChuangKou b;
  swap(a,b);
  Desk c;
  Desk d;
  swap(c,d);
}

template<class T>
void Template::swap(T &a,T &b)
{
    T temp;
    temp = a;
    a = b;
    b = temp;
}
