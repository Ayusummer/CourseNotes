# -*- coding : utf-8 -*-
# @Time      : 2021/5/23 13:26
# @Author    : 咸鱼型233
# @File      : GlobalTest.py
# @Software  : PyCharm
# @Function  : 随手测试代码的文件
# @ChangeLog :
# 导入第三方库
import turtle

# 导入自定义绘图函数
from ComputerGraphics.basic_draw import draw_circle
from ComputerGraphics.basic_draw import rotate_point
from ComputerGraphics.basic_draw import rotate_point_with_center


def draw_8_circle(center, radius):
    radius = radius / 2
    center1 = [center[0] + 6 * radius, center[1]]
    nums = 8
    while nums != 0:
        center1 = rotate_point_with_center(center1, 45, center)
        draw_circle(center1[0], center1[1], radius)
        nums -= 1


def draw_circles(center, radius):
    draw_circle(center[0], center[1], radius)

    radius1 = radius / 2
    center1 = [center[0] + 6 * radius1, center[1]]
    draw_circle(center1[0], center1[1], radius1)
    draw_8_circle(center1, radius1 / 2)

    nums = 7
    while nums != 0:
        center1 = rotate_point_with_center(center1, 45, center)
        draw_circle(center1[0], center1[1], radius1)
        draw_8_circle(center1, radius1 / 2)
        nums -= 1


turtle.speed(0)

draw_circles([0, 0], 80)

turtle.done()
