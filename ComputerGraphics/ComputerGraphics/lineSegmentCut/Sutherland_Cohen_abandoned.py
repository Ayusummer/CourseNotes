# -*- coding: utf-8 -*-
# @Time    : 2021/5/21 8:16
# @Author  : 咸鱼型233
# @File    : Sutherland_Cohen_abandoned.py
# @Software: PyCharm
# @Function: 
# @ChangeLog : 图形数据结构设计得太复杂了,烂尾了,别看了(
import turtle
import math

# 导入自定义绘图函数
from ComputerGraphics.basic_draw import line_to
from ComputerGraphics.basic_draw import draw_circle


def encode_sutherland_cohen_lst(xL, xR, yT, yB, x, y) -> list:
    """编码裁剪算法的编码函数->返回列表

    :param xL: 左框线
    :param xR: 右框线
    :param yT: 上框线
    :param yB: 下框线
    :param x: 待编码点横坐标
    :param y: 待编码点纵坐标
    :return: (list of int: [e1, e2, e3, e4]) 4位编码值

    PS: 方法很笨且低效,不想动脑子,可以用位操作简化处理逻辑从而优化时空复杂度

    PS2 : 点与区域边沿重合也算在区域内
    """
    encode = list()
    if y > yT:
        encode.append(1)
    else:
        encode.append(0)
    if y < yB:
        encode.append(1)
    else:
        encode.append(0)
    if x > xR:
        encode.append(1)
    else:
        encode.append(0)
    if x < xL:
        encode.append(1)
    else:
        encode.append(0)
    return encode


def encode_sutherland_cohen_int(xL, xR, yT, yB, x, y) -> int:
    """编码裁剪算法的编码函数->返回整形编码数据

    PS1 : 毕竟上一版已经很笨了,判断八次最后生成个列表,还不如直接判断8次生成一个整型的编码,这样下一步还可以用位运算简化逻辑

    PS2 : 点与区域边沿重合也算在区域内

    :param xL: 左框线
    :param xR: 右框线
    :param yT: 上框线
    :param yB: 下框线
    :param x: 待编码点横坐标
    :param y: 待编码点纵坐标
    :return: 整型数据,对应九个区域的编码值
    """
    encode = 0
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

    PS : 老师比较仁慈,实验要求的例程中不存在线段两端点都在区域外且与区域有两个交点的情况,因此后面实际使用上不会出现返回值为4的情况

    :param code1: 一个端点的编码值
    :param code2: 另一个端点的编码值
    :return: 0 -> 线段在区域外;   1 -> 线段在区域内;   2->线段与区域有交点且前点在区域内  3 -> 线段与区域有交点且后点在区域内  4 -> 线段端点都在区域外且与区域有交点
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


def intersection_line_rectangle(p_lst, xL, yT, xR, yB) -> list:
    """求线段所在直线与矩形的(四个)交点

    :param p_lst: (list of list of int: [[x0, y0], [x1, y1]]) 线段的起点和终点坐标(后者在矩形内)
    :param xL: 裁剪窗口左上角x坐标, 左边沿
    :param yT: 裁剪窗口左上角y坐标, 上边沿
    :param xR: 裁剪窗口右下角x坐标, 右边沿
    :param yB: 裁剪窗口右下角y坐标, 下边沿
    :return: (list of list of int or False: x) 裁剪后线段的起点和终点坐标(如果线段在区域外则返回False)
    """
    pass
    # 想了想感觉没必要写,每个线段都求四次那还了得


def intersection_line_xLine(p_lst, x_line):
    """求线段所在直线与一条与x轴垂直的直线的交点的纵坐标

    :param p_lst: (list of list of int: [[x0, y0], [x1, y1]]) 线段的起点和终点坐标(后者在矩形内)
    :param x_line: 一条与 x 轴垂直的直线与 x 轴交点的横坐标
    :return: int -> 线段所在直线与一条与x轴垂直的直线的交点的纵坐标
    """
    xA = p_lst[0][0]
    yA = p_lst[0][1]
    xB = p_lst[1][0]
    yBB = p_lst[1][1]
    if xA == xB:
        if xA != x_line:
            return False
        else:
            return math.fabs(yA - yBB)      # 重合,返回两点纵坐标差值
    else:
        return (x_line * (yA - yBB) + xA * yBB - yA * xB) / (xA - xB)


def intersection_line_yLine(p_lst, y_line):
    """求线段所在直线与一条与 y 轴垂直的直线的交点的横坐标

    :param p_lst: (list of list of int: [[x0, y0], [x1, y1]]) 线段的起点和终点坐标(后者在矩形内)
    :param y_line: 一条与 y 轴垂直的直线与 y 轴交点的纵坐标
    :return: int -> 线段所在直线与一条与 y 轴垂直的直线的交点的横坐标
    """
    xA = p_lst[0][0]
    yA = p_lst[0][1]
    xB = p_lst[1][0]
    yBB = p_lst[1][1]
    if yA == yBB:
        if yA != y_line:
            return False
        else:
            return math.fabs(xA - xB)  # 重合, 返回两点横坐标差值
    else:
        return (y_line * (xA - xB) + yA * xB - xA * yBB) / (yA - yBB)


def intersection_line_rectangle_special(p_lst, xL, yT, xR, yB) -> list:
    """求线段与矩形的交点且第2个点在矩形内部

    PS1 : 这是个实验特化函数,并不能求所有线段与矩形的交点;  只有线段中一个端点在矩形内部的情况  没有线段两端点都在矩形外的情况

    PS2 : 为了方便写注释,该函数中线段的两个端点按照参数传入顺序统称为A点和B点

    :param p_lst: (list of list of int: [[x0, y0], [x1, y1]]) 线段的起点和终点坐标(后者在矩形内)
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
    if xA == xL:
        if xB != xL:
            if yA > yT:
                intersection_point = [intersection_line_yLine(p_lst, yT), yT]
            elif yA < yB:
                intersection_point = [intersection_line_yLine(p_lst, yB), yB]
            else:
                pass
        else:
            if yA > yT:
                intersection_point = [xL, yT]
            elif yA < yB:
                intersection_point = [xL, yB]
            else:
                pass



    # A 点在区域左侧
    if xA < xL:
        # A 点在区域左上方
        if yA > yT:
            # 线段所在直线与 xL 的交点在区域上方那么线段与矩形的交点只可能是其所在直线与矩形上边框的交点
            if intersection_line_xLine(p_lst, xL) > yT:
                intersection_point = [intersection_line_yLine(p_lst, yT), yT]
            # 交点不是与上边框的交点就是与左边框的交点
            else:
                intersection_point = [xL, intersection_line_xLine(p_lst, xL)]
        # A 点在区域左下方
        elif yA < yB:
            # 线段所在直线与 xL 的交点在区域下方那么线段与矩形的交点只可能是其所在直线与矩形下边框的交点
            if intersection_line_yLine(p_lst, xL) < yB:
                intersection_point = [intersection_line_yLine(p_lst, yB), yB]
            # 交点不是与下边框的交点就是与左边框的交点
            else:
                intersection_point = [xL, intersection_line_xLine(p_lst, xL)]
        # A 点在区域正左方
        else:
            intersection_point = [xL, intersection_line_xLine(p_lst, xL)]
    # A 点在区域右侧
    elif xA > xR:
        # A 点在区域右上方
        if yA > yT:
            # 线段所在直线与 xR 的交点在区域上方那么线段与矩形的交点只可能是其所在直线与矩形上边框的交点
            if intersection_line_yLine(p_lst, xR) > yT:
                intersection_point = [intersection_line_yLine(p_lst, yT), yT]
            # 交点不是与上边框的交点就是与右边框的交点
            else:
                intersection_point = [xR, intersection_line_xLine(p_lst, xR)]
        # A 点在区域右下方
        elif yA < yB:
            # 线段所在直线与 xR 的交点在区域下方那么线段与矩形的交点只可能是其所在直线与矩形下边框的交点
            if intersection_line_yLine(p_lst, xR) < yB:
                intersection_point = [intersection_line_yLine(p_lst, yB), yB]
            # 交点不是与下边框的交点就是与右边框的交点
            else:
                intersection_point = [xR, intersection_line_xLine(p_lst, xR)]
        # A 点在区域正右方
        else:
            intersection_point = [xR, intersection_line_xLine(p_lst, xR)]
    # A 点在区域正上方
    elif yA > yT:
        intersection_point = [intersection_line_yLine(p_lst, yT), yT]
    # A 点在区域正下方
    elif yA < yB:
        intersection_point = [intersection_line_yLine(p_lst, yB), yB]
    return [intersection_point, p_lst[1]]


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
    code1 = encode_sutherland_cohen_int(xL, xR, yT, yB, p_list[0][0], p_list[0][1])
    code2 = encode_sutherland_cohen_int(xL, xR, yT, yB, p_list[1][0], p_list[1][1])
    location = location_relation(code1, code2)
    if location == 0:
        return False
    elif location == 1:
        return p_list
    # 前点在区域内
    elif location == 2:
        return intersection_line_rectangle_special([p_list[1], p_list[0]], xL, yT, xR, yB)
    # 后点在区域内
    elif location == 3:
        return intersection_line_rectangle_special(p_list, xL, yT, xR, yB)
    # 两点都不在区域内且与矩形有交点, 在本次实验例程中不会出现此种情况,不予考虑
    elif location == 4:
        pass


def clip_circle_rectangle_special(circle, xL, yT, xR, yB):
    """这又是一个例程特化型函数,只考虑矩形内含圆形时矩形裁剪框对圆形的裁剪

    :param circle : 圆形图案的参数 [圆心列表, 半径数值, 弧度]
    :param xL: 裁剪窗口左上角x坐标, 左边沿
    :param yT: 裁剪窗口左上角y坐标, 上边沿
    :param xR: 裁剪窗口右下角x坐标, 右边沿
    :param yB: 裁剪窗口右下角y坐标, 下边沿
    :return: 返回圆周被切割后剩下的弧度范围(从圆周 最右边的点 算起)
    """
    # 不想写了.jpg 直接靠例程写了, 例程里固定切分 1/4 圆, 因此直接返回 -270 (顺时针绘制270°)(注意设置海龟在右点并朝北)
    return -270


def search_table_line_point(point, nums, radius):
    """试验例程特化型函数,用于反查数值,单独拎出来没有任何意义

    """
    div_x = (nums * math.acos(point[0] / radius)) // (2 * math.pi)
    if point[1] > 0:
        return div_x - 1
    else:
        return nums - div_x - 1


def graphic_2D_clip_by_sutherland_cohen(circle, line, table_line_point, xL, yT, xR, yB, nums, radius):
    """通过编码裁剪法对二维图形进行裁剪

    PS : 这个函数的关键就在于第一个参数 graphic 的数据形式, 这里我认为二维图形是由点与线构成的,
    并且由于例程中只含有圆弧以及线段因此该参数的实际情况应当是 [圆], [线段]
    --> [圆心, 半径, 弧度], ...... ,   [[点, [点, 点, ...] ], ...    ]

    :param circle: 圆组 -> [圆心, 半径, 弧度]
    :param line: 线段组 -> [[1, [点, 点, ...] ], ...    ]
    :param table_line_point: 线段断点对照组 -> [[1, 点 ], ...    ]
    :param xL: 裁剪窗口左上角x坐标, 左边沿
    :param yT: 裁剪窗口左上角y坐标, 上边沿
    :param xR: 裁剪窗口右下角x坐标, 右边沿
    :param yB: 裁剪窗口右下角y坐标, 下边沿
    :param nums: 外圆等分数
    :param radius: 外圆半径
    :return: (list of list of int: [[x_0, y_0], [x_1, y_1]]) 裁剪后线段的起点和终点坐标(如果线段在区域外则返回False)
    """
    for i in range(circle.__len__()):
        circle[i][2] = clip_circle_rectangle_special(circle, xL, yT, xR, yB)
    for i in line:
        # 如果 i 就在裁剪区域里,那么就对这些数据做处理
        if encode_sutherland_cohen_int(xL, yT, xR, yB, table_line_point[i][0], table_line_point[i][1]) == 0:
            for j in range(line[i].__len__()):
                if line[search_table_line_point(line[i][j], nums, radius)] != 400:
                    line[search_table_line_point(line[i][j], nums, radius)].append(
                        sutherland_cohen([line[i][j], table_line_point[i]], xL, yT, xR, yB)[0])
            line[i] = 400
            table_line_point[i] = 400
    length = line.__len__()
    for i in range(length):
        if line[i] == 400:
            del line[i]
            del table_line_point[i]
    return [circle, line, table_line_point]


def draw_graphic_2D_circle_line(circle: list, line: dict, table_line_point: dict):
    """绘制由圆形和线段组成的二维图形

    PS : 这又是一个实验例程特化的函数;  规定所有圆的圆心在(0,0); 所有圆形的起绘点都在圆的右点从而需要海龟朝北

    :param circle: 圆组 -> [圆心, 半径, 弧度], ...
    :param line: 线段组 -> { 1 : [点, 点, ...] , ... }
    :param table_line_point: 线段组 -> { 1 : 点 , ... }
    """
    turtle.speed(0)  # 设置笔头移动速度->0->最快
    turtle.ht()  # 隐藏海龟,提高绘制速度
    turtle.setheading(90)  # 海龟朝北
    for i in range(len(circle)):
        draw_circle(circle[i][0][0], circle[i][0][1], circle[i][1], circle[i][2])
    for i in line:
        for j in range(len(line[i])):
            line_to(table_line_point[i][0], table_line_point[i][1], line[i][j][0], line[i][j][1])


def clip_diamond(diamond, xL, yT, xR, yB, nums, radius):
    diamond = graphic_2D_clip_by_sutherland_cohen(diamond[0], diamond[1], diamond[2], xL, yT, xR, yB, nums, radius)
    draw_graphic_2D_circle_line(diamond[0], diamond[1], diamond[2])


"""
相应金刚石绘制函数存储:
"""


def diamond_draw_abandoned(radius, nums):
    """金刚石绘制函数

    PS : 最后一个金刚石图形参数是用来表示整个金刚石图案的信息的,实验四里的裁剪会用上

    :param radius: 外圆半径
    :param nums: 外圆等分数
    :return: diamond -> 金刚石图形参数
    """
    turtle.bgcolor("black")     # 还原示例图片中的黑色底色
    turtle.speed(0)             # 设置笔头移动速度->0->最快
    turtle.ht()                 # 隐藏海龟,提高绘制速度
    x_list = []
    y_list = []
    circle = list()
    line = dict()
    table_line_point = dict()
    for i in range(0, nums):
        # 将圆周上的等分点都加到列表里
        x_list.append(radius * math.cos(2 * math.pi / nums * i))
        y_list.append(radius * math.sin(2 * math.pi / nums * i))
        # 绘制同心圆(注意绘制起点是圆周底点) 并加入到圆组参数中
        circle.append([[0, 0], (i + 1) * (radius / nums), 360])
        draw_circle(0, 0, (i + 1) * (radius / nums))
    for i in range(0, nums):
        line[i] = list()
        table_line_point[i] = [x_list[i], y_list[i]]
        for j in range(i+1, nums):
            line[i].append([x_list[j], y_list[j]])
            line_to(x_list[i], y_list[i], x_list[j], y_list[j])
    return [circle, line, table_line_point]


# 旧版四点式的画线函数
def line_to_abandoned(x, y, ex, ey, color='red'):
    """从(x,y)径直画到(ex,ey)

    :param x: 起始点横坐标
    :param y: 起始点纵坐标
    :param ex: 结束点横坐标
    :param ey: 结束点纵坐标
    :param color: 线条颜色(默认为红色)
    """
    turtle.color(color)     # 设置画笔颜色
    turtle.penup()          # 画笔抬起 -- 移动时不画线
    turtle.goto(x, y)       # 将笔尖移动到(x,y)
    turtle.pendown()        # 落笔
    turtle.goto(ex, ey)     # 画笔直线移动到(ex,ey)并画线
    turtle.color('black')   # 画笔颜色恢复为黑色