/*****************************************************************************/
/*
* \file information.h
* \author zxz
* \date 2022/10/23
* \version TINGSN V1
* \brief 建立一个等待窗口
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#ifndef INFORMATION_H
#define INFORMATION_H

#include <QWidget>

namespace Ui {
class Information;
}

class Information : public QWidget
{
    Q_OBJECT

public:
    explicit Information(QWidget *parent = 0);
    ~Information();

private:
    Ui::Information *ui;
};

#endif // INFORMATION_H
