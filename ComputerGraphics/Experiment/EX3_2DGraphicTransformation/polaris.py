# -*- coding: utf-8 -*-
# @Time    : 2021/5/7 8:32
# @Author  : 咸鱼型233
# @File    : polaris.py
# @Software: PyCharm
# @Function:
import turtle


def polaris_draw() -> None:
    """
    初版-绘制北极星外部轮廓[纯黑边][固定顶点值]
    给定了各顶点坐标(毕竟绘制北极星并不是本次实验的重点)
    """
    x_lst = [75, 47, -9, 11, -26, 19, 0, 47, 75, 103, 160, 142, 189, 142, 169, 104]
    y_lst = [0, 113, 96, 155, 181, 199, 255, 246, 343, 246, 266, 208, 181, 161, 85, 114]

    turtle.penup()  # 画笔抬起 -- 移动时不画线
    turtle.goto(x_lst[0], y_lst[0])  # 将笔尖移动到(x,y)
    turtle.pendown()
    for i in range(x_lst.__len__() - 1):
        turtle.goto(x_lst[i + 1], y_lst[i + 1])
    turtle.goto(x_lst[0], y_lst[0])


def polaris_draw_color() -> None:
    """
    version-1.0-绘制一颗北极星[彩边][含内线]
    给定了各顶点坐标(毕竟绘制北极星并不是本次实验的重点)
    """
    turtle.speed(0)  # 设置笔头移动速度->0-最快
    x_lst = [75, 47, -9, 11, -26, 19, 0, 47, 75, 103, 160, 142, 189, 142, 169, 104]
    y_lst = [0, 113, 96, 155, 181, 199, 255, 246, 343, 246, 266, 208, 181, 161, 85, 114]
    # 颜色RGB:橙蓝粉绿
    color_lst = [(249, 134, 105), (71, 177, 249), (249, 49, 249), (94, 249, 94)]
    # turtle色彩模式切换为RGB模式
    turtle.colormode(255)

    # 绘制北极星内线
    for i in [0, 2, 4, 6]:
        turtle.penup()  # 画笔抬起 -- 移动时不画线
        turtle.goto(x_lst[i], y_lst[i])  # 将笔尖移动到(x,y)
        turtle.pendown()
        turtle.color(color_lst[i // 2])
        turtle.goto(x_lst[i + 8], y_lst[i + 8])
    for i in [1, 3, 5, 7]:
        point_color_dict = {1: 0, 3: 2, 5: 2, 7: 0}
        turtle.penup()  # 画笔抬起 -- 移动时不画线
        turtle.goto(x_lst[i], y_lst[i])  # 将笔尖移动到(x,y)
        turtle.pendown()
        turtle.color(color_lst[point_color_dict[i]])
        turtle.goto(x_lst[i + 8], y_lst[i + 8])

    # 绘制北极星轮廓
    # 轮廓点色对应表
    point_color_dict = {0: 0, 1: 1, 2: 1, 3: 2, 4: 2, 5: 3, 6: 3,
                        7: 0, 8: 0, 9: 1, 10: 1, 11: 2, 12: 2, 13: 3, 14: 3, 15: 0}
    turtle.penup()  # 画笔抬起 -- 移动时不画线
    turtle.goto(x_lst[0], y_lst[0])  # 将笔尖移动到(x,y)
    turtle.pendown()
    for i in range(x_lst.__len__() - 1):
        turtle.color(color_lst[point_color_dict[i]])
        turtle.goto(x_lst[i + 1], y_lst[i + 1])
    turtle.color(color_lst[0])
    turtle.goto(x_lst[0], y_lst[0])


if __name__ == '__main__':
    # turtle.setup(width=.75, height=0.5, startx=None, starty=None)  # 窗口宽75%,高50%,水平垂直居中
    turtle.speed(0)  # 设置笔头移动速度->0->最快
    polaris_draw_color()
    # turtle.exitonclick()
    # turtle.done()
    turtle.mainloop()
