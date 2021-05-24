# -*- coding : utf-8 -*-
# @Time      : 2021/5/21 10:50
# @Author    : 咸鱼型233
# @File      : diamond_draw.py
# @Software  : PyCharm
# @Function  : 
# @ChangeLog :

# 导入第三方库
import turtle
import math

# 导入自定义绘图函数
from ComputerGraphics.basic_draw import line_to
from ComputerGraphics.basic_draw import draw_circle


def diamond_generate_vertex(radius, nums) -> list:
    """金刚石的顶点列表生成函数(外圆上顶点)

    :param radius: 外圆半径
    :param nums: 外圆等分数
    :return: vertex(list of list) 顶点表
    """
    vertex = list()
    for i in range(0, nums):
        # 将圆周上的等分点都加到列表里
        vertex.append([radius * math.cos(2 * math.pi / nums * i),
                       radius * math.sin(2 * math.pi / nums * i)])
    return vertex


def diamond_generate_circle(radius, nums) -> list:
    """金刚石的同心圆列表生成函数

    :param radius: 外圆半径
    :param nums: 外圆等分数
    :return: circle(list of list) [圆心, 半径, 弧度]
    """
    circle = list()
    for i in range(0, nums):
        # 生成同心圆列表
        circle.append([[0, 0], (i + 1) * (radius / nums), 360])
    return circle


def diamond_draw(vertex, radius, nums) -> None:
    """金刚石绘制函数

    PS : 最后一个金刚石图形参数是用来表示整个金刚石图案的信息的,实验四里的裁剪会用上

    :param vertex: 顶点表
    :param radius: 外圆半径 : 用于绘制同心圆,因此这里又把这个参数拿过来了
    :param nums: 外圆等分数 : 其实可以使用vertex的大小,但是不想多计算一步,直接拿来用
    :return: 无返回值 -> 绘制金刚石图案
    """
    turtle.speed(0)  # 设置笔头移动速度->0->最快
    turtle.ht()  # 隐藏海龟,提高绘制速度
    for i in range(0, nums):
        draw_circle(0, 0, (i + 1) * (radius / nums))
    for i in range(0, nums):
        for j in range(i + 1, nums):
            line_to(vertex[i], vertex[j])
