/*****************************************************************************/
/*
* \file chuangshow.cpp
* \author zxz
* \date 2022/10/18
* \version TINGSN V1
* \brief 建立窗口查询结果输出界面，实现与父窗口和子窗口的连接
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#include "chuangshow.h"
#include "ui_chuangshow.h"
#include "const.h"
#include <QString>
#include <QIcon>
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QIcon>
#include <QPainter>
#include <QBitmap>

ChuangShow::ChuangShow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChuangShow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("://ziyuan/winfind.png"));
    // 设置字体大小和字号
    QFont font;
    font.setPixelSize(PIX_ZIHAO);
    font.setFamily("KaiTi");
    // 设置按钮样式
    QPixmap pix = QPixmap("://ziyuan/button.png").scaledToHeight(BUTTON_HEIGHT);
    QPushButton *buttons[] = {ui->pushButton, ui->pushButton_2};
    for (QPushButton *btn : buttons)
    {
        btn->setFont(font);
        btn->setMask(pix.mask());
        btn->setFixedSize(pix.size());
        btn->setStyleSheet("background-image: url(://ziyuan/button.png)");
    }

}

ChuangShow::~ChuangShow()
{
    delete ui;
}


void ChuangShow::setWait(int wait)
{
    this->m_wait = wait;
}

void ChuangShow::setName(QString name)
{
    this->m_name = name;
}

void ChuangShow::setX(int x)
{
    m_cx = x;
}

int  ChuangShow::getX()
{
    return m_cx;
}

void  ChuangShow::setY(int y)
{
    m_cy = y;
}

int   ChuangShow::getY()
{
    return m_cy;
}

int ChuangShow::getWait()
{
    return m_wait;
}
QString ChuangShow::getName()
{
    return m_name;
}

void ChuangShow::Show()
{
    QString text = getName();
    text = text +"有"+ QString::number(getWait()) + "人在排队，预计需要等待" + QString::number(getWait() * TWO) + "分钟。如有任何问题，请点击下方的咨询商家。";
    ui->textEdit->setText(text);
    // 将找到的目标位置画一个正方形框显示出来
    QPixmap img("://ziyuan/map1.png");
    QPainter painter(&img);
    painter.drawRect(QRect(getX() ,getY(),CHUANGKOU_IMAGEX,CHUANGKOU_IMAGEY));
    ui->label->setPixmap(img);
    ui->textEdit->setText(text);
    // 设置标签字号
    QFont font;
    font.setPixelSize(20);
    ui->textEdit->setFont(font);
    // 设置标签颜色
    QPalette palette;
    palette.setColor(QPalette::WindowText,Qt::black);
    ui->textEdit->setPalette(palette);
}

void ChuangShow::Show2()
{
    QString text = getName();
    text = text +"排队人数最少，有"+ QString::number(getWait()) + "人在排队，预计需要等待" + QString::number(getWait() * 2) + "分钟。如有任何问题，请点击下方的咨询商家。";
    ui->textEdit->setText(text);
    ui->textEdit->setText(text);
    // 将找到的目标位置画一个正方形框显示出来
    QPixmap img("://ziyuan/map1.png");
    QPainter painter(&img);
    painter.drawRect(QRect(getX() ,getY(),CHUANGKOU_IMAGEX,CHUANGKOU_IMAGEY));
    ui->label->setPixmap(img);
    ui->textEdit->setText(text);
    // 设置标签字号
    QFont font;
    font.setPixelSize(20);
    ui->textEdit->setFont(font);
    // 设置标签颜色
    QPalette palette;
    palette.setColor(QPalette::WindowText,Qt::black);
    ui->textEdit->setPalette(palette);
}

void ChuangShow::on_pushButton_clicked()
{
    m_canteen.show(); // 打开商家聊天框
    m_client.show();  // 打开用户聊天框
    m_client.Connect(); // 连接商家和用户
    hide();
}

void ChuangShow::on_pushButton_2_clicked()
{
    close();
}
