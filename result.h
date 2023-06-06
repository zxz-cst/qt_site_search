/*****************************************************************************/
/*
* \file result.h
* \author zxz
* \date 2022/10/15
* \version TINGSN V1
* \brief 建立一个结果显示窗口类
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#ifndef RESULT_H
#define RESULT_H

#define ROWS 27
#define COLS 30

#define ZXDJ 10
#define XXDJ 14
#include <QWidget>
#include <QVector>
#include "node.h"


enum direact {
    p_up, p_down, p_left, p_right,
    p_lup, p_ldown, p_rup, p_rdown
};
// 存坐标
struct MyPoint {
    int row;
    int col;

    int f;
    int g;
    int h;
};
// 树的节点类型
struct treeNode
{
    MyPoint  pos;
    QVector<treeNode*> child;
    treeNode* pParent;

};


namespace Ui {
class Result;
}

class Result : public QWidget
{
    Q_OBJECT
signals:
    void returnSignal(); // 发送一个信号到主页实施跳转会主页

public:
    explicit Result(QWidget *parent = 0);
    ~Result();
    void setX(int x);
    int  getX();
    void setY(int y);
    int  getY();
    void setMyX(int myx);
    int  getMyX();
    void setMyY(int myy);
    int  getMyY();
    void setNumber(int number);
    int  getNumber();
    void setFind(bool find);
    bool  getFind(); // 是否找到符合要求的座位
    void dealSignal(); // 处理上一个界面的信息
    treeNode* searchLoad();
    treeNode* creatTreeNode(int row, int col);
    int getH(MyPoint pos, MyPoint endPos);
    void paintEvent(QPaintEvent *event);

private slots:
    void on_pushButton_2_clicked();

 //   void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::Result *ui;
    int m_myx;
    int m_myy;
    int m_rx;
    int m_ry;
    int m_Number;
    bool m_find = false;
    node m_Astar;

};

#endif // RESULT_H
