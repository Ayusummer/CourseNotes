# -*- coding : utf-8 -*-
# @Time      : 2021/5/30 20:25
# @Author    : 咸鱼型233
# @File      : polaris_convert.py
# @Software  : PyCharm
# @Function  : 
# @ChangeLog :
import turtle

import numpy as np

from ComputerGraphics.basic_draw import line_to

from ComputerGraphics.basic_draw import rotate_point


def polaris_draw(x_lst, y_lst) -> None:
    """
    version-1.0-绘制一颗北极星[彩边][含内线]
    给定了各顶点坐标(毕竟绘制北极星并不是本次实验的重点)
    """
    # 颜色RGB:橙蓝粉绿
    color_lst = [(249, 134, 105), (71, 177, 249), (249, 49, 249), (94, 249, 94)]
    # turtle色彩模式切换为RGB模式
    turtle.colormode(255)

    # 绘制北极星内线
    for i in [0, 2, 4, 6]:
        line_to([x_lst[i], y_lst[i]],
                [x_lst[i + 8], y_lst[i + 8]],
                color_lst[i // 2])
    for i in [1, 3, 5, 7]:
        point_color_dict = {1: 0, 3: 2, 5: 2, 7: 0}
        line_to([x_lst[i], y_lst[i]],
                [x_lst[i + 8], y_lst[i + 8]],
                color_lst[point_color_dict[i]])

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


def zoom_polaris(x_lst, y_lst, times):
    """北极星缩放函数

    PS : 早期写的北极星绘制不想改了,用的横纵坐标表,没有打组成顶点表,因此这里参数沿用了横纵坐标表

    PS2 : 中心缩放.jpg  北极星顶点表设计的太拉了

    :param x_lst: 横坐标表
    :param y_lst: 纵坐标表
    :param times: 缩放倍率(> 0)(<1 -> 缩小; >1 -> 放大)
    :return: 返回更新后的横纵坐标表
    """
    Convert = np.mat([
        [times, 0, 0],
        [0, times, 0],
        [0, 0, 1]
    ])
    for i in range(x_lst.__len__()):
        A0 = np.mat([
            [x_lst[i]],
            [y_lst[i]],
            [1]
        ])
        S = Convert * A0
        S.tolist()
        # print(S)
        # 浮点计算误差可能导致 turtle 出错,直接转成 int 了
        x_lst[i] = int(S[0][0])
        y_lst[i] = int(S[1][0])
    return [x_lst, y_lst]


def shift_polaris(x_lst, y_lst, vector_shift):
    """北极星缩放函数

    PS : 早期写的北极星绘制不想改了,用的横纵坐标表,没有打组成顶点表,因此这里参数沿用了横纵坐标表

    PS2 : 中心缩放.jpg  北极星顶点表设计的太拉了

    :param x_lst: 横坐标表
    :param y_lst: 纵坐标表
    :param vector_shift: 平移向量
    :return: 返回更新后的横纵坐标表
    """
    Convert = np.mat([
        [1, 0, vector_shift[0]],
        [0, 1, vector_shift[1]],
        [0, 0, 1]
    ])
    for i in range(x_lst.__len__()):
        A0 = np.mat([
            [x_lst[i]],
            [y_lst[i]],
            [1]
        ])
        S = Convert * A0
        S.tolist()
        # print(S)
        # 浮点计算误差可能导致 turtle 出错,直接转成 int 了
        x_lst[i] = int(S[0][0])
        y_lst[i] = int(S[1][0])
    return [x_lst, y_lst]


def spin_polaris(x_lst, y_lst, angle):
    """北极星旋转函数

    PS : 早期写的北极星绘制不想改了,用的横纵坐标表,没有打组成顶点表,因此这里参数沿用了横纵坐标表

    PS2 : 中心旋转.jpg  北极星顶点表设计的太拉了

    :param x_lst: 横坐标表
    :param y_lst: 纵坐标表
    :param angle: 逆时针旋转角度
    :return: 返回更新后的横纵坐标表
    """
    for i in range(x_lst.__len__()):
        S = rotate_point([x_lst[i], y_lst[i]], angle)
        # 浮点计算误差可能导致 turtle 出错,直接转成 int 了
        x_lst[i] = int(S[0])
        y_lst[i] = int(S[1])
    return [x_lst, y_lst]


def centrosymmetric_polaris(x_lst, y_lst):
    """北极星中心对称函数

    PS : 早期写的北极星绘制不想改了,用的横纵坐标表,没有打组成顶点表,因此这里参数沿用了横纵坐标表

    PS2 : 中心旋转.jpg  北极星顶点表设计的太拉了

    :param x_lst: 横坐标表
    :param y_lst: 纵坐标表
    :return: 返回更新后的横纵坐标表
    """
    for i in range(x_lst.__len__()):
        x_lst[i] = -x_lst[i]
        y_lst[i] = -y_lst[i]
    return [x_lst, y_lst]

#
# if __name__ == '__main__':
#     x_lst1 = [75, 47, -9, 11, -26, 19, 0, 47, 75, 103, 160, 142, 189, 142, 169, 104]
#     y_lst1 = [0, 113, 96, 155, 181, 199, 255, 246, 343, 246, 266, 208, 181, 161, 85, 114]
#     turtle.speed(0)  # 设置笔头移动速度->0->最快
#
#     # 北极星绘制
#     polaris_draw(x_lst1, y_lst1)
#
#     # 缩小一半
#     turtle.clear()
#     lst = zoom_polaris(x_lst1, y_lst1, 0.5)
#     x_lst1 = lst[0]
#     y_lst1 = lst[1]
#     polaris_draw(x_lst1, y_lst1)
#
#     # 放大一倍
#     turtle.clear()
#     lst = zoom_polaris(x_lst1, y_lst1, 2)
#     x_lst1 = lst[0]
#     y_lst1 = lst[1]
#     polaris_draw(x_lst1, y_lst1)
#
#     # 平移[-100, -100]
#     turtle.clear()
#     lst = shift_polaris(x_lst1, y_lst1, [-100, -100])
#     x_lst1 = lst[0]
#     y_lst1 = lst[1]
#     polaris_draw(x_lst1, y_lst1)
#
#     # 中心旋转90°
#     turtle.clear()
#     lst = spin_polaris(x_lst1, y_lst1, 90)
#     x_lst1 = lst[0]
#     y_lst1 = lst[1]
#     polaris_draw(x_lst1, y_lst1)
#
#     # 中心对称
#     turtle.clear()
#     lst = centrosymmetric_polaris(x_lst1, y_lst1)
#     x_lst1 = lst[0]
#     y_lst1 = lst[1]
#     polaris_draw(x_lst1, y_lst1)
#
#     turtle.done()
