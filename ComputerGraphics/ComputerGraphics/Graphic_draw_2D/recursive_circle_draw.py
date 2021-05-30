# -*- coding : utf-8 -*-
# @Time      : 2021/5/29 11:05
# @Author    : 咸鱼型233
# @File      : recursive_circle_draw.py
# @Software  : PyCharm
# @Function  : 绘制递归圆
# @ChangeLog :
# 导入第三方库
import turtle

# 导入自定义绘图函数
from ComputerGraphics.basic_draw import draw_circle
from ComputerGraphics.basic_draw import rotate_point
from ComputerGraphics.basic_draw import rotate_point_with_center


def recursive_circle_draw(center, radius):
    center = [center[0] + 6 * radius * 0.75, center[1]]
    radius /= 4
    print(center, radius)
    center_spin = [center[0] - 6 * radius, center[1]]
    recursive_circle_draw_know_initial_rubbish(radius, center, center_spin, 64, 2)


def draw_8_circle(center, radius):
    """以 center 为中心, radius 为基准半径绘制一圈 8 个圆

    PS : 迭代画法的辅助函数

    """
    radius = radius / 2
    center1 = [center[0] + 6 * radius, center[1]]
    nums = 8
    while nums != 0:
        center1 = rotate_point_with_center(center1, 45, center)
        draw_circle(center1[0], center1[1], radius)
        nums -= 1


def draw_circles(center, radius):
    """以 center 为中心 radius 为基准半径绘制圆图

    PS : 第三题的迭代画法

    """
    draw_circle(center[0], center[1], radius)

    radius1 = radius / 2
    center1 = [center[0] + 6 * radius1, center[1]]
    draw_circle(center1[0], center1[1], radius1)
    draw_8_circle(center1, radius1 / 2)

    nums = 7
    while nums != 0:
        center1 = rotate_point_with_center(center1, 45, center)
        draw_circle(center1[0], center1[1], radius1)
        draw_8_circle(center1, radius1 / 2)
        nums -= 1


def recursive_circle_draw_know_initial_rubbish(radius, center, center_spin, nums, depth=2):
    """递归圆绘制(已知初始值)

    PS : 递归量越写越多, 写不动了,换个版本

    PS : 此函数已作废

    :param radius: 半径
    :param center: 圆心
    :param center_spin: 旋转中心
    :param nums: 周围已经绘制了的圆的个数
    :param depth: 递归深度
    """
    if depth == 0:
        print("\n结束")
        # draw_circle(center[0], center[1], radius)
    elif nums % 8 != 0 or nums == 8 ** depth:
        print("\n旋转绘图")
        center = rotate_point_with_center(center, 45, center_spin)
        draw_circle(center[0], center[1], radius)
        nums -= 1
        recursive_circle_draw_know_initial_rubbish(radius, center, center_spin, nums, depth)
    elif nums == 0:
        print("这轮小圆已绘制完成,缩圈")
        # 旋转中心内移
        center_spin = [center[0] - 18 * radius, center[1]]
        # 圆心内迁
        center = [center[0] - 6 * radius, center[1]]
        # 半径扩大
        radius *= 2
        # 新一轮 nums 赋值
        nums = 8 ** depth
        # 递归深度缩小
        depth -= 1
        # 显示当前圆心半径
        print(center[0], radius)
        recursive_circle_draw_know_initial_rubbish(radius, center, center_spin, nums, depth)
    elif nums % 8 == 0:
        # 旋转中心旋转
        center_spin = rotate_point_with_center(center_spin, 45, [center[0] - 18 * radius, center[1]])
        print("一圈小圆绘制完成")
        recursive_circle_draw_know_initial_rubbish(radius, center, center_spin, nums, depth)
    # else:
    #     print("\n缩圈")
    #     center_spin = [center[0] - 18 * radius, center[1]]
    #     center = [center[0] - 6 * radius, center[1]]
    #     radius *= 2
    #     nums = 8
    #     depth -= 1
    #     print(center[0], radius)
    #     draw_circle(center[0], center[1], radius)
    #     recursive_circle_draw_know_initial(radius, center, center_spin, nums, depth)


# turtle.speed(0)
# print("\n")
# draw_circles([0, 0], 80)
# # recursive_circle_draw([0, 0], 80)
# turtle.done()
