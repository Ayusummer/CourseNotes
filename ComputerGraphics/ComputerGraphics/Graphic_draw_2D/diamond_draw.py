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
from time import sleep

# 导入自定义绘图函数
from ComputerGraphics.basic_draw import line_to
from ComputerGraphics.basic_draw import draw_circle


def diamond_draw(radius, nums):
    # radius = int(turtle.textinput('半径', '请输入半径'))  # 通过对话框获取用户输入半径
    # nums = int(turtle.textinput('等分数', '请输入圆周等分数'))  # 通过对话框获取用户输入的圆周等分数
    # turtle.setup(width=.75, height=0.5, startx=None, starty=None)  # 窗口宽75%,高50%,水平垂直居中
    turtle.speed(0)  # 设置笔头移动速度->0->最快
    x_list = []
    y_list = []
    for i in range(0, nums):
        x_list.append(radius * math.cos(2 * math.pi / nums * i))
        y_list.append(radius * math.sin(2 * math.pi / nums * i))
        draw_circle(0, -(i / nums) * radius, (i / nums) * radius)
    # for i in range(0, x_list.__len__()):
    #     for j in range(0, x_list.__len__()):
    #         line_to(x_list[i], y_list[i], x_list[j], y_list[j])
    for i in range(0, x_list.__len__()):
        for j in range(0, x_list.__len__()):
            line_to(x_list[i], y_list[i], x_list[j], y_list[j])
    # sleep(100)
    turtle.done()
