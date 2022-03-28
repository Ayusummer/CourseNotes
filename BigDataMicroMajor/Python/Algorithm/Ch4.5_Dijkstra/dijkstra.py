# -*- coding: utf-8 -*-
# @Time    : 2020/11/20 10:19
# @Author  : 咸鱼型233
# @File    : dijkstra.py
# @Software: PyCharm
# @Function: 迪杰斯特拉算法实现
# 原文链接:    https://blog.csdn.net/weixin_41799019/article/details/98053981
# 待看参考链接: https://www.cnblogs.com/aminor/p/13828811.html

import networkx as nx               # 内置常用的图与复杂网络分析算法
import matplotlib.pyplot as plt     # 使用matplotlib库进行绘图

# 初始化图
s = [0, 0, 1, 1, 7, 7, 2, 8, 2, 6, 2, 3, 3, 5]      # 源结点
t = [1, 7, 7, 2, 8, 6, 8, 6, 5, 5, 3, 5, 4, 4]      # 目的结点
w = [4, 8, 3, 8, 1, 6, 2, 6, 4, 2, 7, 14, 9, 10]    # 权

# 无向图的构建
G = nx.Graph()              # 创建一个无向图
for i in range(0, len(s)):  # 遍历每一条边
    G.add_edge(s[i], t[i], weight=w[i])  # 为图G添加边，并且附上权重weight

# 生成节点位置
pos = nx.spring_layout(G)  # 设置布局
plt.xticks([])  # 取消x轴的刻度
plt.yticks([])  # 取消y轴的刻度

# 把节点画出来
nx.draw_networkx_nodes(G, pos, node_color='r', node_size=500, alpha=0.8)  # 显示每一个结点

# 把边画出来
nx.draw_networkx_edges(G, pos, width=3.0, alpha=0.5, edge_color='b')  # 显示每一条边

# 把节点的标签画出来
nx.draw_networkx_labels(G, pos, font_size=16)  # 显示每一个结点上的数字

# 把边权重画出来
edge_labels = nx.get_edge_attributes(G, 'weight')  # 获取每一条边的权重
nx.draw_networkx_edge_labels(G, pos, edge_labels)  # 为图添加上权重


def get(G):
    # 使用迪杰斯特拉算法获得从源结点（source）到目的结点的最短路径长度
    length1 = nx.dijkstra_path_length(G, 0, 4)
    # 使用迪杰斯特拉算法获取从源结点（source）到目的结点的最短路径
    path1 = nx.dijkstra_path(G, 0, 4)
    # 使用贝尔曼-福特算法获得从源结点（source）到目的结点的最短路径长度
    length2 = nx.bellman_ford_path_length(G, 0, 4)
    # 使用贝尔曼-福特算法获取从源结点（source）到目的结点的最短路径
    path2 = nx.bellman_ford_path(G, 0, 4)
    # 使用迪杰斯特拉算法获得每两个节点之间的最短路径长度
    length3 = dict(nx.all_pairs_dijkstra_path_length(G))
    # 使用迪杰斯特拉算法获得每两个节点之间的最短路径
    path3 = dict(nx.all_pairs_dijkstra_path(G))

    # 实现最短路径的高亮
    answer = []
    for i in range(0, len(path1) - 1):
        answer.append((path1[i], path1[i + 1]))
    nx.draw_networkx_edges(G, pos, edgelist=answer, width=3.0, alpha=0.5, edge_color='y')


get(G)
plt.show()

