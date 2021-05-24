# -*- coding : utf-8 -*-
# @Time      : 2021/5/24 11:17
# @Author    : 咸鱼型233
# @File      : diamond_clip_draw.py
# @Software  : PyCharm
# @Function  : 
# @ChangeLog :
import turtle
from ComputerGraphics.basic_draw import draw_circle
from ComputerGraphics.basic_draw import line_to
from ComputerGraphics.lineSegmentCut.Sutherland_Cohen import sutherland_cohen


def clip_circle_rectangle_special(xL, yT, xR, yB, circle=None):
    """这又是一个例程特化型函数,只考虑矩形内含圆形时矩形裁剪框对圆形的裁剪

    :param circle : 圆形图案的参数 [圆心列表, 半径数值, 弧度]
    :param xL: 裁剪窗口左上角x坐标, 左边沿
    :param yT: 裁剪窗口左上角y坐标, 上边沿
    :param xR: 裁剪窗口右下角x坐标, 右边沿
    :param yB: 裁剪窗口右下角y坐标, 下边沿
    :return: 返回圆周被切割后剩下的弧度范围(从圆周 最右边的点 算起)
    """
    # 不想写了.jpg 直接靠例程写了, 例程里固定切分 1/4 圆, 因此直接返回 90 (逆时针绘制90°)(注意设置海龟在右点并朝北)
    return 90


def clip_draw_diamond(vertex, circle, xL, xR, yT, yB) -> None:
    """实验特供型金刚石裁剪及绘制函数

    :param vertex: 金刚石顶点表
    :param circle: 金刚石同心圆表
    :param xL: 左框线
    :param xR: 右框线
    :param yT: 上框线
    :param yB: 下框线
    :return: 无返回值 -> 实验特供裁剪及绘制金刚石
    """
    turtle.speed(0)  # 设置笔头移动速度->0->最快
    turtle.ht()  # 隐藏海龟,提高绘制速度
    turtle.setheading(90)  # 海龟朝北

    nums = len(vertex)

    # 绘制同心圆裁剪情况
    for i in range(nums):
        circle[i][2] = clip_circle_rectangle_special(xL, xR, yT, yB)
        x = circle[i][0][0]
        y = circle[i][0][1]
        r = circle[i][1]
        extent = circle[i][2]
        draw_circle(x, y, r, extent, 'green')

    # 绘制金刚石线段裁剪情况
    for i in range(nums):
        for j in range(i+1, nums):
            line_segment = sutherland_cohen([vertex[i], vertex[j]], xL, yT, xR, yB)
            if line_segment:
                line_to(line_segment[0], line_segment[1], 'green')

