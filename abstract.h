/*****************************************************************************/
/*
* \file abstract.h
* \author zxz
* \date 2022/10/22
* \version TINGSN V1
* \brief 构建一个抽象类为桌子和人提供位置设置和读取的方法
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#ifndef ABSTRACT_H
#define ABSTRACT_H

class Abstract
{
public:
    virtual void setX(int x) = 0; // 设置x坐标的纯虚函数
    virtual void setY(int y) = 0; // 设置y坐标的纯虚函数
    virtual int  getX() = 0; // 读取x坐标的纯虚函数
    virtual int  getY() = 0; // 读取x坐标的纯虚函数
};


#endif // ABSTRACT_H
