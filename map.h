/*****************************************************************************/
/*
* \file map.h
* \author zxz
* \date 2022/10/10
* \version TINGSN V1
* \brief 建立一个地图类
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#ifndef MAP_H
#define MAP_H

#include "desk.h"
#include "chuangkou.h"
#include "person.h"
#include "const.h"
#include <QWidget>
#include <QPainter>
#include <QMainWindow>


namespace Ui {
class Map;
}

class Map : public QWidget
{
    Q_OBJECT

signals:
    void mapSignal();
public:
    explicit Map(QWidget *parent = 0);
    ~Map();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    Person m_person;
    Desk   m_desk[DESK_NUMBER];
    ChuangKou m_chuangkou[CHUANGKOU_NUMBER];
private:
    Ui::Map *ui;
    QPainter m_painter;
    int m_map[DESK_MAP_ROW ][DESK_MAP_COL ];
};

#endif // MAP_H
