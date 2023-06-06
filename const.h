/*****************************************************************************/
/*
* \file const.h
* \author zxz
* \date 2022/10/22
* \version TINGSN V1
* \brief 存放常量
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#ifndef CONST_H
#define CONST_H
#define DESK_NUMBER 90 // 座位数
#define DESK_IMAGEX 10 // 座位图片长
#define DESK_IMAGEY 10 // 座位图片宽
#define DESK_MAP_ROW 27 // 桌子和道路的行数
#define DESK_MAP_COL 30 // 桌子和道路的列数
#define ROAD_DESK_DISTENT 3 // 路和桌子的间隔
#define CHUANGKOU_NUMBER 10 // 窗口数
#define CHUANGKOU_IMAGEX 30 // 窗口图片长
#define CHUANGKOU_IMAGEY 30 // 窗口图片宽
#define ROAD_IMAGEX 10 // 路图片长
#define ROAD_IMAGEY 10 // 路图片宽
#define CANTEEN_X 1000 // 商家聊天窗口起始x坐标
#define CANTEEN_Y 200 // 商家聊天窗口起始y坐标
#define CLIENT_X  400 // 用户聊天窗口起始x坐标
#define CLIENT_Y  200 // 用户聊天窗口起始y坐标
#define MIN_INDEX 0 // 最小值坐标
#define DRAW_X 10 // 圈出目标的正方形长
#define DRAW_Y 10 // 圈出目标的正方形宽

const int ZERO   = 0;
const int ONE    = 1;
const int TWO    = 2;
const int THREE  = 3;
const int FOUR   = 4;
const int TIME   = 20; // 发送文件时间间隔
const int PIX_SIZE         = 80; // 标题字号大小
const int BUTTON_HEIGHT   = 50; //按键高度
const int PIX_ZIHAO        = 48; // 按键字号大小


#endif // CONST_H
