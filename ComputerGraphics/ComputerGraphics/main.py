# -*- coding : utf-8 -*-
# @Time      : 2021/5/21 10:39
# @Author    : 咸鱼型233
# @File      : main.py
# @Software  : PyCharm
# @Function  : 
# @ChangeLog :
# 导入第三单方库
import turtle
from tkinter import messagebox

# 导入自定义函数
from Graphic_draw_2D.diamond_draw import diamond_draw
from Graphic_draw_2D.diamond_draw import diamond_generate_vertex
from Graphic_draw_2D.diamond_draw import diamond_generate_circle
from lineSegmentCut.diamond_clip_draw import clip_draw_diamond
from ComputerGraphics.Graphic_draw_2D.magic_triangle_draw import magic_triangle_draw

# 曲线拟合函数导入
from curve_fitting.curve_fitting import Bezier3_4point_on_curve_draw
from curve_fitting.curve_fitting import Bezier3_4control_point_draw
from curve_fitting.curve_fitting import draw_b_spline

# 北极星函数导入
from Graphic_convert_2D.polaris_convert import polaris_draw  # 北极星绘制
from Graphic_convert_2D.polaris_convert import shift_polaris  # 北极星平移
from Graphic_convert_2D.polaris_convert import centrosymmetric_polaris  # 北极星中心对称
from Graphic_convert_2D.polaris_convert import zoom_polaris  # 北极星放缩
from Graphic_convert_2D.polaris_convert import spin_polaris  # 北极星旋转

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
messagebox.showinfo("提示", "绘制金刚石")
diamond_draw(vertex_diamond, radius, nums)

# 金刚石裁剪
messagebox.showinfo("提示", "金刚石裁剪")
clip_draw_diamond(vertex_diamond, circle_diamond, 0, 300, 300, 0)

# 清屏
turtle.clear()

# 绘制魔术三角形
messagebox.showinfo("提示", "绘制魔术三角形")
magic_triangle_draw()

# 曲线拟合
# Bezier 曲线
a = [-600, 100]
b = [-300, 400]
c = [300, 600]
d = [600, 100]
messagebox.showinfo("提示", "根据 4 个控制点绘制 Bezier 曲线")
Bezier3_4control_point_draw(a, b, c, d)  # 根据 4 个控制点绘制 Bezier 曲线
messagebox.showinfo("提示", "根据 4 个曲线上的点绘制 Bezier 曲线")
Bezier3_4point_on_curve_draw(a, b, c, d)  # 根据 4 个曲线上的点绘制 Bezier 曲线
# B 样条曲线
n1 = 7
k1 = 3
nodeVector1 = [0, 0, 0, 0, 1, 2, 3, 4, 5, 5, 5, 5]
X1 = [0, 1, 2, 3, 4, 5, 6, 7]
Y1 = [0, 3, 1, 3, 1, 4, 0, 5]
messagebox.showinfo("提示", "三次 B 样条曲线")
draw_b_spline(n1, k1, nodeVector1, X1, Y1)

# 北极星相关
turtle.clear()

x_lst1 = [75, 47, -9, 11, -26, 19, 0, 47, 75, 103, 160, 142, 189, 142, 169, 104]
y_lst1 = [0, 113, 96, 155, 181, 199, 255, 246, 343, 246, 266, 208, 181, 161, 85, 114]
turtle.speed(0)  # 设置笔头移动速度->0->最快

# 北极星绘制
print("这是一个弹出提示框")
messagebox.showinfo("提示", "北极星绘制")
polaris_draw(x_lst1, y_lst1)

# 缩小一半
lst = zoom_polaris(x_lst1, y_lst1, 0.5)
x_lst1 = lst[0]
y_lst1 = lst[1]
messagebox.showinfo("提示", "北极星缩小一半")
turtle.clear()
polaris_draw(x_lst1, y_lst1)

# 放大一倍
lst = zoom_polaris(x_lst1, y_lst1, 2)
x_lst1 = lst[0]
y_lst1 = lst[1]
messagebox.showinfo("提示", "北极星放大一倍")
turtle.clear()
polaris_draw(x_lst1, y_lst1)

# 平移[-100, -100]
lst = shift_polaris(x_lst1, y_lst1, [-100, -100])
x_lst1 = lst[0]
y_lst1 = lst[1]
messagebox.showinfo("提示", "北极星平移[-100, -100]")
turtle.clear()
polaris_draw(x_lst1, y_lst1)

# 中心旋转90°
lst = spin_polaris(x_lst1, y_lst1, 90)
x_lst1 = lst[0]
y_lst1 = lst[1]
messagebox.showinfo("提示", "北极星逆时针旋转90°")
turtle.clear()
polaris_draw(x_lst1, y_lst1)

# 中心对称
lst = centrosymmetric_polaris(x_lst1, y_lst1)
x_lst1 = lst[0]
y_lst1 = lst[1]
messagebox.showinfo("提示", "北极星中心对称")
turtle.clear()
polaris_draw(x_lst1, y_lst1)

print("\n结束")
turtle.done()
