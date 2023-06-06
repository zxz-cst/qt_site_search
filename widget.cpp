/*****************************************************************************/
/*
* \file widget.cpp
* \author zxz
* \date 2022/10/06
* \version TINGSN V1
* \brief 建立主界面，实现与子窗口的连接
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#include "widget.h"
#include "ui_widget.h"
#include "const.h"
#include <QPainter>
#include <QBitmap>
#include <QIcon>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    setWindowIcon(QIcon("://ziyuan/winfind.png"));
    ui->setupUi(this);
    //设置标签字号
    QFont font;
    font.setPixelSize(PIX_SIZE);
    ui->label->setFont(font);
    //设置标签颜色
    QPalette palette;
    palette.setColor(QPalette::WindowText,Qt::white);
    ui->label->setPalette(palette);
    //设置按钮字号
    font.setPixelSize(PIX_ZIHAO);
    font.setFamily("KaiTi");
    //设置按钮背景
    QPixmap pix = QPixmap("://ziyuan/button.png").scaledToHeight(BUTTON_HEIGHT);
    //设置不规则按钮
    QPushButton *buttons[] = {ui->pushButton, ui->pushButton_2, ui->pushButton_3};
    for (QPushButton *btn : buttons)
    {
        btn->setFont(font);
        btn->setMask(pix.mask());
        btn->setFixedSize(pix.size());
        btn->setStyleSheet("background-image: url(://ziyuan/button.png)");
    }
    // 接受最后一个窗口的信号，显示当前窗口
    connect(&m_widget.m_result,&Result::returnSignal,this,&Widget::dealSignal);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{
    this->hide();
    m_widget.show();

}

void Widget::resizeEvent(QResizeEvent *)
{
     m_wide  = width();
     m_hight = height();
}
void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    //清空背景
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::black);
    painter.drawRect(rect());
    //绘制背景
    QPixmap pix;
    pix.load("://ziyuan/bj2.png");
    painter.drawPixmap(0, 0, m_wide, m_hight, pix);
}

void Widget::on_pushButton_3_clicked()
{
    this->hide();
}

void Widget::dealSignal()
{
    this->show();
}

void Widget::on_pushButton_2_clicked()
{
    this->hide();
    m_search.show();

}
