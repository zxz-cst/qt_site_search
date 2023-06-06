/*****************************************************************************/
/*
* \file templa.h
* \author zxz
* \date 2022/10/22
* \version TINGSN V1
* \brief 建立一个模板用来交换两个类对象
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#ifndef TEMPLATE_H
#define TEMPLATE_H


class Template
{
public:
    Template();
    // 交换类的模板函数
    template<class T>
    void  swap(T &a,T &b);
};

#endif // TEMPLATE_H
