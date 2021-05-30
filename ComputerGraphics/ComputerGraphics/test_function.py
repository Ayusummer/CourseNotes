# -*- coding : utf-8 -*-
# @Time      : 2021/5/21 10:57
# @Author    : 咸鱼型233
# @File      : test_function.py
# @Software  : PyCharm
# @Function  : 用于测试函数的文件
# @ChangeLog :
# 第三方库导入
import turtle
from tkinter import messagebox

from basic_draw import draw_circle
from basic_draw import line_to
from Graphic_draw_2D.diamond_draw import diamond_draw
from Graphic_draw_2D.magic_triangle_draw import magic_triangle_draw
from Graphic_draw_2D.recursive_circle_draw import recursive_circle_draw

from Graphic_draw_2D.diamond_draw import diamond_generate_vertex
from Graphic_draw_2D.diamond_draw import diamond_generate_circle
from lineSegmentCut.diamond_clip_draw import clip_draw_diamond

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

# # 大背景定义,绘图模具初始化
turtle.bgcolor("black")  # 还原示例图片中的黑色底色
turtle.speed(0)  # 设置笔头移动速度->0->最快
turtle.ht()  # 隐藏海龟,提高绘制速度

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

print("\n")
print("结束")
turtle.done()
