# -*- coding : utf-8 -*-
# @Time      : 2021/5/21 10:37
# @Author    : 咸鱼型233
# @File      : basic_draw.py
# @Software  : PyCharm
# @Function  : 
# @ChangeLog :
import turtle
import numpy as np


def draw_circle(x, y, r, extent=None, color='red') -> None:
    """以(x,y)为圆心,r为半径画圆;

    画笔起始点位置并非圆心,而是圆心垂线与下圆弧的交点,然后逆时针画圆

    :param x: 圆心横坐标
    :param y: 圆心纵坐标
    :param r: 圆的半径
    :param extent: 弧度
    :param color: 线条颜色(默认为红色)
    """
    turtle.color(color)  # 设置画笔颜色
    turtle.penup()  # 画笔抬起 -- 移动时不画线
    turtle.goto(x + r, y)  # 将笔尖移动到(x+r,y)
    turtle.setheading(90)  # 海龟朝北
    turtle.pendown()  # 落笔
    turtle.circle(r, extent)  # 画圆


def line_to(v1, v2, color='red'):
    """从v1径直画到v2(默认笔触为红色)

    :param v1: 起始点坐标 : [x1, y1]
    :param v2: 结束点坐标 : [x2, y2]
    :param color: 线条颜色(默认为红色)
    """
    turtle.color(color)  # 设置画笔颜色
    turtle.penup()  # 画笔抬起 -- 移动时不画线
    turtle.goto(v1[0], v1[1])  # 将笔尖移动到(x,y)
    turtle.pendown()  # 落笔
    turtle.goto(v2[0], v2[1])  # 画笔直线移动到(ex,ey)并画线


def rotate_point(point: list, angle) -> list:
    """将一个点(point)绕坐标原点逆时针旋转angle°

    PS : 懒省事不想写绕任意点.jpg

    :param point: 待旋转点
    :param angle: 旋转角度(°)
    """
    angle = ((2 * np.pi) / 360) * angle
    a = round(np.cos(angle), 3)
    b = round(-np.sin(angle), 3)
    c = round(np.sin(angle), 3)
    d = round(np.cos(angle), 3)
    angle_matrix = np.mat([[a, b], [c, d]])
    N = np.mat([[point[0]], [point[1]]])
    S = angle_matrix * N
    S = S.tolist()
    lst = [S[0][0], S[1][0]]
    return lst
