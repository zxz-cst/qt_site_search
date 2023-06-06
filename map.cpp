/*****************************************************************************/
/*
* \file map.cpp
* \author zxz
* \date 2022/10/10
* \version TINGSN V1
* \brief 用paint方法绘制食堂地图
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#include "map.h"
#include "ui_map.h"
#include "const.h"
#include <QPainter>
#include <QMouseEvent>
#include <QTime>
#include <QDebug>
#include <QIcon>

Map::Map(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Map)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("://ziyuan/winfind.png"));
    QTime time = QTime::currentTime();
    qsrand(time.msec()+time.second()*1000);
    // 随机生成窗口等待人数3 - 20人
    for(int i = 0;i<CHUANGKOU_NUMBER;i++)
    {
        m_chuangkou[i].setX(i*CHUANGKOU_IMAGEX);
        m_chuangkou[i].setY(0);
        m_chuangkou[i].setName(m_chuangkou[i].m_allname[i]);
        m_chuangkou[i].setWait(qrand()%17 + 3);

    }
    // 随机生成桌子就坐人数0 - 4人
    for(int i = 0;i<DESK_NUMBER;i++)
    {
        if(i % 3 != 0)
        m_desk[i].setPersonnum(qrand()%2+3);
        else
        m_desk[i].setPersonnum(qrand()%3);

    }
    // 将地图刷零
    for(int i = 0;i<DESK_MAP_ROW;i++)
        for(int j = 0;j<DESK_MAP_COL;j++)
            m_map[i][j] = 0;
    // 读入桌子坐标，并记录桌子位置以便画图
    int s_tmpx = ZERO;
    int s_tmpy = CHUANGKOU_IMAGEY;
    int s_sum  = 0;
    for(int i = 0;i<DESK_MAP_ROW;i++){
        for(int j = 0;j<DESK_MAP_COL;j++)
        {
            if(i % ROAD_DESK_DISTENT == 1 && j % ROAD_DESK_DISTENT ==1)
            {

               m_desk[s_sum].setX(s_tmpx);
               m_desk[s_sum].setY(s_tmpy);
               s_tmpx += DESK_IMAGEX;
               s_sum++;
               m_map[i][j] = 1;
            }
            else
            {
               s_tmpx += DESK_IMAGEX;
            }
        }
        s_tmpx = 0;
        s_tmpy += DESK_IMAGEY;
    }
}


Map::~Map()
{

    delete ui;
}

void Map::paintEvent(QPaintEvent *event)
{

    m_painter.begin(this);
    // 绘制窗口
    for(int i = 0;i<CHUANGKOU_NUMBER;i++)
    {
        m_chuangkou[i].setX(i*CHUANGKOU_IMAGEX);
        m_chuangkou[i].setY(0);
        m_chuangkou[i].painter(&m_painter);

    }

    // 绘制地图
    int s_sm = 0;
    for(int i = 0;i<DESK_MAP_ROW;i++){
        for(int j = 0;j<DESK_MAP_COL;j++)
        {
            if(m_map[i][j] == 1)
            {
               m_desk[s_sm].painter(&m_painter);
               s_sm ++;
            }
            else
            {
               m_painter.drawImage(QRect(j * 10 ,i * 10 + 30,ROAD_IMAGEX,ROAD_IMAGEY),QImage("://ziyuan/road2.png"));
            }
        }
    }
    m_painter.end();


}


void Map::mousePressEvent(QMouseEvent *event)
{
    // 用户在地图点击时获取位置信息
    if(event->button()==Qt::LeftButton)
        {
            m_person.setX(event->x());
            m_person.setY(event->y());
            emit mapSignal();
            hide();
        }
}

