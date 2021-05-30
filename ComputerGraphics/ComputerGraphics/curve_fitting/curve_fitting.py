# -*- coding : utf-8 -*-
# @Time      : 2021/5/30 16:25
# @Author    : 咸鱼型233
# @File      : curve_fitting.py
# @Software  : PyCharm
# @Function  : 曲线拟合
# @ChangeLog :
import matplotlib.pyplot as plt
import numpy as np


def Bezier_3_generate_axis(p0: list, p1: list, p2: list, p3: list):
    """通过 4 个控制点求横纵坐标序列并返回
    p0 ~ p3 即为四个控制点, t -> [0, 1]
    """
    x0 = p0[0]
    x1 = p1[0]
    x2 = p2[0]
    x3 = p3[0]
    y0 = p0[1]
    y1 = p1[1]
    y2 = p2[1]
    y3 = p3[1]
    ax = -x0 + 3 * x1 - 3 * x2 + x3
    ay = -y0 + 3 * y1 - 3 * y2 + y3
    bx = 3 * x0 - 6 * x1 + 3 * x2
    by = 3 * y0 - 6 * y1 + 3 * y2
    cx = -3 * x0 + 3 * x1
    cy = -3 * y0 + 3 * y1
    dx = x0
    dy = y0
    t = np.linspace(0, 1)
    x = ax * (t ** 3) + bx * (t ** 2) + cx * t + dx
    y = ay * (t ** 3) + by * (t ** 2) + cy * t + dy
    return [x, y]


def Bezier_3_generate_axis_on_line(p0: list, p1: list, p2: list, p3: list):
    """通过曲线上 4 个点反求控制点并求横纵坐标序列并返回
    p0 ~ p3 即为四个曲线上的点, t -> [0, 1]
    """
    B = np.mat([
        [1, 0, 0, 0],
        [8 / 27, 4 / 9, 2 / 9, 1 / 27],
        [1 / 27, 2 / 9, 4 / 9, 8 / 27],
        [0, 0, 0, 1]
    ])
    C = np.mat([
        p0, p1, p2, p3
    ])
    P = B.I * C
    P = P.tolist()
    print(type(P))
    print(P)
    return Bezier_3_generate_axis(P[0], P[1], P[2], P[3])


def function_draw(x, y):
    """冗余函数,绘制函数图像

    """
    # 使用黑体
    plt.rcParams['font.family'] = ['simhei']
    plt.rcParams['axes.unicode_minus'] = False
    plt.title('函数图', size=16)  # 设置图的标题
    plt.xlabel('x 值', labelpad=10)  # 设置X轴的名称
    plt.ylabel('函\n数\n值',
               rotation=0,  # 文本中的文字水平显示
               linespacing=2,  # 行距
               labelpad=20,  # 文本名称与坐标轴的距离
               position=(10, 0.35)  # 文本名称的纵坐标（第2个数值）
               )
    plt.plot(x, y)  # 画折线图
    plt.show()


def Bezier3_4control_point_draw(p0: list, p1: list, p2: list, p3: list):
    """通过 4 个控制点绘制贝塞尔曲线

    """
    x_lst = Bezier_3_generate_axis(p0, p1, p2, p3)[0]
    y_lst = Bezier_3_generate_axis(p0, p1, p2, p3)[1]
    # 使用黑体
    plt.rcParams['font.family'] = ['simhei']
    plt.rcParams['axes.unicode_minus'] = False
    plt.title('根据 4 个控制点绘制的 Bezier 曲线图', size=16)  # 设置图的标题
    plt.xlabel('x 值', labelpad=10)  # 设置X轴的名称
    plt.ylabel('函\n数\n值',
               rotation=0,  # 文本中的文字水平显示
               linespacing=2,  # 行距
               labelpad=20,  # 文本名称与坐标轴的距离
               position=(10, 0.35)  # 文本名称的纵坐标（第2个数值）
               )
    plt.scatter(p0[0], p0[1])
    plt.scatter(p1[0], p1[1])
    plt.scatter(p2[0], p2[1])
    plt.scatter(p3[0], p3[1])
    plt.plot(x_lst, y_lst)  # 画折线图
    plt.show()


def Bezier3_4point_on_curve_draw(p0: list, p1: list, p2: list, p3: list):
    """通过 4 个曲线上的点绘制内塞尔曲线

    """
    x_lst = Bezier_3_generate_axis_on_line(p0, p1, p2, p3)[0]
    y_lst = Bezier_3_generate_axis_on_line(p0, p1, p2, p3)[1]
    # 使用黑体
    plt.rcParams['font.family'] = ['simhei']
    plt.rcParams['axes.unicode_minus'] = False
    plt.title('根据 4 个曲线上的点绘制的 Bezier 曲线图', size=16)  # 设置图的标题
    plt.xlabel('x 值', labelpad=10)  # 设置X轴的名称
    plt.ylabel('函\n数\n值',
               rotation=0,  # 文本中的文字水平显示
               linespacing=2,  # 行距
               labelpad=20,  # 文本名称与坐标轴的距离
               position=(10, 0.35)  # 文本名称的纵坐标（第2个数值）
               )
    plt.scatter(p0[0], p0[1])
    plt.scatter(p1[0], p1[1])
    plt.scatter(p2[0], p2[1])
    plt.scatter(p3[0], p3[1])
    plt.plot(x_lst, y_lst)  # 画折线图
    plt.show()


def b_spline_basis(i, k, u, nodeVector):
    """计算基函数

    :param i: 控制顶点序号
    :param k: 次数
    :param u: 代入的值
    :param nodeVector: 节点向量
    :return: 返回第i+1个k次基函数在u处的值
    """
    # nodeVector = np.mat(nodeVector)  # 将输入的节点转化成能够计算的数组
    # k=0时，定义一次基函数
    if k == 0:
        if (nodeVector[i] < u) & (u <= nodeVector[i + 1]):  # 若u在两个节点之间，函数之为1，否则为0
            result = 1
        else:
            result = 0
    else:
        # 计算支撑区间长度
        length1 = nodeVector[i + k] - nodeVector[i]
        length2 = nodeVector[i + k + 1] - nodeVector[i + 1]
        # 定义基函数中的两个系数
        if length1 == 0:  # 特别定义 0/0 = 0
            alpha = 0
        else:
            alpha = (u - nodeVector[i]) / length1
        if length2 == 0:
            beta = 0
        else:
            beta = (nodeVector[i + k + 1] - u) / length2
        # 递归定义
        result = alpha * b_spline_basis(i, k - 1, u, nodeVector) + beta * b_spline_basis(i + 1, k - 1, u, nodeVector)
    return result


# 画B样条函数图像
def draw_b_spline(n, k, nodeVector, X, Y):
    plt.figure()
    basis_i = np.zeros(100)  # 存放第i个基函数
    rx = np.zeros(100)  # 存放B样条的横坐标
    ry = np.zeros(100)
    for i in range(n + 1):  # 计算第i个B样条基函数，
        U = np.linspace(nodeVector[k], nodeVector[n + 1], 100)  # 在节点向量收尾之间取100个点，u在这些点中取值
        j = 0
        for u in U:
            nodeVector = np.array(nodeVector)
            basis_i[j] = b_spline_basis(i, k, u, nodeVector)  # 计算取u时的基函数的值
            j = j + 1
        rx = rx + X[i] * basis_i
        ry = ry + Y[i] * basis_i
        # plt.plot(U,basis_i)
    #     print(basis_i)
    # print(rx)
    # print(ry)
    # 使用黑体
    plt.rcParams['font.family'] = ['simhei']
    plt.rcParams['axes.unicode_minus'] = False
    plt.title('三次 B 样条曲线', size=16)  # 设置图的标题
    plt.xlabel('x 值', labelpad=10)  # 设置X轴的名称
    plt.ylabel('函\n数\n值',
               rotation=0,  # 文本中的文字水平显示
               linespacing=2,  # 行距
               labelpad=20,  # 文本名称与坐标轴的距离
               position=(10, 0.35)  # 文本名称的纵坐标（第2个数值）
               )
    plt.plot(X, Y)
    plt.plot(rx, ry)
    plt.show()
