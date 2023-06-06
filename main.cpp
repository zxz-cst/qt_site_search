/*****************************************************************************/
/*
* \file main.cpp
* \author zxz
* \date 2022/10/06
* \version TINGSN V1
* \brief 主函数调用
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.show();

    return a.exec();
}
