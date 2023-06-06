/*****************************************************************************/
/*
* \file chuangsearch.cpp
* \author zxz
* \date 2022/10/17
* \version TINGSN V1
* \brief 建立窗口查找界面，实现与父窗口和子窗口的连接和传值
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#include "chuangsearch.h"
#include "ui_chuangsearch.h"
#include "const.h"
#include "template.h"
#include <QDebug>
#include <QIcon>
#include <chuangkou.h>
#include <QPainter>
#include <QBitmap>
#include <QMessageBox>

ChuangSearch::ChuangSearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChuangSearch)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("://ziyuan/winfind.png"));
    // 设置comboBox的选择值
    ui->comboBox->addItem("点击选择窗口");
    ui->comboBox->addItem("特色快餐");
    ui->comboBox->addItem("土耳其烤肉饭");
    ui->comboBox->addItem("兰州拉面");
    ui->comboBox->addItem("老妈拌饭");
    ui->comboBox->addItem("兰州拉面");
    ui->comboBox->addItem("陕西风味");
    ui->comboBox->addItem("麻辣香锅");
    ui->comboBox->addItem("风味砂锅");
    ui->comboBox->addItem("河南烩面");
    ui->comboBox->addItem("鸭血粉丝汤");
    ui->comboBox->addItem("牛肉粉");
    QFont font;
    font.setPixelSize(PIX_SIZE);
    ui->label_2->setFont(font);
    //设置标签颜色
    QPalette palette;
    palette.setColor(QPalette::WindowText,Qt::black);
    ui->label_2->setPalette(palette);
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

}

ChuangSearch::~ChuangSearch()
{
    delete ui;
}

void ChuangSearch::on_pushButton_2_clicked()
{
    if(ui->comboBox->currentText() == "点击选择窗口")
    {
        QMessageBox::warning(this,"提示","请选择窗口");
    }
    //根据用户选择窗口名称找出对应的等待人数并输出
    else
    {
        for(int i = 0;i<CHUANGKOU_NUMBER;i++){
            if(m_mymap.m_chuangkou[i].getname() == ui->comboBox->currentText())
            {
                m_show.setWait(m_mymap.m_chuangkou[i].getWait());
                m_show.setName(m_mymap.m_chuangkou[i].getname());
                m_show.setX(m_mymap.m_chuangkou[i].getX());
                m_show.setY(m_mymap.m_chuangkou[i].getY());
                break;
            }
        }
        m_show.Show(); // 传递值到下一个窗口
        hide();
        m_show.show();
    }



}

void ChuangSearch::on_pushButton_clicked()
{
    // 利用快速排序找到当前食堂排队人数最少的窗口
    quickSortWait(ZERO,CHUANGKOU_NUMBER - ONE,m_mymap.m_chuangkou);
    m_show.setWait(m_mymap.m_chuangkou[MIN_INDEX].getWait());
    m_show.setName(m_mymap.m_chuangkou[MIN_INDEX].getname());
    m_show.setX(m_mymap.m_chuangkou[MIN_INDEX].getX());
    m_show.setY(m_mymap.m_chuangkou[MIN_INDEX].getY());
    m_show.Show2(); // 将text中文字显示
    hide();
    m_show.show();

}

void ChuangSearch::quickSortWait(int left,int right,ChuangKou * c)
{
        if(left > right)
            return;
        int i = left;
        int j = right;
        Template t;
        ChuangKou tmp = c[left];
        while(i != j)
        {
            while(c[j] >= tmp && i < j)
                j--;
            while(c[i] <= tmp && i < j)
                i++;
            if(i < j)
            {
                t.swap(c[i],c[j]);

            }
        }
        t.swap(c[left],c[i]);
        quickSortWait(left,i - ONE,c);
        quickSortWait(i + ONE,right,c);
        return;
}


