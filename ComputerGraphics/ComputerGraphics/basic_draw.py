# -*- coding : utf-8 -*-
# @Time      : 2021/5/21 10:37
# @Author    : 咸鱼型233
# @File      : basic_draw.py
# @Software  : PyCharm
# @Function  : 
# @ChangeLog :
import turtle


def draw_circle(x, y, r) -> None:
    """以(x,y)为圆心,r为半径画圆;

    画笔起始点位置并非圆心,而是圆心垂线与下圆弧的交点,然后逆时针画圆

    :param x: 圆心横坐标
    :param y: 圆心纵坐标
    :param r: 圆的半径
    """
    turtle.penup()      # 画笔抬起 -- 移动时不画线
    turtle.goto(x, y)   # 将笔尖移动到(x,y)
    turtle.pendown()    # 落笔
    turtle.circle(r)    # 画圆


def line_to(x, y, ex, ey):
    """
    从(x,y)径直画到(ex,ey)
    """
    turtle.penup()          # 画笔抬起 -- 移动时不画线
    turtle.goto(x, y)       # 将笔尖移动到(x,y)
    turtle.pendown()        # 落笔
    turtle.goto(ex, ey)     # 画笔直线移动到(ex,ey)并画线

