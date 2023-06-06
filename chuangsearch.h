/*****************************************************************************/
/*
* \file chuangsearch.h
* \author zxz
* \date 2022/10/10
* \version TINGSN V1
* \brief 建立一个窗口查找类
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#ifndef CHUANGSEARCH_H
#define CHUANGSEARCH_H

#include <QWidget>
#include "map.h"
#include "chuangshow.h"

namespace Ui {
class ChuangSearch;
}

class ChuangSearch : public QWidget
{
    Q_OBJECT


public:
    explicit ChuangSearch(QWidget *parent = 0);
    ~ChuangSearch();
    void quickSortWait(int left,int right,ChuangKou * c); // 根据窗口等待的人的数量的快速排序

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ChuangSearch *ui;
    Map m_mymap;
    ChuangShow m_show;
};

#endif // CHUANGSEARCH_H
