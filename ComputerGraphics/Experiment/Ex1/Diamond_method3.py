# -*- coding: utf-8 -*-
# @Time    : 2021/4/9 20:16
# @Author  : 咸鱼型233
# @File    : Diamond_method3.py
# @Software: PyCharm
# @Function: 金刚石绘制方法三
"""
假设有n个点。
规则:从当前起点按顺序查找与之没有相连的第一个顶点
    若存在，则画线到该顶点，重复上述步骤，直到不存在与之没有相连的顶点为止。
"""
"""
仔细看老师给的示例图发现同心圆的个数与圆周等分数并不一致
但是看起来同心圆的数目还是越多越好看些,因此索性同心圆的数目与圆周的等分数一致
"""



import turtle
import math
from time import sleep


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
    radius = int(turtle.textinput('半径', '请输入半径'))           # 通过对话框获取用户输入半径
    nums = int(turtle.textinput('等分数', '请输入圆周等分数'))       # 通过对话框获取用户输入的圆周等分数
    turtle.setup(width=.75, height=0.5, startx=None, starty=None)   # 窗口宽75%,高50%,水平垂直居中
    turtle.speed(0)     # 设置笔头移动速度->0->最快
    x_list = []
    y_list = []
    for i in range(0, nums):
        x_list.append(radius * math.cos(2 * math.pi / nums * i))
        y_list.append(radius * math.sin(2 * math.pi / nums * i))
        draw_circle(0, -(i/nums)*radius, (i/nums)*radius)
    # for i in range(0, x_list.__len__()):
    #     for j in range(0, x_list.__len__()):
    #         line_to(x_list[i], y_list[i], x_list[j], y_list[j])
    for i in range(0, x_list.__len__()):
        for j in range(0, x_list.__len__()):
            line_to(x_list[i], y_list[i], x_list[j], y_list[j])
    sleep(100)

