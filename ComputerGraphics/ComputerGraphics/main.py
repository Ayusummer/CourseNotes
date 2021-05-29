# -*- coding : utf-8 -*-
# @Time      : 2021/5/21 10:39
# @Author    : 咸鱼型233
# @File      : main.py
# @Software  : PyCharm
# @Function  : 
# @ChangeLog :
# 导入第三单方库
import turtle

# 导入自定义函数
from Graphic_draw_2D.diamond_draw import diamond_draw
from Graphic_draw_2D.diamond_draw import diamond_generate_vertex
from Graphic_draw_2D.diamond_draw import diamond_generate_circle
from lineSegmentCut.diamond_clip_draw import clip_draw_diamond
from ComputerGraphics.Graphic_draw_2D.magic_triangle_draw import magic_triangle_draw

# 金刚石相关数据定义
radius = 300  # 外圆半径为300
nums = 24  # 外圆等分数为24
# 生成金刚石的顶点表
vertex_diamond = diamond_generate_vertex(radius, nums)
circle_diamond = diamond_generate_circle(radius, nums)

# 大背景定义,绘图模具初始化,海龟初始化
turtle.bgcolor("black")  # 还原示例图片中的黑色底色
turtle.speed(0)  # 设置笔头移动速度->0->最快
turtle.ht()  # 隐藏海龟,提高绘制速度

# 绘制金刚石
diamond_draw(vertex_diamond, radius, nums)

# 金刚石裁剪
clip_draw_diamond(vertex_diamond, circle_diamond, 0, 300, 300, 0)

# 清屏
turtle.clear()

# 绘制魔术三角形
magic_triangle_draw()

print("\n结束")
turtle.done()
