/*****************************************************************************/
/*
* \file chuangshow.h
* \author zxz
* \date 2022/10/20
* \version TINGSN V1
* \brief 建立一个窗口界面结果类
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#ifndef CHUANGSHOW_H
#define CHUANGSHOW_H

#include "clientwidget.h"
#include "canteenwidget.h"
#include <QWidget>
#include <QString>

namespace Ui {
class ChuangShow;
}

class ChuangShow : public QWidget
{
    Q_OBJECT

public:
    explicit ChuangShow(QWidget *parent = 0);
    ~ChuangShow();
    void setWait(int wait);
    void setName(QString name);
    void setX(int x);
    int  getX();
    void setY(int y);
    int  getY();
    void Show();
    void Show2();
    int getWait();
    QString getName();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ChuangShow *ui;
    int m_wait;
    int m_cx;
    int m_cy;
    QString m_name;
    CanteenWidget m_canteen;
    ClientWidget  m_client;
};

#endif // CHUANGSHOW_H
