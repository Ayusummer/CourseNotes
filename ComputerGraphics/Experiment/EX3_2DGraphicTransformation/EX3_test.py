# -*- coding: utf-8 -*-
# @Time    : 2021/5/7 10:34
# @Author  : 咸鱼型233
# @File    : EX3_test.py
# @Software: PyCharm
# @Function:
# coding:utf-8
# coding:utf-8
# coding:utf-8
import turtle
import time

turtle.pensize(30)
turtle.tracer(0)  # 设置为手动将图片更新到屏幕上

for i in range(500):
    # ========4.清除屏幕=========
    turtle.clear()
    # =========1.绘制图片============
    turtle.forward(1)
    # =========2.图片更新到屏幕上=========
    turtle.update()
    # ========3.等待=========
    time.sleep(1 / 30)

turtle.done()
