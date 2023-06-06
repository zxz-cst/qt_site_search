/*****************************************************************************/
/*
* \file result.cpp
* \author zxz
* \date 2022/10/20
* \version TINGSN V1
* \brief 输出最后结果的方法
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#include "result.h"
#include "ui_result.h"
#include "const.h"
#include <QString>
#include <QPainter>
#include <QImage>
#include <QPixmap>
#include <QIcon>
#include <QPainter>
#include <QBitmap>
#include <QDebug>
#include <string.h>
#include <QtAlgorithms>
#include <algorithm>



Result::Result(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Result)
{
    ui->setupUi(this);
    setWindowIcon(QIcon("://ziyuan/winfind.png"));
    QFont font;
    font.setPixelSize(PIX_ZIHAO);
    font.setFamily("KaiTi");
    QPixmap pix = QPixmap("://ziyuan/button.png").scaledToHeight(BUTTON_HEIGHT);
    QPushButton *buttons[] = {ui->pushButton_3, ui->pushButton_2};
    for (QPushButton *btn : buttons)
    {
        btn->setFont(font);
        btn->setMask(pix.mask());
        btn->setFixedSize(pix.size());
        btn->setStyleSheet("background-image: url(://ziyuan/button.png)");
    }



}

Result::~Result()
{
    delete ui;

}

void Result::setX(int x)
{
    m_rx = x;
}
int  Result::getX()
{
    return m_rx;
}

void  Result::setY(int y)
{
    m_ry = y;
}
int   Result::getY()
{
    return m_ry;
}

void Result::setMyX(int myx)
{
    this->m_myx = myx;
}

int  Result::getMyX()
{
    return m_myx;
}

void Result::setMyY(int myy)
{
    this->m_myy = myy;
}

int  Result::getMyY()
{
    return m_myy;
}

void Result::setFind(bool find)
{
    m_find = find;
}

bool  Result::getFind()
{
    return m_find;
}

void Result::setNumber(int number)
{
    m_Number = number;
}

int  Result::getNumber()
{
    return m_Number;
}



void Result::on_pushButton_2_clicked()
{
    close();
}

/*void Result::on_pushButton_clicked()
{
    emit returnSignal();
    close();
}*/

void Result::paintEvent(QPaintEvent *event)
{
   /* if(m_find == true)
    {
    QPixmap img("://ziyuan/map1.png");
    QPainter paint(&img);
    QPainterPath path;
    treeNode * s_current = searchLoad();
    path.moveTo(s_current->pos.row,s_current->pos.col);

    s_current = s_current->pParent;
    while(s_current)
    {
        path.lineTo(s_current->pos.row,s_current->pos.col);
        s_current = s_current->pParent;
    }
    paint.setPen(QColor(Qt::red));
    //paint.drawPath(path);
    paint.drawRect(QRect((getY() - 1) * CHUANGKOU_IMAGEY + DESK_IMAGEY,(getX() - 1) * CHUANGKOU_IMAGEX + CHUANGKOU_IMAGEX + DESK_IMAGEX,DRAW_X,DRAW_Y));
   // ui->label->setPixmap(img);
    }*/
}

void Result::dealSignal()
{
    QString text;
    if(m_find == true){
        text = "成功找到符合要求的座位，距离您最近座位在第";
        text = text + QString::number(getX())  + "排" + QString::number(getY()) + "列（图中已框出）" + "。当前座位有" + QString::number(getNumber()) + "人在用餐。祝您用餐愉快！";
        // 用正方形圈出找到的位置
       QPixmap img("://ziyuan/map1.png");
        QPainter painter(&img);
        painter.drawRect(QRect((getY() - 1) * CHUANGKOU_IMAGEY + DESK_IMAGEY,(getX() - 1) * CHUANGKOU_IMAGEX + CHUANGKOU_IMAGEX + DESK_IMAGEX,DRAW_X,DRAW_Y));
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
    else{
        text = "很抱歉，未找到符合要求的座位，返回首页试试其他座位数吧";
        // 用正方形圈出找到的位置
        QPixmap img("://ziyuan/map1.png");
        ui->label->setPixmap(img);
        ui->textEdit->setText(text);
        QFont font;
        font.setPixelSize(20);
        ui->textEdit->setFont(font);
        // 设置标签颜色
        QPalette palette;
        palette.setColor(QPalette::WindowText,Qt::black);
        ui->textEdit->setPalette(palette);
    }

}
/*
treeNode* Result::searchLoad()
{
    int map[ROWS][COLS] =
        {
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
            {0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,1,0},
            {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},

        };
        bool pathMap[ROWS][COLS] = { 0 };
        MyPoint begPos = { getMyX() /10,(getMyY() -30)/10 };
        MyPoint endPos = { getY()*3 - 2,getX()*3 - 2 };
        map[getY()*3 - 2][getX()*3 - 2] = 0;

        pathMap[begPos.row][begPos.col] = true;
        treeNode* pRoot = NULL;
        // 起点如树
        pRoot = creatTreeNode(begPos.row, begPos.col);
        QVector<treeNode*> buff;
        bool isFindEnd = false;

        treeNode* current = pRoot;
        QVector<treeNode*>::iterator it;
        QVector<treeNode*>::iterator itMin;
        while (1)
        {
            // 把当前点周围能走的点找出来
            for (int i = 0;i < 8;i++)
            {
                treeNode* pChild = creatTreeNode(current->pos.row, current->pos.col);
                switch (i)
                {
                case p_up:
                    pChild->pos.row--;
                    pChild->pos.g += ZXDJ;
                    // 判断能不能走，，
                    break;
                case p_down:
                    pChild->pos.row++;
                    pChild->pos.g += ZXDJ;
                    // 判断能不能走，，
                    break;
                case p_left:
                    pChild->pos.col--;
                    pChild->pos.g += ZXDJ;
                    // 判断能不能走，，
                    break;
                case p_right:
                    pChild->pos.col++;
                    pChild->pos.g += ZXDJ;
                    // 判断能不能走，，
                    break;
                case p_lup:
                    pChild->pos.col--;
                    pChild->pos.row--;
                    pChild->pos.g += XXDJ;
                    // 判断能不能走，，
                    break;
                case p_ldown:
                    pChild->pos.col--;
                    pChild->pos.row++;
                    pChild->pos.g += XXDJ;
                    // 判断能不能走，，
                    break;
                case p_rup:
                    pChild->pos.col++;
                    pChild->pos.row--;
                    pChild->pos.g += XXDJ;
                    // 判断能不能走，，
                    break;
                case p_rdown:
                    pChild->pos.col++;
                    pChild->pos.row++;
                    pChild->pos.g += XXDJ;
                    // 判断能不能走，，
                    break;

                }
                if (map[pChild->pos.row][pChild->pos.col] != 1 &&
                    pathMap[pChild->pos.row][pChild->pos.col] == false
                    )
                {// 能走的计算f值入树
                    pChild->pos.h = getH(pChild->pos, endPos);
                    pChild->pos.f = pChild->pos.g + pChild->pos.h;

                    current->child.push_back(pChild);
                    pChild->pParent = current;

                    buff.push_back(pChild);
                }
                else
                {
                    //delete pChild;
                }
            }


            //找出数组中f值最小的点，走上去
            itMin = buff.begin();
            for (it = buff.begin();it != buff.end();it++)
            {
                itMin = (((*it)->pos.f < (*itMin)->pos.f) ? it : itMin);

            }

            // 走上去
            current = *itMin;
            // 标记走过
            pathMap[current->pos.row][current->pos.col] = true;


            // 从数组中删除
            buff.erase(itMin);



            //判断是否找到终点
            if (current->pos.row == endPos.row &&
                current->pos.col == endPos.col
                ) {
                isFindEnd = true;
                break;
            }

            // 判断数组是否为空 为空说明都试过仍找不到终点
            if (buff.size() == 0)
                break;
        }
        /*if (isFindEnd)
        {
            qDebug()<< "找到终点了\n";
            while (current)
            {
                qDebug()<<" "<< current->pos.row <<" "<< current->pos.col<<" ";
                current = current->pParent;
            }
            qDebug() <<'\n';
        }
        if(isFindEnd)
        return current;
}


treeNode* Result::creatTreeNode(int row, int col)
{
        treeNode* pNew = new treeNode;
     //   memset(pNew, 1, sizeof(treeNode));
        pNew->pParent = NULL;
        pNew->pos.row = row;
        pNew->pos.col = col;
        return pNew;
}

int Result::getH(MyPoint pos, MyPoint endPos)
{
        int  x = (pos.col > endPos.col) ? (pos.col - endPos.col) : (endPos.col - pos.col);
        int  y = (pos.row > endPos.row) ? (pos.row - endPos.row) : (endPos.row - pos.row);
        return ZXDJ * (x + y);
}
*/



void Result::on_pushButton_3_clicked()
{
    QPixmap img("://ziyuan/map1.png");
    QPainter paint(&img);
    QPainterPath path;
    int bgy = (getMyY() -30)/10;
    int bgx = getMyX() /10;
    int edy = getX()*3 - 2;
    int edx = getY()*3 - 2;


    if(bgx>edx&&bgy>edy)
    {
        edy++;
        goto next;
    }


   if(bgx<edx&&bgy<edy)
    {
        edy--;
        goto next;
    }

    if(bgx>edx&&bgy<edy)
    {
        edy--;
        goto next;
    }

    if(bgx<edx&&bgy>edy)
    {
        edy++;
        goto next;
    }

    if(bgx==edx&&bgy>edy)
    {
        edy++;
        goto next;
    }

    if(bgx==edx&&bgy<edy)
    {
        edy--;
        goto next;
    }

    if(bgx>edx&&bgy==edy)
    {
        edx++;
        goto next;
    }

    else if(bgx<edx&&bgy==edy)
    {
        edx--;
        goto next;
    }

next:    QStack<node> re = m_Astar.m(bgy,bgx,edy,edx);
    if(bgx - edx ==1&&bgy == edy)
    {
        path.moveTo(bgx*10 + 5,bgy*10 + 35);
        path.lineTo(edx*10 + 5,edy*10 + 35);
    }
    else
    {
    node now = re.top();
    re.pop();
   // printf("(%d,%d)", now.m_nx, now.m_ny);
    path.moveTo((now.m_ny)*10 + 5,(now.m_nx)*10 + 35);
    qDebug() << now.m_nx << " " << now.m_ny<< " " ;
    while (re.size()) {
        node now = re.top();
        re.pop();
        //printf("-->(%d,%d)", now.m_nx, now.m_ny);
        path.lineTo(( now.m_ny)*10 + 5,(now.m_nx)*10 + 35);
        qDebug() << now.m_nx << " " << now.m_ny<< " " ;
    }
}

    paint.setPen(QPen(Qt::red,3));
   // paint.setPen();
    paint.drawPath(path);
    paint.drawRect(QRect((getY() - 1) * CHUANGKOU_IMAGEY + DESK_IMAGEY,(getX() - 1) * CHUANGKOU_IMAGEX + CHUANGKOU_IMAGEX + DESK_IMAGEX,DRAW_X,DRAW_Y));

    ui->label->setPixmap(img);

}
