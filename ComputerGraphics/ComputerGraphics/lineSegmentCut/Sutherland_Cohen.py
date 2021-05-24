# -*- coding : utf-8 -*-
# @Time      : 2021/5/24 9:41
# @Author    : 咸鱼型233
# @File      : Sutherland_Cohen.py
# @Software  : PyCharm
# @Function  : 编码裁剪法
# @ChangeLog : 与之前弃用的版本作区分, 上一版为了迎合复杂的数据结构,洋洋洒洒写了四百多行,虽然文档写的比较详细,但是就一个脚本而言还是太长了
#              因此本版只用于编码裁剪方案的定义
import math


def encode_sutherland_cohen_int(xL, xR, yT, yB, v) -> int:
    """编码裁剪算法的编码函数->返回整形编码数据

    PS1 : 毕竟上一版已经很笨了,判断八次最后生成个列表,还不如直接判断8次生成一个整型的编码,这样下一步还可以用位运算简化逻辑

    PS2 : 点与区域边沿重合也算在区域内

    PS3 : 这版函数将原本的零散的横纵坐标参数去掉了,改用坐标列表

    :param xL: 左框线
    :param xR: 右框线
    :param yT: 上框线
    :param yB: 下框线
    :param v: 待编码点坐标[x, y]
    :return: 整型数据,对应九个区域的编码值
    """
    encode = 0
    x = v[0]
    y = v[1]
    if y > yT:
        if x < xL:
            encode = 9
        elif x > xR:
            encode = 10
        else:
            encode = 8
    elif y < yB:
        if x < xL:
            encode = 5
        elif x > xR:
            encode = 6
        else:
            encode = 4
    else:
        if x < xL:
            encode = 1
        elif x > xR:
            encode = 2
        else:
            encode = 0
    return encode


def location_relation(code1, code2) -> int:
    """判断线段与裁剪窗口的位置关系

    :param code1: 一个端点的编码值
    :param code2: 另一个端点的编码值
    :return:  0 -> 线段在区域外;   1 -> 线段在区域内;
              2->线段与区域有交点且前点在区域内  3 -> 线段与区域有交点且后点在区域内
              4 -> 线段端点都在区域外且与区域有交点
    """
    if code1 & code2 != 0:
        return 0
    elif code1 == 0 and code2 == 0:
        return 1
    else:
        if code1 == 0:
            return 2
        elif code2 == 0:
            return 3
        else:
            return 4


def intersection_line_xLine_noParallel(p_lst, x_line) -> list:
    """求线段所在直线与一条与x轴垂直的直线的交点的坐标(线段不得与直线平行)

    PS : 规定线段不能与直线平行,因为这个函数本质上还是为编码裁剪服务,
         线段和矩形都是有定义域的,因此平行的情况要写的话还是要特殊化
         因此索性这里就写个普遍的线段与直线相交情况求交点坐标

    :param p_lst: (list of list of int: [[x0, y0], [x1, y1]]) 线段的起点和终点坐标
    :param x_line: 一条与 x 轴垂直的直线与 x 轴交点的横坐标
    :return: list -> 线段所在直线与一条与x轴垂直的直线的交点的坐标[x_line, y]
    """
    xA = p_lst[0][0]
    yA = p_lst[0][1]
    xB = p_lst[1][0]
    yBB = p_lst[1][1]
    return [x_line, (x_line * (yA - yBB) + xA * yBB - yA * xB) / (xA - xB)]


def intersection_line_yLine_noParallel(p_lst, y_line) -> list:
    """求线段所在直线与一条与 y 轴垂直的直线的交点的坐标(线段不得与直线平行)

    :param p_lst: (list of list of int: [[x0, y0], [x1, y1]])
    :param y_line: 一条与 y 轴垂直的直线与 y 轴交点的纵坐标
    :return: list -> 线段所在直线与一条与 y 轴垂直的直线的交点的坐标 [x, y_line]
    """
    xA = p_lst[0][0]
    yA = p_lst[0][1]
    xB = p_lst[1][0]
    yBB = p_lst[1][1]
    return [(y_line * (xA - xB) + yA * xB - xA * yBB) / (yA - yBB), y_line]


def intersection_line_rectangle_v1outRec_v2inRec(p_lst, xL, yT, xR, yB) -> list:
    """求线段与矩形的交点(前者在矩形外, 后者在矩形内)

    PS2 : 为了方便写注释, 该函数中线段的两个端点按照参数传入顺序统称为A点和B点

    :param p_lst: (list of list of int: [[x0, y0], [x1, y1]]) 线段的起点和终点坐标(前者在矩形外,后者在矩形内)
    :param xL: 裁剪窗口左上角x坐标, 左边沿
    :param yT: 裁剪窗口左上角y坐标, 上边沿
    :param xR: 裁剪窗口右下角x坐标, 右边沿
    :param yB: 裁剪窗口右下角y坐标, 下边沿
    :return: (list of int: [x_0, y_0] -> 线段与矩形的交点以及原本在矩形内部的点坐标组成的列表
    """
    # 这里取出列表是为了减少列表访问次数, 参数传入列表是为了传参方便
    xA = p_lst[0][0]
    yA = p_lst[0][1]
    xB = p_lst[1][0]
    yBB = p_lst[1][1]
    intersection_point = list()

    # 线段与 x 轴垂线平行
    if xA == xB:
        if yA > yT:
            return [[xA, yT], p_lst[1]]
        elif yA < yB:
            return [[xA, yB], p_lst[1]]
        else:
            pass  # 不可能出现的情况, 这里是为了补全逻辑

    # 线段与 y 轴垂线平行
    if yA == yBB:
        if xA < xL:
            return [[xL, yA], p_lst[1]]
        elif xA > xR:
            return [[xR, yA], p_lst[1]]
        else:
            pass  # 补全逻辑

    # A 点在区域左侧
    if xA < xL:
        # A 点在区域左上方
        if yA > yT:
            # 线段所在直线与 xL 的交点在区域上方那么线段与矩形的交点只可能是其所在直线与矩形上边框的交点
            if intersection_line_xLine_noParallel(p_lst, xL)[1] > yT:
                intersection_point = intersection_line_yLine_noParallel(p_lst, yT)
            # 交点不是与上边框的交点就是与左边框的交点
            else:
                intersection_point = intersection_line_xLine_noParallel(p_lst, xL)
        # A 点在区域左下方
        elif yA < yB:
            # 线段所在直线与 xL 的交点在区域下方那么线段与矩形的交点只可能是其所在直线与矩形下边框的交点
            if intersection_line_xLine_noParallel(p_lst, xL)[1] < yB:
                intersection_point = intersection_line_yLine_noParallel(p_lst, yB)
            # 交点不是与下边框的交点就是与左边框的交点
            else:
                intersection_point = intersection_line_xLine_noParallel(p_lst, xL)
        # A 点在区域正左方
        else:
            intersection_point = intersection_line_xLine_noParallel(p_lst, xL)

    # A 点在区域右侧
    elif xA > xR:
        # A 点在区域右上方
        if yA > yT:
            # 线段所在直线与 xR 的交点在区域上方那么线段与矩形的交点只可能是其所在直线与矩形上边框的交点
            if intersection_line_xLine_noParallel(p_lst, xR) > yT:
                intersection_point = intersection_line_yLine_noParallel(p_lst, yT)
            # 交点不是与上边框的交点就是与右边框的交点
            else:
                intersection_point = intersection_line_xLine_noParallel(p_lst, xR)
        # A 点在区域右下方
        elif yA < yB:
            # 线段所在直线与 xR 的交点在区域下方那么线段与矩形的交点只可能是其所在直线与矩形下边框的交点
            if intersection_line_xLine_noParallel(p_lst, xR) < yB:
                intersection_point = intersection_line_yLine_noParallel(p_lst, yB)
            # 交点不是与下边框的交点就是与右边框的交点
            else:
                intersection_point = intersection_line_xLine_noParallel(p_lst, xR)
        # A 点在区域正右方
        else:
            intersection_point = intersection_line_xLine_noParallel(p_lst, xR)

    # A 点在区域正上方
    elif yA > yT:
        intersection_point = intersection_line_yLine_noParallel(p_lst, yT)

    # A 点在区域正下方
    elif yA < yB:
        intersection_point = intersection_line_yLine_noParallel(p_lst, yB)
    return [intersection_point, p_lst[1]]


def intersection_line_rectangle_v1v2outRec_two_point(p_lst, xL, yT, xR, yB) -> list:
    """求线段与矩形的交点(两者均在矩形外且与矩形有交点)

    PS2 : 为了方便写注释, 该函数中线段的两个端点按照参数传入顺序统称为A点和B点

    :param p_lst: (list of list of int: [[x0, y0], [x1, y1]]) 线段的起点和终点坐标
    :param xL: 裁剪窗口左上角x坐标, 左边沿
    :param yT: 裁剪窗口左上角y坐标, 上边沿
    :param xR: 裁剪窗口右下角x坐标, 右边沿
    :param yB: 裁剪窗口右下角y坐标, 下边沿
    :return: (list of int: [x_0, y_0] -> 线段与矩形的交点以及原本在矩形内部的点坐标组成的列表
    """
    # 这里取出列表是为了减少列表访问次数, 参数传入列表是为了传参方便
    xA = p_lst[0][0]
    yA = p_lst[0][1]
    xB = p_lst[1][0]
    yBB = p_lst[1][1]
    intersection_point = list()

    # 线段与 x 轴垂线平行
    if xA == xB:
        return [[xA, yT], [xA, yB]]
    # 线段与 y 轴垂线平行
    elif yA == yBB:
        return [[xL, yA], [xR, yA]]

    # 线段与矩形所有边框都不平行
    point_xL = intersection_line_xLine_noParallel(p_lst, xL)
    point_xR = intersection_line_xLine_noParallel(p_lst, xR)
    point_yT = intersection_line_yLine_noParallel(p_lst, yT)
    point_yB = intersection_line_yLine_noParallel(p_lst, yB)

    # 将在矩形内的点收录进交点列表
    if encode_sutherland_cohen_int(xL, yT, xR, yB, point_xL) == 0:
        intersection_point.append(point_xL)
    if encode_sutherland_cohen_int(xL, yT, xR, yB, point_xR) == 0:
        intersection_point.append(point_xR)
    if encode_sutherland_cohen_int(xL, yT, xR, yB, point_yT) == 0:
        intersection_point.append(point_yT)
    if encode_sutherland_cohen_int(xL, yT, xR, yB, point_yB) == 0:
        intersection_point.append(point_yB)

    return intersection_point


def sutherland_cohen(p_list, xL, yT, xR, yB) -> list or False:
    """线段裁剪

    PS : 规定若返回列表则列表的第2个元素必定是在裁剪区域内部的点的坐标

    :param p_list: (list of list of int: [[x0, y0], [x1, y1]]) 线段的起点和终点坐标
    :param xL: 裁剪窗口左上角x坐标, 左边沿
    :param yT: 裁剪窗口左上角y坐标, 上边沿
    :param xR: 裁剪窗口右下角x坐标, 右边沿
    :param yB: 裁剪窗口右下角y坐标, 下边沿
    :return: (list of list of int: [[x_0, y_0], [x_1, y_1]]) 裁剪后线段的起点和终点坐标(如果线段在区域外则返回False)
    """
    code1 = encode_sutherland_cohen_int(xL, xR, yT, yB, p_list[0])
    code2 = encode_sutherland_cohen_int(xL, xR, yT, yB, p_list[1])
    location = location_relation(code1, code2)
    # 线段在区域外
    if location == 0:
        return False

    # 线段在区域内
    elif location == 1:
        return p_list

    # 前点在区域内
    elif location == 2:
        return intersection_line_rectangle_v1outRec_v2inRec([p_list[1], p_list[0]], xL, yT, xR, yB)

    # 后点在区域内
    elif location == 3:
        return intersection_line_rectangle_v1outRec_v2inRec(p_list, xL, yT, xR, yB)

    # 两点都不在区域内且与矩形有交点
    elif location == 4:
        return intersection_line_rectangle_v1v2outRec_two_point(p_list, xL, yT, xR, yB)
