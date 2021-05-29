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
from Graphic_draw_2D.diamond_draw import diamond_draw_no_interrupt
from Graphic_draw_2D.diamond_draw import diamond_generate_vertex
from Graphic_draw_2D.diamond_draw import diamond_generate_circle
from lineSegmentCut.diamond_clip_draw import clip_draw_diamond

import turtle


radius = 300    # 外圆半径为300
nums = 24       # 外圆等分数为24

# 大背景定义,绘图模具初始化
turtle.bgcolor("black")  # 还原示例图片中的黑色底色

# 生成金刚石的顶点表并绘制金刚石
vertex_diamond = diamond_generate_vertex(radius, nums)
circle_diamond = diamond_generate_circle(radius, nums)
turtle.speed(0)  # 设置笔头移动速度->0->最快
turtle.ht()  # 隐藏海龟,提高绘制速度
diamond_draw(vertex_diamond, radius, nums)


# clip_draw_diamond(vertex_diamond, circle_diamond, 0, 300, 300, 0)

print("\n")
print("结束")
turtle.done()
