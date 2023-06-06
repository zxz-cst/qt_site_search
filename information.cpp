/*****************************************************************************/
/*
* \file information.cpp
* \author zxz
* \date 2022/10/22
* \version TINGSN V1
* \brief 建立等待窗口，放入等待图片
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#include "information.h"
#include "ui_information.h"
#include <QMovie>
#include <QImage>

Information::Information(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Information)
{
    ui->setupUi(this);
    // 构造提示信息，在多线程时显示
    setWindowFlags(Qt::FramelessWindowHint);//无边框
    setAttribute(Qt::WA_TranslucentBackground);//背景透明
    QMovie * s_mov = new QMovie("://ziyuan/loading.gif");
    ui->label->setMovie(s_mov);
    s_mov->start();
}

Information::~Information()
{
    delete ui;
}
