# -*- coding : utf-8 -*-
# @Time      : 2021/5/29 8:40
# @Author    : 咸鱼型233
# @File      : magic_triangle_draw.py
# @Software  : PyCharm
# @Function  : 绘制魔术三角形
# @ChangeLog :
# 导入第三方库
import turtle
import math

# 导入自定义绘图函数
from ComputerGraphics.basic_draw import line_to
from ComputerGraphics.basic_draw import rotate_point


def magic_triangle_draw():
    """魔术三角形绘制

    """
    a = [50, -50/math.sqrt(3)]
    b = [-150, -50/math.sqrt(3)]
    c = [50, 200*math.sqrt(3)-50/math.sqrt(3)]
    d = [-50, 200*math.sqrt(3)-50/math.sqrt(3)]
    e = [-300, -50/math.sqrt(3)-50*math.sqrt(3)]
    f = [100, -50/math.sqrt(3)-50*math.sqrt(3)]
    vertex = [a, b, c, d, e, f]
    turtle.begin_fill()
    for i in range(vertex.__len__() - 1):
        line_to(vertex[i], vertex[i+1], "pink")
    line_to(vertex[-1], vertex[0], "pink")
    turtle.end_fill()

    for i in range(vertex.__len__()):
        vertex[i] = rotate_point(vertex[i], 120)
    turtle.begin_fill()
    for i in range(vertex.__len__() - 1):
        line_to(vertex[i], vertex[i+1], "red")
    line_to(vertex[-1], vertex[0], "red")
    turtle.end_fill()

    for i in range(vertex.__len__()):
        vertex[i] = rotate_point(vertex[i], 120)
    turtle.begin_fill()
    for i in range(vertex.__len__() - 1):
        line_to(vertex[i], vertex[i+1], "yellow")
    line_to(vertex[-1], vertex[0], "yellow")
    turtle.end_fill()


