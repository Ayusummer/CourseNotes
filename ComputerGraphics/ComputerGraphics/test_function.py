# -*- coding : utf-8 -*-
# @Time      : 2021/5/21 10:57
# @Author    : 咸鱼型233
# @File      : test_function.py
# @Software  : PyCharm
# @Function  : 用于测试函数的文件
# @ChangeLog :
from basic_draw import draw_circle
from basic_draw import line_to
from Graphic_draw_2D.diamond_draw import diamond_draw
from Graphic_draw_2D.diamond_draw import diamond_generate_vertex
from Graphic_draw_2D.diamond_draw import diamond_generate_circle
from lineSegmentCut.diamond_clip_draw import clip_draw_diamond


import turtle



# 画圆
# basic_draw.draw_circle(0, 0, 50)

# 画金刚石(旧版函数,为了迎合旧版复杂的数据结构写的函数,返回值是一个三元列表,是列表与字典与列表的嵌套)
# diamond = Graphic_draw_2D.diamond_draw.diamond_draw(300, 24)   # 半径300,圆周24等分绘制金刚石

# 大背景定义,绘图模具初始化
turtle.bgcolor("black")  # 还原示例图片中的黑色底色

# 生成金刚石的顶点表并绘制金刚石
vertex_diamond = diamond_generate_vertex(300, 24)
circle_diamond = diamond_generate_circle(300, 24)
diamond_draw(vertex_diamond, 300, 24)

# turtle.reset()
# lineSegmentCut.Sutherland_Cohen_abandoned.clip_diamond(diamond, 0, 300, 300, 0, 24, 300)
clip_draw_diamond(vertex_diamond, circle_diamond, 0, 300, 300, 0)

print("\n")
print("结束")
turtle.done()

