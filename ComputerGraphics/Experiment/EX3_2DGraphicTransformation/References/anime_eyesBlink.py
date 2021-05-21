# -*- coding: utf-8 -*-
# @Time    : 2021/5/7 9:04
# @Author  : CSDN@梁梁LYQF : https://blog.csdn.net/weixin_44817017/article/details/88878941
# @File    : anime_eyesBlink.py
# @Software: PyCharm
# @Function:
import turtle
from time import sleep

# 定义画布的大小和背景
turtle.screensize(300, 200, "yellow")

# 定义画笔的速度
turtle.speed(0)


# 定义一个在不同位置画不同弧度
def hudu(x, r, y, t, f):
    turtle.penup()
    turtle.goto(x, r)
    turtle.pendown()
    turtle.left(y)
    turtle.circle(t, f)


# 定义一个画全脸的函数
def lian():
    # 左眼睛
    hudu(-240, 0, 90, -90, 180)

    # 右眼睛
    hudu(50, 0, 180, -90, 180)

    # 鼻子
    hudu(-15, -40, 0, 0, 0)
    turtle.fillcolor("black")
    turtle.begin_fill()
    turtle.left(90)
    turtle.forward(30)
    turtle.right(150)
    turtle.forward(20)
    turtle.right(60)
    turtle.forward(20)
    turtle.end_fill()

    # 嘴巴-下嘴唇
    hudu(120, -105, 120, 0, 0)
    turtle.fillcolor("red")
    turtle.begin_fill()
    turtle.circle(-120, 177)
    turtle.end_fill()

    # 嘴巴-上嘴唇
    hudu(0, -100, 160, 0, 0)
    turtle.fillcolor("yellow")
    turtle.begin_fill()
    turtle.circle(-70, 150)
    hudu(0, -100, 190, 70, 140)
    turtle.end_fill()


# 动画：让脸笑起来的动画——眨眼
turtle.tracer(False)
turtle.hideturtle()

# 设置一个循环不停地眨眼
for i in range(30000):
    turtle.reset()
    turtle.pensize(6)
    lian()
    # 闭眼
    if i % 2 == 0:
        hudu(-240, 0, -10, -100, 127)
        hudu(50, 0, 125, -100, 127)
        turtle.update()
        sleep(0.5)
    # 睁眼
    else:
        hudu(-240, 0, -125, 110, 110)
        hudu(50, 0, -110, 110, 110)
        turtle.fillcolor("black")
        turtle.begin_fill()
        hudu(-120, 0, 0, 40, 360)
        turtle.end_fill()
        turtle.fillcolor("black")
        turtle.begin_fill()
        hudu(175, 0, 0, 40, 360)
        turtle.end_fill()
        turtle.update()
        sleep(0.5)

turtle.exitonclick()
