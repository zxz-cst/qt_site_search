/*****************************************************************************/
/*
* \file widget.h
* \author zxz
* \date 2022/10/06
* \version TINGSN V1
* \brief 建立一个主窗口类
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "subwidget.h"
#include "result.h"
#include "chuangsearch.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override; // 画窗口背景
    void dealSignal(); // 处理最后一个窗口返回的信号

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Widget *ui;
    SubWidget m_widget;
    ChuangSearch m_search;
    int m_hight,m_wide;

};

#endif // WIDGET_H
