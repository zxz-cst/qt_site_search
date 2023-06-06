/*****************************************************************************/
/*
* \file node.cpp
* \author zxz
* \date 2022/10/28
* \version TINGSN V1
* \brief 查找最优路径方法
* \note Copyright (c) 2020-2030 南京理工大学
* \remarks 修改日志
******************************************************************************/
#include "node.h"
#include <QDebug>
//存放父节点
static QStack<node> st;
static node pre[N][N];
node::node()
{

}


node::node(int x, int y, int cost, int rest) {
    this->hasInited = true;
    this->m_nx = x;
    this->m_ny = y;
    this->cost = cost;
    this->rest = rest;

}

QStack<node> node::m(int sx,int sy,int ex,int ey)
{


    memset(vis, 0, sizeof vis);
    memset(pre, 0, sizeof pre);
    memset(in_queue, 0, sizeof in_queue);
    /*sx = 4;
    sy = 7;
    ex = 18;
    ey = 11;*/
   // map[sx][sy] = 1;

    bfs_astar(node(sx, sy, 0, abs(ex - sx) + abs(ey - sy)), node(ex, ey, map[ex][ey], 0));
    QStack<node> re = st;
    return re;

}

bool node::ok(int x, int y) {
    return x >= 0 && y >= 0 && x < N&& y < N&& map[x][y] > 0 && !vis[x][y];
}

void node::print_path() {
  //  printf("打印路径.....\n");
    node now = st.top();
    st.pop();
   // printf("(%d,%d)", now.m_nx, now.m_ny);
    qDebug() << now.m_nx << " " << now.m_ny<< " " ;
    while (st.size()) {
        node now = st.top();
        st.pop();
        //printf("-->(%d,%d)", now.m_nx, now.m_ny);
        qDebug() << now.m_nx << " " << now.m_ny<< " " ;
    }
    qDebug()<<'\n';
}

bool node::bfs_astar(node start, node end) {
    std::priority_queue<node> q;
    q.push(start);
    in_queue[start.m_nx][start.m_ny] = true;
    vis[start.m_nx][start.m_ny] = true;
    node now;
    int x, y, nx, ny;
    while (q.size()) {
        now = q.top();
        q.pop();
        x = now.m_nx;
        y = now.m_ny;
        vis[x][y] = true;
        in_queue[x][y] = false;
       // printf("当前位置%d %d\n", x, y);
        // 判断是否是终点
        if (now == end) {
           // printf("找到终点\n");
            st.push(now);
            while (pre[now.m_nx][now.m_ny].hasInited) {
                now = pre[now.m_nx][now.m_ny];
                st.push(now);
            }
           // print_path();

            return true;
        }
        for (int i = 0;i < 8;i++) {
            nx = x + dir[i][0];
            ny = y + dir[i][1];
            if (ok(nx, ny)) {
                //计算cost rest值
                int cost = now.cost + map[nx][ny];
                int rest = abs(end.m_nx - nx) + abs(end.m_ny - ny);
                if (in_queue[nx][ny]) {
                    priority_queue<node> qq;
                    while (q.size()) {
                        node temp = q.top();
                        q.pop();
                        if (temp.m_nx == nx && temp.m_ny == ny) {
                            if (temp.cost > cost) {
                                temp.cost = cost;
                                pre[nx][ny] = now;
                            }
                        }
                        qq.push(temp);
                    }
                    q = qq;
                }
                pre[nx][ny] = now;
                q.push(node(nx, ny, cost, rest));
                in_queue[nx][ny] = true;
            }
        }
    }
    return false;
}
bool node::bfs(node start, node end) {
    queue<node> q;
    q.push(start);
    vis[start.m_nx][start.m_ny] = true;
    node now;
    int x, y, nx, ny;
    while (q.size()) {
        now = q.front();
        q.pop();
        x = now.m_nx;
        y = now.m_ny;
        vis[x][y] = true;
       // printf("当前位置%d %d\n", x, y);
        // 判断是否是终点
        if (x == end.m_nx && y == end.m_ny) {
          //  printf("找到终点\n");
            return true;
        }
        for (int i = 0;i < 8;i++) {
            nx = x + dir[i][0];
            ny = y + dir[i][1];
            if (ok(nx, ny)) {
                q.push(node(nx, ny, 0, 0));
            }
        }
    }
    return false;
}
