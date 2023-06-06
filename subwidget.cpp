/*****************************************************************************/
/*
* \file subwidget.cpp
* \author zxz
* \date 2022/10/10
* \version TINGSN V1
* \brief 建立座位查询窗口，实现与父类和子类窗口的联系及传值方法
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#include "subwidget.h"
#include "ui_subwidget.h"
#include "map.h"
#include "const.h"
#include "template.h"
#include "thread.h"
#include <QString>
#include <QMessageBox>
#include <QDebug>
#include <QIcon>
#include <QPainter>
#include <QBitmap>


SubWidget::SubWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SubWidget)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("://ziyuan/winfind.png"));
    //设置标签字号
    QFont font;
    font.setPixelSize(PIX_SIZE);
    ui->label->setFont(font);
    //设置标签颜色
    QPalette palette;
    palette.setColor(QPalette::WindowText,Qt::black);
    ui->label->setPalette(palette);
    //设置按钮字号
    font.setPixelSize(PIX_ZIHAO);
    font.setFamily("KaiTi");
    //设置按钮背景
    QPixmap pix = QPixmap("://ziyuan/button.png").scaledToHeight(BUTTON_HEIGHT);
    //设置不规则按钮
    QPushButton *buttons[] = {ui->pushButton, ui->pushButton_2};
    for (QPushButton *btn : buttons)
    {
        btn->setFont(font);
        btn->setMask(pix.mask());
        btn->setFixedSize(pix.size());
        btn->setStyleSheet("background-image: url(://ziyuan/button.png)");
    }
    // 获取map发送的信号调取函数
    connect(&m_mymap,&Map::mapSignal,this,&SubWidget::dealSignal);
    // 发送数据到thread中处理
    connect(this,&SubWidget::sendDate,&m_mythread,&Thread::recvData);
    // 接受thread处理好的数据
    connect(&m_mythread,&Thread::sendResult,this,&SubWidget::dealResult);

}

SubWidget::~SubWidget()
{
    delete ui;
}

void SubWidget::on_pushButton_clicked()
{
    // 打开地图
    m_mymap.show();
    this->hide();
}

void SubWidget::dealSignal()
{
    show();
    QString text = "x:";
    text = text + QString::number(m_mymap.m_person.getX()) +"  y:"+QString::number(m_mymap.m_person.getY());
    m_result.setMyX(m_mymap.m_person.getX());
    m_result.setMyY(m_mymap.m_person.getY());
    ui->lineEdit_2->setText(text);

}

void SubWidget::on_pushButton_2_clicked()
{
    if((ui->lineEdit->text()!=nullptr)
    && (ui->lineEdit_2->text()!=nullptr)
    && ((ui->lineEdit->text() == "1")
    || (ui->lineEdit->text() == "2")
    || (ui->lineEdit->text() == "3")
    || (ui->lineEdit->text() == "4")))
    {
    m_mymap.m_person.setSite(ui->lineEdit->text().toInt());
    emit sendDate(m_mymap.m_desk,m_mymap.m_person.getX(),m_mymap.m_person.getY(),m_mymap.m_person.getSite());
    m_mythread.start(); // 进入thread线程处理数据
    m_information.show(); // 当前线程继续执行，打开一个等待窗口，等待数据处理完成
    }
    else
        QMessageBox::warning(this,"warning","请按要求输入"); // 如果输入不符合要求弹出
}

void SubWidget::dealResult(bool find,int x,int y,int personnumber)
{
    // 将处理后返回的数据存入
    m_result.setFind(find);
    m_result.setX(x);
    m_result.setY(y);
    m_result.setNumber(personnumber);
    // 关闭等待窗口
    m_information.close();
    // 调用下一个界面处理数据
    m_result.dealSignal();
    hide();
    // 显示下一个界面
    m_result.show();
}

