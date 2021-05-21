# -*- coding: utf-8 -*-
# @Time    : 2021/3/19 17:08
# @Author  : 咸鱼型233
# @File    : GlobalTest.py
# @Software: PyCharm
# @Function: 原始版本,只采集用户输入的圆的半径,然后将圆周分成30等分进行绘制


import turtle
import math


def draw_circle(x, y, r) -> None:
    """
    以(x,y)为圆心,r为半径画圆;

    参数
    ------
    x : 圆心横坐标

    y : 圆心纵坐标

    r : 圆的半径

    """
    turtle.penup()          # 画笔抬起 -- 移动时不画线
    turtle.goto(x, y)       # 将笔尖移动到(x,y)
    turtle.pendown()        # 落笔
    turtle.circle(r)        # 画圆


def line_to(x, y, ex, ey):
    """
    从(x,y)径直画到(ex,ey)
    """
    turtle.penup()          # 画笔抬起 -- 移动时不画线
    turtle.goto(x, y)       # 将笔尖移动到(x,y)
    turtle.pendown()        # 落笔
    turtle.goto(ex, ey)     # 画笔直线移动到(ex,ey)并画线


if __name__ == '__main__':
    radius = int(turtle.textinput('半径', '请输入半径'))        # 通过对话框获取用户输入半径
    turtle.setup(width=.75, height=0.5, startx=None, starty=None)   # 窗口宽75%,高50%,水平垂直居中
    turtle.speed(0)     # 设置笔头移动速度->0->最快
    x_list = []
    y_list = []

    for i in range(0, 30):
        x_list.append(radius * math.cos(math.pi / 15 * i))
        y_list.append(radius * math.sin(math.pi / 15 * i))
        draw_circle(0, (i + 1) * -(radius / 30), (i + 1) * (radius / 30))
    for i in range(0, x_list.__len__()):
        for j in range(0, x_list.__len__()):
            line_to(x_list[i], y_list[i], x_list[j], y_list[j])

