/*****************************************************************************/
/*
* \file subwidget.h
* \author zxz
* \date 2022/10/06
* \version TINGSN V1
* \brief 建立一个座位查找窗口类
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#ifndef SUBWIDGET_H
#define SUBWIDGET_H

#include <QWidget>
#include "map.h"
#include <QMainWindow>
#include "result.h"
#include <QVector>
#include "thread.h"
#include "information.h"

namespace Ui {
class SubWidget;
}

class SubWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SubWidget(QWidget *parent = 0);
    ~SubWidget();
    Result m_result;
signals:
    void sendDate(Desk * d,int x,int y,int site); // 将地图信息传给thread线程处理
private slots:
    void on_pushButton_clicked();
    void dealSignal();  // 处理从map中获取用户位置的信息
    void dealResult(bool find,int x,int y,int personnumber); // 处理thread返回的信号
    void on_pushButton_2_clicked();

private:
    Ui::SubWidget *ui;
    Map  m_mymap;
    Thread  m_mythread;
    Information m_information;

};

#endif // SUBWIDGET_H
